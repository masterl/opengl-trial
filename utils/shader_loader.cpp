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

#include "shader_loader.hpp"

#include <stdexcept>

namespace uf = Utility_Functions;

namespace gl_shaders
{
    void print_log(GLuint object)
    {
        GLint log_length = 0;

        if (glIsShader(object))
        {
            glGetShaderiv(object, GL_INFO_LOG_LENGTH, &log_length);
        }
        else if (glIsProgram(object))
        {
            glGetProgramiv(object, GL_INFO_LOG_LENGTH, &log_length);
        }
        else
        {
            throw std::domain_error("Not a shader or program!");
        }

        std::vector<GLchar> log_msg;

        log_msg.resize(log_length+1,'\0');

        if (glIsShader(object))
        {
            glGetShaderInfoLog(object, log_length, NULL, log_msg.data());
        }
        else if (glIsProgram(object))
        {
            glGetProgramInfoLog(object, log_length, NULL, log_msg.data());
        }

        throw std::invalid_argument(std::string(log_msg.data()));
    }

    GLuint  create_shader(std::string const &filename, GLenum const &type)
    {
        std::vector<GLchar> source_vector;

        if(!read_shader_source(filename,source_vector))
        {
            throw std::runtime_error("Couldn't read shader file " + filename);
        }

        GLuint res = glCreateShader(type);

        const GLchar* sources[2] = {
            #ifdef GL_ES_VERSION_2_0
                "#version 100\n"
                "#define GLES2\n",
            #else
                "#version 120\n",
            #endif
                source_vector.data() };

        glShaderSource(res, 2, sources, NULL);

        glCompileShader(res);
        GLint compile_ok = GL_FALSE;
        glGetShaderiv(res, GL_COMPILE_STATUS, &compile_ok);

        if(compile_ok == GL_FALSE)
        {
            std::cerr << "\n" << filename << ": ";
            print_log(res);
            glDeleteShader(res);
            return 0;
        }

        return res;
    }

    bool read_shader_source(const std::string &filename,std::vector<GLchar> &filecontents)
    {
        if(uf::read_file_to_vector(filename,filecontents))
        {
            filecontents.push_back('\0');
            return true;
        }
        return false;
    }

    void load_shader(GLuint &shader,std::string const &filename, GLenum const &type)
    {
        shader = gl_shaders::create_shader(filename, type);

        if(shader == 0)
        {
            throw std::runtime_error("Couldn't compile shader from " + filename);
        }
    }
}
