#pragma once
#include "LineMovement.h"
#include <vector>
#include <glm/mat4x3.hpp>
#include <glm/mat3x3.hpp>
class BezierMovement : public LineMovement
{
private:
	std::vector<glm::mat4x3> points;
	glm::mat4 base_function_coefficients;
public:
	BezierMovement(glm::mat4x3 first_curve, glm::mat4 bfs, float delta = 0.02f, float start = 0.0f);
	glm::mat4 TransformMatrix() override;
	void AddPoints(glm::mat3x3 points);
};

