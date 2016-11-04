#ifndef __SHADER_PROGRAM_HPP__		
#define __SHADER_PROGRAM_HPP__

#include "base.h"

#include "vec3.hpp"
#include "vec4.hpp"
#include "mat4.hpp"
#include "shader.hpp"
#include "attribute.h"
#include "geometry.hpp"
#include "textures.hpp"

namespace glRender
{
    
enum AttributeType
{
    XYZW,
    XYZ,
    XY,
    X,
    UVW,
    UV,
    RGB,
    RGBA
};

class ShaderProgram
{

public:
    GLuint m_programId;   // The unique ID / handle for the shader program

    ShaderProgram(const char * pathToVertexShader, const char * pathToFragmentShader);
    ~ShaderProgram();

    inline GLuint id()
    {
        return m_programId;
    }

    void attachVertexShader(Shader * shader);
    void attachFragmentShader(Shader * shader);

    void detachVertexShader();
    void detachFragmentShader();

    bool link();

    inline void use()
    {
        glUseProgram(m_programId);
    }

    inline void disable()
    {
        glUseProgram(0);
    }

    Attribute attribute(const char * attribute);
    bool hasAttribute(const char * attribute);
    void setAttributeType(const char * attributeName, AttributeType type);
    void bindAttributesWithBuffers(Geometry * geometry);
    void bindTextures(Textures * textures);
    void unbindTextures(Textures * textures);

    GLuint uniform(const char * uniform);
    int addUniform(const char * uniformName);
    void addUniformsForTextures(Textures * textures);

    int setUniform(const char * uniformName, float value);
    int setUniform(const char * uniformName, int value);
    int setUniform(const char * uniformName, Vec3 & value);
    int setUniform(const char * uniformName, Vec4 & value);
    int setUniform(const char * uniformName, Mat4 & value);

    void setUniform1f(const char * uniformName, float value);
    void setUniform3f(const char * uniformName, Vec3 value);
    void setUniform4f(const char * uniformName, Vec4 value);
    void setUniformMatrix4f(const char * uniformName, Mat4 value);
    void setUniform1i(const char * uniformName, int value);

private:
    friend class Model;

    Shader * m_vertexShader = nullptr;
    Shader * m_fragmentShader = nullptr;

//    GLuint shaderCount; // How many shaders are attached to the shader program

    // Map of attributes and their binding locations
    std::map<std::string, Attribute> attributesList;

    // Map of uniforms and their binding locations
    std::map<std::string,int> uniformLocList;
};

}

#endif /* __SHADER_PROGRAM_HPP__ */
