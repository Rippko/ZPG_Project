#pragma once
/**
 *
 * @brief Model header file
 *
 * @author Adam Fiury
 *
 * @year 2023
 **/
#include <GL/glew.h>
//Include GLFW  
#include <GLFW/glfw3.h>

//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

//Include the standard C++ headers  
#include <stdlib.h>
#include <stdio.h>
#include <vector>

class Model
{
protected:
	std::vector<float> points;
	GLuint VBO = 0;
	GLuint VAO = 0;
	Model();
public:
	Model(std::vector<float> points);
	void AssignVAO();
	virtual void drawArrays();
	virtual void drawSkyBox();
};

