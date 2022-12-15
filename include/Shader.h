#ifndef LIQSURFACE_SHADER_H
#define LIQSURFACE_SHADER_H

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <fstream>

class Shader {
    unsigned int ID;
public:
    Shader(const char* vertexPath, const char* fragmentPath);
    void setVec3(const std::string& name, const glm::vec3& vec) const;
    void setMat4(const std::string& name, const glm::mat4& mat) const;
    void use() const;
};


#endif //LIQSURFACE_SHADER_H
