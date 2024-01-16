#include "Application.h"


//transformations
#include "Rotation.h"
#include "Scale.h"
#include "Translation.h"

//lights
#include "Spotlight.h"
#include "PointLight.h"
#include "DirectionLight.h"


#include "SkyboxModel.h"

#include "Scene.h"
#include "SkyBox.h"
#include "ModelLoader.h"

//models
#include "./Models/suzi_flat.h"
#include "./Models/sphere.h"
#include "./Models/tree.h"
#include "./Models/bushes.h"
#include "./Models/plain.h"
#include "./Models/gift.h"
#include "./Models/suzi_smooth.h"
#include "./Models/textured_plain.h"

#include "TextureModel.h"

Application* Application::app_instance = nullptr;
Application::Application() { app_instance = this; }

void Application::error_callback(int error, const char* description) { fputs(description, stderr); }

void Application::window_focus_callback(GLFWwindow* window, int focused) { printf("window_focus_callback \n"); }

void Application::window_iconify_callback(GLFWwindow* window, int iconified) { printf("window_iconify_callback \n"); }

void Application::window_size_callback(GLFWwindow* window, int width, int height) {

	if (app_instance != nullptr) {
		app_instance->camera->setWidthHeight(width, height);
	}
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
}

void Application::cursor_callback(GLFWwindow* window, double x, double y) 
{ 
	if (app_instance != nullptr) {
		int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
		if (state == GLFW_PRESS) {

			glfwSetInputMode(app_instance->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			app_instance->camera->controlCameraWithMouse(x, y);
		}
		else if (state == GLFW_RELEASE) {
			glfwSetInputMode(app_instance->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
	}
}
void Application::button_callback(GLFWwindow* window, int button, int action, int mode)
{	
	if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_1) {
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		GLbyte color[4];
		GLfloat depth;
		GLuint index; // identifikace tìlesa
		int newy = height - y;
		glReadPixels((int)x, newy, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
		glReadPixels((int)x, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
		glReadPixels((int)x, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

		glm::vec3 screenX = glm::vec3(x, newy, depth);
		glm::mat4 view = app_instance->camera->getViewMatrix();
		glm::mat4 projection = app_instance->camera->getProjectionMatrix();
		glm::vec4 viewPort = glm::vec4(0, 0, width, height);
		glm::vec3 pos = glm::unProject(screenX, view, projection, viewPort);

		
		if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS && depth != 1.0f && app_instance->d_models.at(index)->GetModel() == app_instance->models_map["gift"]) {
			printf("Clicked on pixel %f, %f, color %02hhx%02hhx%02hhx%02hhx, depth % f, stencil index % u\n", x, y, color[0], color[1], color[2], color[3], depth, index);
			printf("unProject [%f,%f,%f]\n", pos.x, pos.y, pos.z);
			app_instance->scene->deleteObject((int)index, app_instance->d_models);
		}
		else if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
			printf("Clicked on pixel %f, %f, color %02hhx%02hhx%02hhx%02hhx, depth % f, stencil index % u\n", x, y, color[0], color[1], color[2], color[3], depth, index);
			printf("unProject [%f,%f,%f]\n", pos.x, pos.y, pos.z);
			app_instance->scene->drawTree(pos, app_instance->shaders_map, app_instance->d_models);
		}
	}
}

void Application::Initialization()
{
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	//inicializace konkretni verze
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE,
		GLFW_OPENGL_CORE_PROFILE);
	//inicialization of window in params of the class
	this->window = glfwCreateWindow(1200, 1000, "ZPG", NULL, NULL);
	this->camera = new Camera(this->window);
	
	
	PointLight* p_light = new PointLight();
	p_lights.push_back(p_light);

	PointLight* p_light2 = new PointLight(glm::vec3(30.0f, 1.0f, 25.0f));
	p_lights.push_back(p_light2);

	PointLight* p_light3 = new PointLight(glm::vec3(30.0f, 1.0f, 35.0f));
	p_lights.push_back(p_light3);
	
	PointLight* p_light4 = new PointLight(glm::vec3(10.0f, 1.0f, 10.0f));
	//p_lights.push_back(p_light4);

	PointLight* p_light5 = new PointLight(glm::vec3(0.0f, 0.0f, 0.0f));
	//p_lights.push_back(p_light5);

	
	DirectionLight* d_light = new DirectionLight();
	//d_lights.push_back(d_light);

	Spotlight* s_light = new Spotlight();
	s_lights.push_back(s_light);
	this->camera->SetSpotlight(s_light);

	Spotlight* s_light2 = new Spotlight(glm::vec3(25.0f, 3.0f, 20.0f), glm::vec3(0.0f, -1.0f, 0.0f));
	s_lights.push_back(s_light2);

	glfwSetErrorCallback(error_callback);
	//glfwSetKeyCallback(this->window, key_callback);
	glfwSetCursorPosCallback(this->window, cursor_callback);
	glfwSetWindowSizeCallback(this->window, window_size_callback);
	glfwSetWindowFocusCallback(this->window, window_focus_callback);
	glfwSetMouseButtonCallback(this->window, button_callback);

	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}


	glfwMakeContextCurrent(this->window);
	glfwSwapInterval(1);


	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	// get version info
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);

	int width, height;
	glfwGetFramebufferSize(this->window, &width, &height);
	float ratio = width / (float)height;
	glViewport(0, 0, width, height);
}

