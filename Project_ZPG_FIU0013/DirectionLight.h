#pragma once
/**
 *
 * @brief DirectionLight header file
 *
 * @author Adam Fiury
 *
 * @year 2023
 **/
#include "Light.h"
class DirectionLight : public Light
{
private:
	glm::vec3 lightDirection;
public:
	DirectionLight(glm::vec3 lightDirection = glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3 lightColor = glm::vec3(0.2f, 0.2f, 0.2f),
		float Kc = 0.3f,
		float Kl = 0.1f,
		float Kq = 0.02f);
	~DirectionLight() = default;
	void notifyObservers(int index) override;
};