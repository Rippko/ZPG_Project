#include "LineMovement.h"

LineMovement::LineMovement(float delta, float start)
{
    this->delta = delta;
    this->start = start;
    this->isDynamic = true;
    this->_return = false;
}

LineMovement::LineMovement(glm::vec3 point, glm::vec3 direction, float delta, float start)
{
    this->point = point;
    this->direction = direction;
    this->delta = delta;
    this->start = start;
    this->isDynamic = true;
    this->_return = false;
}

glm::mat4 LineMovement::TransformMatrix()
{
    if (isDynamic) {
        glm::mat4 matrix = glm::translate(glm::mat4(1.0f), this->point + this->direction * this->start);
        if (start > 1) _return = !_return;
        else if (start < 0) _return = !_return;

        if (!_return) start += delta;
        else start -= delta;
        return matrix;
    }
}