void Application::CreateShaders()
{
	this->shaders_map["sun_shader"] = new Shader("phong_vertex_shader.glsl", "sun_fragment_shader.glsl");
	this->shaders_map["skybox_shader"] = new Shader("skybox_vertex.glsl", "skybox_fragment.glsl");
 	this->shaders_map["lightning_shader"] = new Shader("lights_vertex_shader.glsl", "phong_multi_light_fragment.glsl");
	this->shaders_map["blinn"] = new Shader("lights_vertex_shader.glsl", "blinn_multi_light_fragment.glsl");

	for (auto shader : shaders_map) {
		this->camera->addObserver(shader.second);
	}
	for (auto shader : shaders_map) { for (auto light : p_lights) { light->addObserver(shader.second); }
									  for (auto light : d_lights) { light->addObserver(shader.second); }
									  for (auto light : s_lights) { light->addObserver(shader.second); }}
}

void Application::CreateModels()
{
	ModelLoader* md_loader = new ModelLoader();
	int count = 0;
	//creating vector of points and then and creating model object from it

	//Sphere
	std::vector<float> sphere_float = std::vector<float>(std::begin(sphere), std::end(sphere));
	this->models_map["sphere"] = new Model(sphere_float);

	//Tree
	std::vector<float> tree_float = std::vector<float>(std::begin(tree), std::end(tree));
	this->models_map["tree"] = new Model(tree_float);

	//Bush
	std::vector<float> bushes_float = std::vector<float>(std::begin(bushes), std::end(bushes));
	this->models_map["bush"] = new Model(bushes_float);

	//Classic plain
	std::vector<float> plain_float = std::vector<float>(std::begin(plain), std::end(plain));
	this->models_map["plain"] = new Model(plain_float);

	//Suzi flat
	std::vector<float>suzi_float = std::vector<float>(std::begin(suziFlat), std::end(suziFlat));
	this->models_map["suzi"] = new Model(suzi_float);

	//Gift
	std::vector<float>gift_float = std::vector<float>(std::begin(gift), std::end(gift));
	this->models_map["gift"] = new Model(gift_float);

	//Smooth suzi
	std::vector<float>suzi_smooth = std::vector<float>(std::begin(suziSmooth), std::end(suziSmooth));
	this->models_map["smooth_suzi"] = new Model(suzi_smooth);

	//Textured plain
	std::vector<float> plain_tex = std::vector<float>(std::begin(textured_plain), std::end(textured_plain));
	this->models_map["textured_plain"] = new TextureModel(plain_tex);

	//House
	std::vector<float> house_data = md_loader->loadModel("../Project_ZPG_FIU0013/ObjModels/HouseModel/model.obj", count);
	this->models_map["house"] = new TextureModel(house_data);

	//Zombie
	std::vector<float> zombie_data = md_loader->loadModel("../Project_ZPG_FIU0013/ObjModels/Zombie/zombie.obj", count);
	this->models_map["zombie"] = new TextureModel(zombie_data);

	std::vector<float> cottage_data = md_loader->loadModel("../Project_ZPG_FIU0013/ObjModels/Cottage/CottageOBJ.obj", count);
	this->models_map["cottage"] = new TextureModel(cottage_data);

	std::vector<float> textured_tree_data = md_loader->loadModel("../Project_ZPG_FIU0013/ObjModels/TexturedTree/tree.obj", count);
	this->models_map["tex_tree"] = new TextureModel(textured_tree_data);

	this->scene = new Scene(this->models_map, this->shaders_map);

	
	//this->scene->Phong(this->d_models);
	//this->scene->SolarSystem(this->d_models);
	this->scene->Forest(this->d_models);
}
//main core of rendering in my application
void Application::Run()
{	
	float lastTime = glfwGetTime();
	while (!glfwWindowShouldClose(this->window)) {
		float currentTime = glfwGetTime();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;
		// clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		//maintaining observers
		this->camera->moveCamera(deltaTime);

		//rendering skybox first and then clearing z-buffer

		for (int i = 0; i < p_lights.size(); i++) { p_lights[i]->notifyObservers(i); }
		for (int i = 0; i < d_lights.size(); i++) { d_lights[i]->notifyObservers(i); }
		for (int i = 0; i < s_lights.size(); i++) { s_lights[i]->notifyObservers(i); }
		
		this->scene->sky_box->Render();
		this->scene->sky_box->Update();

		glClear(GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		int i = 0;
		for (DrawableModel* d_model : d_models) {
			if (i < 255) {
				glStencilFunc(GL_ALWAYS, i, 0xFF);
			}
			d_model->Update();
			d_model->Render();
			
			i++;
		}

		// update other events like input handling
		glfwPollEvents();
		// put the stuff we’ve been drawing onto the display
		glfwSwapBuffers(this->window);
	}

	glfwDestroyWindow(this->window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}