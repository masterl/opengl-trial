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

#include <iostream>

#include <GLFW/glfw3.h>
#include "game.hpp"

using namespace std;

void glfw_init(void)
{
    /* Initialize the library */
    if (!glfwInit())
    {
        std::terminate();
    }
}

int main(void)
{
    try
    {
        glfw_init();
        gl_cpp::Window window = gl_cpp::create_window();

        /* Make the window's context current */
        glfwMakeContextCurrent(window.get());

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
    catch(std::exception &e)
    {
        cerr << "\n\tERROR\n" << e.what() << endl;
    }
    glfwTerminate();

    return 0;
}
