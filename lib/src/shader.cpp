#include "shader.hpp"
#include "opengl.h"

namespace glRender {

std::map<ShaderType, GLenum> shaderTypeToGLenumMap =
{
    {ShaderType::VertexShader, GL_VERTEX_SHADER},
    {ShaderType::FragmentShander, GL_FRAGMENT_SHADER}
};

std::map<ShaderType, const char *> shaderTypeToCharMap =
{
    {ShaderType::VertexShader, "Vertex"},
    {ShaderType::FragmentShander, "Fragment"}
};

inline GLenum convertShaderTypeToGLenum(ShaderType type)
{
    return shaderTypeToGLenumMap[type];
}

inline const char * convertShaderTypeToChar(ShaderType type)
{
    return shaderTypeToCharMap[type];
}

Shader::Shader(ShaderType type)
    : m_type(type)
{
    m_typeString = convertShaderTypeToChar(type);
//    // Get the type of the shader
//    if (type == GL_VERTEX_SHADER)
//    {
//        m_typeString = "Vertex";
//    }
//    else if (type == GL_FRAGMENT_SHADER)
//    {
//        m_typeString = "Fragment";
//    }
//    else
//    {
//        m_typeString = "Geometry";
//    }

    // Create the vertex shader id / handle
    // Note: If you segfault here you probably don't have a valid rendering context.
    m_id = glCreateShader(convertShaderTypeToGLenum(type));
}

Shader::~Shader()
{
    glDeleteShader(m_id);
}

uint Shader::id()
{
    return m_id;
}

const char * Shader::source()
{
    return m_source.c_str();
}

// Method to load the shader contents from a file
void Shader::loadFromString(const char * sourceString)
{
    // Keep hold of a copy of the source
    m_source = sourceString;

    // Get the source as a pointer to an array of characters
    const char *sourceChars = m_source.c_str();

    // Associate the source with the shader id
    glShaderSource(m_id, 1, &sourceChars, NULL);
}

// Method to load the shader contents from a string
bool Shader::loadFromFile(const char * filename)
{
    std::ifstream file;

    file.open( filename );

    if (!file.good() )
    {
        std::cout << "Failed to open file: " << filename << std::endl;
        return false;
    }

    // Create a string stream
    std::stringstream stream;

    // Dump the contents of the file into it
    stream << file.rdbuf();

    // Close the file
    file.close();

    // Convert the StringStream into a string
    m_source = stream.str();

    // Get the source string as a pointer to an array of characters
    const GLchar *sourceChars = m_source.c_str();

    // Associate the source with the shader id
    glShaderSource(m_id, 1, &sourceChars, NULL);
    return true;
}


// Method to compile a shader and display any problems if compilation fails
bool Shader::compile()
{
    // Compile the shader
    glCompileShader(m_id);

    // Check the compilation status and report any errors
    GLint shaderStatus;
    glGetShaderiv(m_id, GL_COMPILE_STATUS, &shaderStatus);

    // If the shader failed to compile, display the info log and quit out
    if (shaderStatus == GL_FALSE)
    {
        GLint infoLogLength;
        glGetShaderiv(m_id, GL_INFO_LOG_LENGTH, &infoLogLength);

        GLchar *strInfoLog = new GLchar[infoLogLength + 1];
        glGetShaderInfoLog(m_id, infoLogLength, &infoLogLength, strInfoLog);

        std::cout << m_typeString << " shader compilation failed: " << strInfoLog << std::endl;
        delete[] strInfoLog;

        glDeleteShader(m_id);
        // glfwTerminate();
        return false;
    }
    else
    {
        std::cout << m_typeString << " shader compilation OK" << std::endl;
        return true;
    }
}
    
}
