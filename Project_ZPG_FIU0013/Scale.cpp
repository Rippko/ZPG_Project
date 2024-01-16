#include "Scale.h"
Scale::Scale(float scale, bool isDynamic)
{
    this->scale = scale;
    this->isDynamic = isDynamic;
}

glm::mat4 Scale::TransformMatrix()
{
    if (isDynamic) {
        glm::mat4 s_matrix = glm::mat4(1.0f);
        s_matrix = glm::scale(s_matrix, glm::vec3(this->scale));
        this->scale++;
        return s_matrix;
    }
    else {
        glm::mat4 s_matrix = glm::mat4(1.0f);
        s_matrix = glm::scale(s_matrix, glm::vec3(this->scale));
        return s_matrix;
    }
}