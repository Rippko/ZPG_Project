#include "BezierMovement.h"

BezierMovement::BezierMovement(glm::mat4x3 first_curve, glm::mat4 bfs, float delta, float start) : LineMovement(delta, start)
{
	this->points.push_back(first_curve);
	this->base_function_coefficients = bfs;
	this->isDynamic = true;
}

glm::mat4 BezierMovement::TransformMatrix()
{
	if (isDynamic) {
		int wholeProgress = (int)(start);
		float t = start - (float)(wholeProgress);
		glm::vec4 parameters = glm::vec4(glm::pow(t, 3), glm::pow(t, 2), t, 1.0f);

		const int max = (int)(points.size());
		if (start + delta > (float)max && !_return) {
			_return = !_return;
		}
		else if (start - delta < 0 && _return) {
			_return = !_return;
		}

		if (!_return) {
			start += delta;
		}
		else {
			start -= delta;
		}

		return glm::translate(glm::mat4(1.0f), parameters * this->base_function_coefficients * glm::transpose(points[wholeProgress]));
	}
}

void BezierMovement::AddPoints(glm::mat3x3 new_points)
{
	glm::mat4x3 new_curve = glm::mat4x3(glm::vec3(this->points[this->points.size() - 1][3]), glm::vec3(new_points[0]), glm::vec3(new_points[1]), glm::vec3(new_points[2]));
	this->points.push_back(new_curve);
}


