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

#include <iostream>

using std::cerr;
using std::endl;

namespace gl_cpp
{
    OpenglApp::~OpenglApp(void)
    {
        /* destroying window before terminating glfw to prevent error */
        window.reset(nullptr);

        glfwTerminate();
    }

    Window OpenglApp::create_window(void)
    {
        GLFWwindow* window_ptr;

        /* Create a windowed mode window and its OpenGL context */
        window_ptr = glfwCreateWindow(640, 480, _settings.title.c_str(), NULL, NULL);

        if (!window_ptr)
        {
            throw std::runtime_error("Couldn't allocate window");
        }

        return Window(window_ptr,glfwDestroyWindow);
    }

    void OpenglApp::init_and_create_window(void)
    {
        /* Initialize the library */
        if (!glfwInit())
        {
            throw std::runtime_error("Couldn't initialize GLFW!");
        }

        this->init();

        window = create_window();

        /* Make the window's context current */
        glfwMakeContextCurrent(window.get());

        // glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
        // glutInitWindowSize(_settings.window_width, _settings.window_height);
        // glutInitWindowPosition(0,0);
        // glutCreateWindow(_settings.title.c_str());

        glfwSetErrorCallback(OpenglApp::error_callback);
        glfwSetKeyCallback(window.get(), OpenglApp::key_callback);
    }

    void OpenglApp::run(void)
    {
        init_and_create_window();

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window.get()))
        {
            /* Render here */

            /* Swap front and back buffers */
            glfwSwapBuffers(window.get());

            /* Poll for and process events */
            glfwPollEvents();
        }
    }


    // =================== CALLBACKS ===================

    void OpenglApp::error_callback(int error, const char* description)
    {
        cerr << "\nError code: " << error
             << "\nDescription: " << description << endl;
    }

    void OpenglApp::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if ((key == GLFW_KEY_ESCAPE) && (action == GLFW_PRESS))
        {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
    }
}