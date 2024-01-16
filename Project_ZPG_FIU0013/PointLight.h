#pragma once
/**
 *
 * @brief PointLight header file
 *
 * @author Adam Fiury
 *
 * @year 2023
 **/
#include "Light.h"
class PointLight : public Light
{
private:
	glm::vec3 lightPosition;
public:
	PointLight(glm::vec3 lightPosition = glm::vec3(30.0f, 1.0f, 30.0f),
			   glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f),
			   float Kc = 0.5f,
			   float Kl = 0.3f,
			   float Kq = 0.12f);
	~PointLight() = default;
	void notifyObservers(int index) override;
};

