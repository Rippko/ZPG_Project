#include "DirectionLight.h"
DirectionLight::DirectionLight(glm::vec3 lightDirection,
	glm::vec3 lightColor, float Kc, float Kl, float Kq) : Light(lightColor, Kc, Kl, Kq)
{
	this->lightDirection = lightDirection;
}

void DirectionLight::notifyObservers(int index)
{
	for (Observer* observer : observers) {
		observer->updateDirLight(index, this->lightDirection, this->lightColor, this->Kc, this->Kl, this->Kq);
	}
}
