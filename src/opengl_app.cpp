#include "opengl_app.hpp"

namespace gl_cpp
{
    void OpenglApp::init_and_create_window(void)
    {
        this->init();

        glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
        glutInitWindowSize(_settings.window_width, _settings.window_height);
        glutInitWindowPosition(0,0);
        glutCreateWindow(_settings.title.c_str());
    }
}