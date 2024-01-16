#pragma once
/**
 *
 * @brief Texture header file
 *
 * @author Adam Fiury
 *
 * @year 2023
 **/
//Include GLFW
#include <GL/glew.h>
#include <string>
#include "SOIL.h"
class Texture
{
public:
	GLuint textureID;
	int texture_unitID;
	int scalingConstant;
	Texture();
	Texture(std::string path, int scale);
	virtual void bindTexture();
};

