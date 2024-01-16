#pragma once
/**
 *
 * @brief Shader header file
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

//Include the standard C++ headers  
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include "Observer.h"

class Shader : public Observer
{
private:
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint shaderProgram;
public:
	Shader(const char* input_vertex_shader, const char* input_fragment_shader);
	std::string loadShader(const std::string& path);
	void ShaderCheck();
	void UseShaderProgram();
	void LinkDataToShader(const char* name, const int value);
	void LinkDataToShader(const char* name, const float value);
	void LinkDataToShader(const char* name, const glm::mat4& matrix);
	void LinkDataToShader(const char* name, const glm::vec3& vec3);
	void updateCamera(const glm::vec3& cameraPos, const glm::vec3& cameraFront, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);
	void updatePointLight(int index, const glm::vec3& lightPos, const glm::vec3& lightColor, float Kc, float Kl, float Kq);
	void updateDirLight(int index, const glm::vec3& lightDir, const glm::vec3& lightColor, float Kc, float Kl, float Kq);
	void updateSpotlight(int index, const glm::vec3& lightPos, const glm::vec3& lightDir, float cutOff, float outerCutOff, const glm::vec3& lightColor, float Kc, float Kl, float Kq);
};