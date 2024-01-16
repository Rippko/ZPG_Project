#include "Rotation.h"

Rotation::Rotation(float angle, glm::vec3 ra, bool isDynamic)
{
	this->rotation_axis = ra;
	this->angle = angle;
	this->isDynamic = isDynamic;
	this->new_angle = this->angle;
}

glm::mat4 Rotation::TransformMatrix()
{
	if (isDynamic) {
		glm::mat4 matrix1 = glm::mat4(1.f);
		//                            speed of rotation
		matrix1 = glm::rotate(matrix1, glm::radians(this->angle), this->rotation_axis);
		this->angle += this->new_angle;
		this->angle = fmod(this->angle, 360);
		return matrix1;
	}
	else {
		glm::mat4 matrix = glm::mat4(1.0f);
		matrix = glm::rotate(matrix, glm::radians(this->angle), this->rotation_axis);
		return matrix;
	}
}
