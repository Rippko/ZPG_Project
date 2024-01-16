#pragma once
#include "Transformation.h"
class LineMovement : public Transformation
{
protected:
	glm::vec3 point;
	glm::vec3 direction;
	float delta; //speed / step
	float start;
	bool _return;
	bool isDynamic;
	LineMovement(float delta, float start);
public:
	LineMovement(glm::vec3 point, glm::vec3 direction, float delta = 0.02f, float start = 0.0f);
	glm::mat4 TransformMatrix() override;
};

