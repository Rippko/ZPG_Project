#pragma once
/**
 *
 * @brief Transformation header file
 *
 * @author Adam Fiury
 *
 * @year 2023
 **/
#include <glm/ext/matrix_float4x4.hpp>

#include <glm/ext/matrix_transform.hpp>

class Transformation
{
public:
	virtual glm::mat4 TransformMatrix() = 0;
};