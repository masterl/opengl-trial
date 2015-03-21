#include <iostream>

#include <GL/glew.h>

#include <GL/freeglut.h>

using namespace std;

GLuint program;
GLint attribute_coord2d;

bool init_resources(void)
{
    GLint compile_ok = GL_FALSE;
    GLint link_ok = GL_FALSE;

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);

    const char *vs_source = 
    #ifdef GL_ES_VERSION_2_0
        "#version 100\n"  // OpenGL ES 2.0
    #else
        "#version 120\n"  // OpenGL 2.1
    #endif
    "attribute vec2 coord2d;                  "
    "void main(void) {                        "
    "  gl_Position = vec4(coord2d, 0.0, 1.0); "
    "}";

    glShaderSource(vs, 1, &vs_source, NULL);

    glCompileShader(vs);

    glGetShaderiv(vs, GL_COMPILE_STATUS, &compile_ok);

    if(0 == compile_ok)
    {
        cerr << "Error in vertex shader\n" << endl;
        return false;
    }

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    
    const char *fs_source =
    "#version 120           \n"
    "void main(void) {        "
    "  gl_FragColor[0] = gl_FragCoord.x/640.0; "
    "  gl_FragColor[1] = gl_FragCoord.y/480.0; "
    "  gl_FragColor[2] = 0.3; "
    "}";

    glShaderSource(fs, 1, &fs_source, NULL);
    glCompileShader(fs);
    glGetShaderiv(fs, GL_COMPILE_STATUS, &compile_ok);

    if (!compile_ok)
    {
        cerr << "Error in fragment shader\n" << endl;
        return false;
    }

    program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
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
         0.0,  0.2,
        -0.2,  0.0,
         0.2,  0.0,
         0.0, -0.3,
        -0.3,  0.0,
         0.3,  0.0
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

    /* Display the result */
    glutSwapBuffers();
}

void free_resources(void)
{
    glDeleteProgram(program);
}

int main(int argc,char *argv[])
{
    glutInit(&argc,argv);
    glutInitContextVersion(2,0);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("OpenGL doido");

    GLenum glew_status = glewInit();
    if(glew_status != GLEW_OK)
    {
        cerr << "\nError: " << glewGetErrorString(glew_status) << endl;
        return 1;
    }

    if(init_resources())
    {
        glutDisplayFunc(onDisplay);
        glutMainLoop();
    }
    else
    {
        cerr << "Couldn't init resources!" << endl;
    }

    free_resources();

    return 0;
}
