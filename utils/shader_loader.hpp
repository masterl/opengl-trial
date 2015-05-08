/*
The MIT License (MIT)

Copyright (c) 2015 Leonardo de Oliveira Lourenço

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

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
    GLuint create_shader(std::string const &filename, GLenum const &type);

    /*   ------------------------
        |   read_shader_source   |
         ------------------------

         Reads file 'filename' and store it's contents on GLchar vector 'filecontents'
    */
    bool read_shader_source(std::string const &filename,std::vector<GLchar> &filecontents);

    void load_shader(GLuint &shader,std::string const &filename, GLenum const &type);
}

#endif
