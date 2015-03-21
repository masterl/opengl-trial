#ifndef SHADER_LOADER_H
#define SHADER_LOADER_H

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "file_operations.hpp"

namespace gl_shaders
{
    /**
    * Display compilation errors from the OpenGL shader compiler
    */
    void print_log(GLuint object);

    /**
    * Compile the shader from file 'filename', with error handling
    */
    GLuint create_shader(const char* filename, GLenum type);

    /*   ------------------------
        |   read_shader_source   |
         ------------------------

         Reads file 'filename' and store it's contents on GLchar vector 'filecontents'
    */
    bool read_shader_source(const std::string &filename,std::vector<GLchar> &filecontents);
}

#endif
