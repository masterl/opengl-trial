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

#ifndef GAME_H
#define GAME_H

#include "../utils/shader_loader.hpp"
#include "opengl_app.hpp"


class Game : public gl_cpp::OpenglApp
{
    public:
        Game(void)
        {
        }
        virtual ~Game(void)
        {
        }
    protected:
        virtual void init(void)
        {
        }
        virtual void startup(void)
        {
            GLint link_ok = GL_FALSE;

            GLuint vertex_shader;
            gl_shaders::load_shader(vertex_shader,"shaders/example_vertex_shader.glsl",GL_VERTEX_SHADER);

            GLuint fragment_shader;
            gl_shaders::load_shader(fragment_shader,"shaders/example_fragment_shader.glsl",GL_FRAGMENT_SHADER);

            program = glCreateProgram();
            glAttachShader(program, vertex_shader);
            glAttachShader(program, fragment_shader);
            glLinkProgram(program);
            glGetProgramiv(program, GL_LINK_STATUS, &link_ok);
            if (!link_ok)
            {
                throw std::runtime_error("Couldn't initialize opengl program!");
            }

            const char* attribute_name = "coord2d";
            attribute_coord2d = glGetAttribLocation(program, attribute_name);
            if (attribute_coord2d == -1)
            {
                // cerr << "Could not bind attribute %s\n" << attribute_name << endl;
                throw std::runtime_error("Couldn't bind attribute" + std::string(attribute_name) + "!");
            }
        }
        virtual void render(double time_delta)
        {


            // glClearColor(1.0, 1.0, 1.0, 1.0);
            // glClear(GL_COLOR_BUFFER_BIT);

            // glUseProgram(program);
            // glEnableVertexAttribArray(attribute_coord2d);
            // GLfloat triangle_vertices[] = {
            //      0.0,  0.5,
            //     -0.5,  0.0,
            //      0.5,  0.0,
            //      0.0, -0.8,
            //     -0.8,  0.0,
            //      0.8,  0.0
            // };
            // /* Describe our vertices array to OpenGL (it can't guess its format automatically) */
            // glVertexAttribPointer(
            //     attribute_coord2d, // attribute
            //     2,                 // number of elements per vertex, here (x,y)
            //     GL_FLOAT,          // the type of each element
            //     GL_FALSE,          // take our values as-is
            //     0,                 // no extra data between each position
            //    triangle_vertices  // pointer to the C array
            // );

            // /* Push each element in buffer_vertices to the vertex shader */
            // glDrawArrays(GL_TRIANGLES, 0, 6);
            // glDisableVertexAttribArray(attribute_coord2d);
        }
    private:
        GLuint program;
        GLint attribute_coord2d;
};

#endif
