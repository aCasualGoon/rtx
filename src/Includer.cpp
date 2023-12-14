#include "Includer.h"

#include <unordered_map>
#include <unordered_set>
#include <string>
#include <fstream>
#include <sstream>
using std::unordered_map, std::unordered_set, std::string, std::ifstream, std::stringstream;

unordered_map<string, string> cache;

string parse_file(string filename, unordered_set<string> already_included)
{
    if()
    string src = "";
    if(cache.find(filename) != cache.end())
        src = cache[filename];
    else {
        ifstream src_file(filename);
        stringstream buffer;
        buffer << src_file.rdbuf();
        src = buffer.str();
    }
    return src;
}

string parse_text(string source, unordered_set<string> already_included) {

}

const char* Includer::parse(const char *src)
    { return parse_text(src, unordered_set<string>()).c_str(); }