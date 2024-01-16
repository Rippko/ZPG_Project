#pragma once
/**
 *
 * @brief SkyboxModel header file
 *
 * @author Adam Fiury
 *
 * @year 2023
 **/
#include "Model.h"
class SkyboxModel : public Model
{
public:
	SkyboxModel(std::vector<float> points);
	~SkyboxModel() = default;
};