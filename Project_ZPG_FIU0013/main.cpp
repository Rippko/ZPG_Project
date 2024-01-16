/**
 *
 * @brief Main
 *
 * @author Adam Fiury
 *
 * @year 2023
 **/
#include "Application.h"

int main(void) {
	Application* app = new Application();
	app->Initialization();
	app->CreateShaders();
	app->CreateModels();
	app->Run();
}