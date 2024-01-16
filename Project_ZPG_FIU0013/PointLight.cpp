#include "PointLight.h"
PointLight::PointLight(glm::vec3 lightPosition, glm::vec3 lightColor, float Kc, float Kl, float Kq) : Light(lightColor, Kc, Kl, Kq)
{
	this->lightPosition = lightPosition;
}

void PointLight::notifyObservers(int index)
{
	for (Observer* observer : observers) {
		observer->updatePointLight(index, this->lightPosition, this->lightColor, this->Kc, this->Kl, this->Kq);
	}
}