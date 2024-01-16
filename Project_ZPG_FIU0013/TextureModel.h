#pragma once
/**
 *
 * @brief TextureModel header file
 *
 * @author Adam Fiury
 *
 * @year 2023
 **/
#include "Model.h"
class TextureModel : public Model
{
private:
	TextureModel();
public:
	TextureModel(std::vector<float> points);
	~TextureModel() = default;
	void drawArrays() override;
};

