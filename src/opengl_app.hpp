#ifndef OPENGL_APP_H
#define OPENGL_APP_H

#include <string>
#include <GLFW/glfw3.h>
#include <GL/freeglut.h>

namespace gl_cpp
{
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
            OpenglApp(void)
            {
            }
            virtual ~OpenglApp(void)
            {
            }
            virtual void run(void) final
            {
                init_and_create_window();
            }
        protected:
            virtual void init(void)
            {
            }

            void set_title(std::string const &title)
            {
                _settings.title;
            }

            void set_window_size(int width,int height)
            {
                _settings.window_width = width;
                _settings.window_height = height;
            }
        private:
            _gl_app_settings _settings;

            void init_and_create_window(void);
    };
}

#endif
