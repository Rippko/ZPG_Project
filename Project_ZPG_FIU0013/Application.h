#pragma once
/**
 *
 * @brief Application header file
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
#include <unordered_map>

#include "Camera.h"
#include "Light.h"
#include "PointLight.h"
#include "DirectionLight.h"
#include "Spotlight.h"
#include "Shader.h"
#include "Model.h"
#include "DrawableModel.h"
#include "Scene.h"

#include <cstdlib>
#include <ctime>


class Application
{
private:
	GLFWwindow* window;
	static Application* app_instance;
	Camera* camera;
	std::vector<Light*> lights;
	std::vector<PointLight*> p_lights;
	std::vector<DirectionLight*> d_lights;
	std::vector<Spotlight*> s_lights;
	std::vector<Shader*> shaders;
	std::unordered_map<std::string, Model*> models_map;
	std::unordered_map<std::string, Shader*> shaders_map;
	std::vector<DrawableModel*> d_models;
	Scene* scene;
public:
	Application();
	~Application() = default;
	void Initialization();
	void CreateShaders();
	void CreateModels();
	void Run();
	static void error_callback(int error, const char* description);
	static void window_focus_callback(GLFWwindow* window, int focused);
	static void window_iconify_callback(GLFWwindow* window, int iconified);
	static void window_size_callback(GLFWwindow* window, int width, int height);
	static void cursor_callback(GLFWwindow* window, double x, double y);
	static void button_callback(GLFWwindow* window, int button, int action, int mode);
};

