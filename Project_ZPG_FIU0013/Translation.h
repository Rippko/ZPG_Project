#pragma once
/**
 *
 * @brief Translation header file
 *
 * @author Adam Fiury
 *
 * @year 2023
 **/
#include "Transformation.h"
class Translation : public Transformation
{
private:
	glm::vec3 movement;
	bool isDynamic;
public:
	Translation(glm::vec3 movement, bool isDynamic);
	glm::mat4 TransformMatrix();
};

