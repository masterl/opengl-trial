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

#include "opengl_app.hpp"

namespace gl_cpp
{
    Window create_window(void)
    {
        GLFWwindow* window_ptr;

        /* Create a windowed mode window and its OpenGL context */
        window_ptr = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);

        if (!window_ptr)
        {
            glfwTerminate();
            throw std::runtime_error("Couldn't allocate window");
        }

        return Window(window_ptr,glfwDestroyWindow);
    }

    void OpenglApp::init_and_create_window(void)
    {
        this->init();

        glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
        glutInitWindowSize(_settings.window_width, _settings.window_height);
        glutInitWindowPosition(0,0);
        glutCreateWindow(_settings.title.c_str());
    }
}