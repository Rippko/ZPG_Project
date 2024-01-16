#include "Material.h"

Material::Material(glm::vec3 d_objectColor, glm::vec3 d_ambientColor, glm::vec3 d_specularColor, glm::vec3 d_diffuseColor, float d_shininess)
{
	this->objectColor = d_objectColor;
	this->ambientColor = d_ambientColor;
	this->specularColor = d_specularColor;
	this->diffuseColor = d_diffuseColor;
	this->shininess = d_shininess;
}

Material::Material(glm::vec3 d_objectColor, glm::vec3 d_ambientColor, glm::vec3 d_specularColor, glm::vec3 d_diffuseColor, float d_shininess, Texture* tex)
{
	this->objectColor = d_objectColor;
	this->ambientColor = d_ambientColor;
	this->specularColor = d_specularColor;
	this->diffuseColor = d_diffuseColor;
	this->texture = tex;
}
