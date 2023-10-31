#include <GL/glew.h>
#include "drawing.h"

void draw(EngineContext *context) {
    // Clear the color buffer
    glClear(GL_COLOR_BUFFER_BIT);

    // Set the color to white
    glColor3f(0.0f, 0.5f, 0.5f);

    // Draw quad on entire screen
    glBegin(GL_TRIANGLES);
        glVertex3f(-1, -1, 0);glVertex3f( 1, -1, 0);glVertex3f( 1,  1, 0);
        glVertex3f(-1, -1, 0);glVertex3f( 1,  1, 0);glVertex3f(-1,  1, 0);
    glEnd();

    // Swap the buffers
    SDL_GL_SwapWindow(context->window);
}

const char* read_file(const char* filename)
{
    FILE* file = fopen(filename, "rb");
    if (file == NULL)
    {
        fprintf(stderr, "File %s not found.\n", filename);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* data = new char[length + 1];
    fread(data, 1, length, file);
    data[length] = 0;

    fclose(file);
    return data;
}

Shader::Shader(const char *vertexSourceFile, const char *fragmentSourceFile)
{
    const char *vertexSource = read_file(vertexSourceFile);
    const char *fragmentSource = read_file(fragmentSourceFile);

    // Create the shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // Load the source code into the shaders
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);

    // Compile the shaders
    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    // Check if shaders compiled successfully
    GLint status;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint length;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &length);
        GLchar *info = new GLchar[length + 1];
        glGetShaderInfoLog(vertexShader, length, NULL, info);
        fprintf(stderr, "Vertex shader compilation failed:\n%s\n", info);
        delete[] info;
    }
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint length;
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &length);
        GLchar *info = new GLchar[length + 1];
        glGetShaderInfoLog(fragmentShader, length, NULL, info);
        fprintf(stderr, "Fragment shader compilation failed:\n%s\n", info);
        delete[] info;
    }

    // Link the shaders into a program
    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    // Check if shaders linked successfully
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
        GLchar *info = new GLchar[length + 1];
        glGetProgramInfoLog(program, length, NULL, info);
        fprintf(stderr, "Shader linking failed:\n%s\n", info);
        delete[] info;
    }

    // Clean up shaders (we don't need them anymore because they are in the program)
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader() { glDeleteProgram(program); }
void Shader::use() { glUseProgram(program); }

// draws a quad on the entire screen using the provided shader
void draw_shader(EngineContext *context, Shader *shader) {
    // set up vertex data and buffers
    float vertices[] = {
        // positions        // texture coords
        -1.0f,  1.0f,  0.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  0.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  0.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  0.0f,  1.0f, 1.0f
    };
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

    // draw quad using the provided shader
    shader->use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

    // cleanup
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}