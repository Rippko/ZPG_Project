#include "DrawableModel.h"
#include "TextureModel.h"
#include "SkyboxModel.h"

DrawableModel::DrawableModel(Model* model, Shader* shader, TransformationComposite* transformation_comp, Material* material)
{
	this->model = model;
	this->shader = shader;
	this->matrix = glm::mat4(1.f);
	this->transformation_comp = transformation_comp;
	this->material = material;
}

void DrawableModel::Render()
{
	this->shader->UseShaderProgram();
	this->shader->LinkDataToShader("modelMatrix", matrix);
	this->shader->LinkDataToShader("material.ambientColor", material->ambientColor);
	this->shader->LinkDataToShader("material.diffuseColor", material->diffuseColor);
	this->shader->LinkDataToShader("material.specularColor", material->specularColor);
	this->shader->LinkDataToShader("material.shininess", material->shininess);
	this->shader->LinkDataToShader("material.objectColor", material->objectColor);

	TextureModel* textureModel = dynamic_cast<TextureModel*>(model);
	SkyboxModel* skyModel = dynamic_cast<SkyboxModel*>(model);

	if (textureModel) {
		this->shader->LinkDataToShader("textureUnitID", material->texture->texture_unitID);
		this->shader->LinkDataToShader("scalingConstant", material->texture->scalingConstant);
		this->shader->LinkDataToShader("hasTexture", 1);
		this->material->texture->bindTexture();
	}
	else if (skyModel) {
		this->shader->LinkDataToShader("textureUnitID", material->texture->texture_unitID);
		this->material->texture->bindTexture();
	}
	else {
		this->shader->LinkDataToShader("hasTexture", 0);
	}

	this->model->AssignVAO();

	if (skyModel) {
		this->model->drawSkyBox();
	}
	else {
		this->model->drawArrays();
	}
}

void DrawableModel::Update()
{
	matrix = transformation_comp->TransformMatrix();
}

Model* DrawableModel::GetModel()
{
	return this->model;
}
