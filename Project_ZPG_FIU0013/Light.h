#pragma once
/**
 *
 * @brief Light header file
 *
 * @author Adam Fiury
 *
 * @year 2023
 **/
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "ObservableObject.h"
class Light : public ObservableObject
{
protected:
	glm::vec3 lightColor;
	float Kc;
	float Kl;
	float Kq;
public:
	Light(glm::vec3 lightColor,float Kc, float Kl, float Kq);
	~Light() = default;
};

