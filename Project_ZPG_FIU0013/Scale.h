#pragma once
/**
 *
 * @brief Scale header file
 *
 * @author Adam Fiury
 *
 * @year 2023
 **/
#include "Transformation.h"
class Scale : public Transformation
{
private:
	float scale;
	bool isDynamic;
public:
	Scale(float scale, bool isDynamic);
	glm::mat4 TransformMatrix();
};

