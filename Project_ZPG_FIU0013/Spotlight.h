#pragma once
/**
 *
 * @brief Spotlight header file
 *
 * @author Adam Fiury
 *
 * @year 2023
 **/
#include "Light.h"
class Spotlight : public Light
{
private:
	glm::vec3 lightPosition;
	glm::vec3 lightDirection;
	float cutOff;
	float outerCutOff;
public:
	Spotlight(glm::vec3 lightPosition = glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3 lightDirection = glm::vec3(1.0f, 1.0f, 1.0f),
		float cutOff = 15, float outerCutOff = 20,
		glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f),
		float Kc = 1.0f,
		float Kl = 0.2f,
		float Kq = 0.05f);
	~Spotlight() = default;
	void notifyObservers(int index) override;
	void SetPosition(glm::vec3 lightPosition);
	void SetDirection(glm::vec3 lightDirection);
};

