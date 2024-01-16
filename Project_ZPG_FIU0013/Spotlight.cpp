#include "Spotlight.h"
Spotlight::Spotlight(glm::vec3 lightPosition, glm::vec3 lightDirection, float cutOff, float outerCutOff,
	glm::vec3 lightColor, float Kc, float Kl, float Kq) : Light(lightColor, Kc, Kl, Kq)
{
	this->lightPosition = lightPosition;
	this->lightDirection = lightDirection;
	this->cutOff = cutOff;
	this->outerCutOff = outerCutOff;
}

void Spotlight::notifyObservers(int index)
{
	for (Observer* observer : observers) {
		observer->updateSpotlight(index, this->lightPosition, this->lightDirection, this->cutOff, this->outerCutOff, this->lightColor, this->Kc, this->Kl, this->Kq);
	}
}

void Spotlight::SetPosition(glm::vec3 lightPosition)
{
	this->lightPosition = lightPosition;
}

void Spotlight::SetDirection(glm::vec3 lightDirection)
{
	this->lightDirection = lightDirection;
}
