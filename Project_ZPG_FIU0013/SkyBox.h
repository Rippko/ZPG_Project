#pragma once
/**
 *
 * @brief SkyBox header file
 *
 * @author Adam Fiury
 *
 * @year 2023
 **/
#include "Texture.h"

class SkyBox : public Texture
{
public:
	SkyBox(std::string pathPosX, std::string pathNegX, std::string pathPosY, std::string pathNegY, std::string pathPosZ, std::string pathNegZ);
	~SkyBox() = default;
	void bindTexture() override;
};

