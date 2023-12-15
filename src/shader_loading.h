#include <string>
/*
* Loads a shader source file and returns its contents as a string.
* extends glsl to support #include "file.glsl"
*   - include paths are relative to the including file
*   - includes are automatically equippet with guard macros
* @param filepath The relative path to the file to load.
* @return The contents of the file as a string.
* @throws std::runtime_error if the file could not be opened.
*/
std::string loadShaderSource(std::string filepath);