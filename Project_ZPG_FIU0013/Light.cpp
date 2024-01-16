#include "Light.h"

Light::Light(glm::vec3 lightColor, float Kc, float Kl, float Kq)
{
	this->lightColor = lightColor;
	this->Kc = Kc;
	this->Kl = Kl;
	this->Kq = Kq;
}
