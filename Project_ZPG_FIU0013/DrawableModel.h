#pragma once
/**
 *
 * @brief DrawableModel header file
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
#include "Model.h"
#include "Shader.h"
#include "TransformationComposite.h"
#include "Material.h"

class DrawableModel
{
private:
	Model* model;
	Shader* shader;
	Material* material;
	glm::mat4 matrix;
	TransformationComposite* transformation_comp;
public:
	int model_id;
	DrawableModel(Model* model, Shader* shader,
				  TransformationComposite* transformation_comp,
				  Material* material);
	~DrawableModel() = default;
	void Render();
	void Update();
	Model* GetModel();
};

