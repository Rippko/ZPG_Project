#pragma once
#include <vector>
#include <string>
class ModelLoader
{
public:
	ModelLoader();
	~ModelLoader() = default;
	std::vector<float> loadModel(std::string path, int& count);
};

