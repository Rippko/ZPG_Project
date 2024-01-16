#include "Translation.h"
#include <glm/ext/matrix_transform.hpp>

Translation::Translation(glm::vec3 movement, bool isDynamic)
{
    this->movement = movement;
    this->isDynamic = isDynamic;
}

glm::mat4 Translation::TransformMatrix()
{
    if (isDynamic) {
        glm::mat4 matrix = glm::mat4(1.0f);
        matrix = glm::translate(matrix, this->movement);
        this->movement++;
        return matrix;
    }
    else {
        glm::mat4 matrix = glm::mat4(1.0f);
        matrix = glm::translate(matrix, this->movement);
        return matrix;
    }
}
