#ifndef _BUFFER_H_
#define _BUFFER_H_

#include <vector>
#include <GL/glew.h>

template <typename T>
class Buffer {
private:
    GLuint bufferID;
public:
    Buffer() {
        glGenBuffers(1, &bufferID);
    }

    ~Buffer() {
        glDeleteBuffers(1, &bufferID);
    }

    void setData(const std::vector<T>& data, GLenum usage = GL_STATIC_DRAW) {
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, bufferID);
        glBufferData(GL_SHADER_STORAGE_BUFFER, data.size() * sizeof(T), data.data(), usage);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    }

    GLuint getBufferID() const {
        return bufferID;
    }

    // Disallow copying for safety
    Buffer(const Buffer&) = delete;
    Buffer& operator=(const Buffer&) = delete;

    // Allow move semantics
    Buffer(Buffer&& other) noexcept : bufferID(other.bufferID) {
        other.bufferID = 0;
    }

    Buffer& operator=(Buffer&& other) noexcept {
        if (this != &other) {
            glDeleteBuffers(1, &bufferID);
            bufferID = other.bufferID;
            other.bufferID = 0;
        }
        return *this;
    }

};

#endif//_BUFFER_H_