#pragma once
/**
 *
 * @brief Rotation header file
 *
 * @author Adam Fiury
 *
 * @year 2023
 **/
#include "Transformation.h"
class Rotation : public Transformation
{
private:
	float angle;
	float new_angle;
	glm::vec3 rotation_axis;
	bool isDynamic;
public:
	Rotation(float angle, glm::vec3 ra, bool isDynamic);
	glm::mat4 TransformMatrix();
};

