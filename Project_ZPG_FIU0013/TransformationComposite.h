#pragma once
/**
 *
 * @brief TransformationComposite header file
 *
 * @author Adam Fiury
 *
 * @year 2023
 **/
#include "Transformation.h"
#include <vector>
class TransformationComposite : public Transformation
{
private:
	std::vector<Transformation*> all_transformations;
public:
	glm::mat4 TransformMatrix();
	void Add(Transformation* ts);
};

