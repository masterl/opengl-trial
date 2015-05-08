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

#ifndef OPENGL_APP_H
#define OPENGL_APP_H

#include <string>
#include <memory>

#include <GLFW/glfw3.h>
#include <GL/freeglut.h>

namespace gl_cpp
{
    typedef std::unique_ptr<GLFWwindow,void(*)(GLFWwindow*)> Window;

    struct _gl_app_settings
    {
        _gl_app_settings(void):
            title("OpenGL cpp"),
            window_width(800),
            window_height(600)
        {
        }
        std::string title;
        int window_width;
        int window_height;
    };

    class OpenglApp
    {
        public:
            OpenglApp(void):
                window(nullptr,glfwDestroyWindow)
            {
            }
            virtual ~OpenglApp(void);

            void run(void);
        protected:
            virtual void init(void)
            {
            }

            virtual void render(double time_delta)
            {
            }

            virtual void startup(void)
            {
            }

            void set_title(std::string const &title)
            {
                _settings.title = title;
            }

            void set_window_size(int width,int height)
            {
                _settings.window_width = width;
                _settings.window_height = height;
            }

            Window create_window(void);
        private:
            _gl_app_settings _settings;
            Window window;

            void init_and_create_window(void);

            static void error_callback(int error, const char* description);
            static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

            void print_versions(void);
    };
}

#endif
