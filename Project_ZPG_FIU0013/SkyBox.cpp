#include "SkyBox.h"

SkyBox::SkyBox(std::string pathPosX, std::string pathNegX, std::string pathPosY, std::string pathNegY, std::string pathPosZ, std::string pathNegZ)
{
	this->texture_unitID = GL_TEXTURE1;
	glActiveTexture(GL_TEXTURE0);
	
	this->scalingConstant = 1;

	this->textureID = SOIL_load_OGL_cubemap(pathPosX.c_str(), pathNegX.c_str(), pathPosY.c_str(), pathNegY.c_str(), pathPosZ.c_str(), pathNegZ.c_str(),
		SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	if (this->textureID == -1) {
		printf("An error occurred while loading CubeMap.");
	}
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->textureID);
	
}

void SkyBox::bindTexture()
{
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->textureID);
}
