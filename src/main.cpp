#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "../utils/shader_loader.hpp"

using namespace std;

GLuint program;
GLint attribute_coord2d;

bool init_resources(void)
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
        cerr << "glLinkProgram:" << endl;
        return false;
    }

    const char* attribute_name = "coord2d";
    attribute_coord2d = glGetAttribLocation(program, attribute_name);
    if (attribute_coord2d == -1)
    {
        cerr << "Could not bind attribute %s\n" << attribute_name << endl;
        return false;
    }

    return true;
}

void onDisplay(void)
{
    /* Clear the background as white */
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(program);
    glEnableVertexAttribArray(attribute_coord2d);
    GLfloat triangle_vertices[] = {
         0.0,  0.5,
        -0.5,  0.0,
         0.5,  0.0,
         0.0, -0.8,
        -0.8,  0.0,
         0.8,  0.0
    };
    /* Describe our vertices array to OpenGL (it can't guess its format automatically) */
    glVertexAttribPointer(
        attribute_coord2d, // attribute
        2,                 // number of elements per vertex, here (x,y)
        GL_FLOAT,          // the type of each element
        GL_FALSE,          // take our values as-is
        0,                 // no extra data between each position
       triangle_vertices  // pointer to the C array
    );

    /* Push each element in buffer_vertices to the vertex shader */
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDisableVertexAttribArray(attribute_coord2d);


    // === ERROR TEST ===
    // GLuint test;
    // glGenBuffers(-1,&test);
    // GLenum error_code = glGetError();
    // cout << "GL_INVALID_VALUE? " << ( error_code == GL_INVALID_VALUE ? "TRUE" : "FALSE") << endl;


    /* Display the result */
    glutSwapBuffers();
}

void free_resources(void)
{
    glDeleteProgram(program);
}

int main(int argc,char *argv[])
{
    try
    {
        glutInit(&argc,argv);
        glutInitContextVersion(2,0);
        glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
        glutInitWindowSize(1024, 768);
        glutInitWindowPosition(0, 0);
        glutCreateWindow("OpenGL doido");

        GLenum glew_status = glewInit();
        if(glew_status != GLEW_OK)
        {
            cerr << "\nError: " << glewGetErrorString(glew_status) << endl;
            return 1;
        }

        if(init_resources())
        {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glutDisplayFunc(onDisplay);
            glutMainLoop();
        }
        else
        {
            cerr << "Couldn't init resources!" << endl;
        }
    }
    catch(std::exception &e)
    {
        cerr << "\nFatal error!\n\n" << e.what() << endl;
    }

    free_resources();

    return 0;
}
