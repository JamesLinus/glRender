#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "base.h"

#include "shader.hpp"
#include "shaderProgram.hpp"

#include "texture.hpp"
#include "textures.hpp"

namespace glRender {

class ResourceManager
{    
public:
    static ResourceManager & getInstance()
    {
        static ResourceManager instance; // Guaranteed to be destroyed.
                              // Instantiated on first use.
        return instance;
    }
    ResourceManager(ResourceManager const &)               = delete;
    void operator=(ResourceManager const &)  = delete;

    // Note: Scott Meyers mentions in his Effective Modern
    //       C++ book, that deleted functions should generally
    //       be public as it results in better error messages
    //       due to the compilers behavior to check accessibility
    //       before deleted status

public:
    Texture *       getTexture(const char * path);
    ShaderProgram * getShaderProgram(const char * pathToVerticesShader, const char * pathToFragmentShader);

    bool hasShader(const char * path);
    bool initShader(const char * path, const ShaderType & type);
    Shader * getShader(const char * path);


private:
    ResourceManager() {}                    // Constructor? (the {} brackets) are needed here.

    // C++ 11
    // =======
    // We can use the better technique of deleting the methods
    // we don't want.

    std::map<std::string, Texture *> m_textures;
    std::map<std::string, ShaderProgram *> m_shaderPrograms;
    std::map<std::string, Shader *> m_shaders;

};

}

#endif // RESOURCEMANAGER_H
