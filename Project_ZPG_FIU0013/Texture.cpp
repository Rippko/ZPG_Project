#include "Texture.h"


Texture::Texture()
{
}

Texture::Texture(std::string path, int scale)
{
    glActiveTexture(GL_TEXTURE0);
    this->texture_unitID = GL_TEXTURE0;
    this->scalingConstant = scale;
    this->textureID = SOIL_load_OGL_texture(path.c_str(), SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    if (this->textureID == NULL) {
        printf("An error occurred while loading image.");
        exit(EXIT_FAILURE);
    }
    glBindTexture(GL_TEXTURE_2D, this->textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

}

void Texture::bindTexture()
{
	glBindTexture(GL_TEXTURE_2D, this->textureID);
}
