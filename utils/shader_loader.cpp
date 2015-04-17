#include "shader_loader.hpp"

#include <stdexcept>

namespace uf = Utility_Functions;

void gl_shaders::print_log(GLuint object)
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

GLuint  gl_shaders::create_shader(std::string const &filename, GLenum type)
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

bool gl_shaders::read_shader_source(const std::string &filename,std::vector<GLchar> &filecontents)
{
    if(uf::read_file_to_vector(filename,filecontents))
    {
        filecontents.push_back('\0');
        return true;
    }
    return false;
}
