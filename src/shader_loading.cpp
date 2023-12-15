#include "shader_loading.h"
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <sstream>
#include <fstream>
using std::string, std::unordered_map, std::unordered_set, std::stringstream, std::ifstream, std::vector;

unordered_map<string, string> cache;

string get_siblingPath(string filepath, string sibling) {
    size_t last_slash = filepath.find_last_of("/\\");
    if (last_slash == string::npos)
        return sibling;
    return filepath.substr(0, last_slash + 1) + sibling;
}

// converts "path/to/file.glsl" to "_file_glsl_"
string get_includeName(string path) {
    string result = "_";
    for(char c : path) {
        // if(c == '/' || c == '\\')
        //     continue;
        // if(c == '.')
        //     result += '_';
        // else
        //     result += std::toupper(c);

        switch(c)
        {
        case '/':
        case '\\':
            continue;
        
        case '.':
            result += '_';
            break;

        default:
            result += std::toupper(c);
        }
    }

    return result + "_";
}

string read_file(string filepath)
{
    ifstream file(filepath);
    if (!file.is_open())
        throw std::runtime_error("Could not open file: '" + filepath + "'");

    stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}

string parseFile(string filepath, unordered_set<string> already_included) {
    string content = read_file(filepath);
    stringstream ss(content), result;

    string line;
    uint processed_lines = 0; // for #line directive
    while (getline(ss, line)) {
        if (line.find("#include") == string::npos) {
            result << line << '\n';
            continue;
        }

        size_t first_quote = line.find_first_of('"');
        size_t last_quote = line.find_last_of('"');
        if (first_quote == string::npos || last_quote == string::npos)
            throw std::runtime_error("Invalid #include directive in file: '" + filepath + "'");

        string include_path = line.substr(first_quote + 1, last_quote - first_quote - 1);
        if (!already_included.insert(include_path).second)
            throw std::runtime_error("Circular #include directive in file: '" + filepath + "'");

        string include_name = get_includeName(include_path);
        result << "#ifndef " << include_name << '\n';
        result << "#define " << include_name << '\n';
        result << "#line 1" << '\n';

        string content2include = cache.count(include_path) 
            ? cache[include_path]
            : parseFile(get_siblingPath(filepath, include_path), already_included);
        cache[include_path] = content2include;
        result << content2include << '\n';

        result << "#endif\n";
        result << "#line " << processed_lines + 1 << '\n';
    }
    return result.str();
}

string loadShaderSource(string filepath) {
    string content;
    try {
        content = parseFile(filepath, unordered_set<string>());
    } catch (std::runtime_error &e) {
        cache.clear();
        throw e;
    }
    
    cache.clear();
    return content;
}