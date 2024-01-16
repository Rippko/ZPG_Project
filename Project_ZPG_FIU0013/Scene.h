#pragma once
/**
 *
 * @brief Scene header file
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
#include <vector>
#include <cstdlib>
#include <ctime>
#include <unordered_map>

#include "Shader.h"
#include "Model.h"
#include "DrawableModel.h"
#include "Rotation.h"
#include "Scale.h"
#include "Translation.h"
#include "LineMovement.h"
#include "BezierMovement.h"
#include "Texture.h"
#include "SkyboxModel.h"

class Scene
{
private:
	GLFWwindow* viewed_window;
	std::unordered_map<std::string, Model*> models_map;
	std::unordered_map<std::string, Shader*> shaders_map;
	
public:
	DrawableModel* sky_box;
	Scene(std::unordered_map<std::string, Model*> models_map, std::unordered_map<std::string, Shader*> shaders_map);
	~Scene() = default;
	void CreateSkybox();
	void Phong(std::vector<DrawableModel*>& d_models);
	void SolarSystem(std::vector<DrawableModel*>& d_models);
	void Forest(std::vector<DrawableModel*>& d_models);
	void drawTree(glm::vec3 position, std::unordered_map<std::string, Shader*> shaders_map, std::vector<DrawableModel*>& d_models);
	void deleteObject(int index, std::vector<DrawableModel*>& d_models);
};