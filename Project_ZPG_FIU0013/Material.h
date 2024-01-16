#pragma once
/**
 *
 * @brief Material header file
 *
 * @author Adam Fiury
 *
 * @year 2023
 **/

 //Include GLFW
#include <GL/glew.h>
//Include GLFW  
#include <GLFW/glfw3.h>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include "Texture.h"

//Include the standard C++ headers  
#include <stdlib.h>
#include <stdio.h>
class Material
{
public:
	glm::vec3 objectColor;
	glm::vec3 ambientColor; //ra
	glm::vec3 specularColor; //rs
	glm::vec3 diffuseColor; //rd
	float shininess;
	Texture* texture;
	Material(glm::vec3 d_objectColor = glm::vec3(1.0f, 0.0f, 1.0f),
			 glm::vec3 d_ambientColor = glm::vec3(0.2f, 0.2f, 0.2f),
			 glm::vec3 d_specularColor = glm::vec3(0.5f, 0.5f, 0.5f),
			 glm::vec3 d_diffuseColor = glm::vec3(0.5f, 0.5f, 0.5f),
			 float d_shininess = 32.0f);
	Material(glm::vec3 d_objectColor,
			 glm::vec3 d_ambientColor,
			 glm::vec3 d_specularColor,
			 glm::vec3 d_diffuseColor,
			 float d_shininess, Texture* tex);
	~Material() = default;
};

