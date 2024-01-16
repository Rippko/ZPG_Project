#include "Scene.h"
#include "SkyBox.h"

#include "ModelLoader.h"
#include "./Models/skycube.h"

Scene::Scene(std::unordered_map<std::string, Model*> models_map, std::unordered_map<std::string, Shader*> shaders_map)
{
	this->models_map = models_map;
	this->shaders_map = shaders_map;
	this->CreateSkybox();
}

void Scene::CreateSkybox()
{
	std::vector<float> skybox = std::vector<float>(std::begin(skycube), std::end(skycube));
	SkyBox* skyTex = new SkyBox("../Project_ZPG_FIU0013/posx.png",
		"../Project_ZPG_FIU0013/negx.png",
		"../Project_ZPG_FIU0013/posy.png",
		"../Project_ZPG_FIU0013/negy.png",
		"../Project_ZPG_FIU0013/posz.png",
		"../Project_ZPG_FIU0013/negz.png");

	Material* skyMat = new Material(glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(0.5f, 0.5f, 0.5f), 32.0f, skyTex);

	TransformationComposite* sky_ts = new TransformationComposite();

	this->sky_box = new DrawableModel(new SkyboxModel(skybox), this->shaders_map["skybox_shader"], sky_ts, skyMat);
}

void Scene::Phong(std::vector<DrawableModel*>& d_models)
{
	float shininess = 32;
	float shininess2 = 1;
	Material* material = new Material(glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(0.2f, 0.2f, 0.2f),
		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(0.5f, 0.5f, 0.5f), 32);
	Material* material2 = new Material(glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(0.2f, 0.2f, 0.2f),
		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(0.5f, 0.5f, 0.5f), 1);

	d_models.clear();

	TransformationComposite* sphere_ts = new TransformationComposite();
	TransformationComposite* sphere2_ts = new TransformationComposite();
	TransformationComposite* sphere3_ts = new TransformationComposite();
	TransformationComposite* sphere4_ts = new TransformationComposite();

	Rotation* rotation = new Rotation(0.5f, glm::vec3(0.0f, 1.0f, 0.0f), true);
	Scale* scale = new Scale(0.1f, false);
	Translation* translation_right = new Translation(glm::vec3(2.0f, 0.0f, 0.0f), false); //move to right
	Translation* translation_left = new Translation(glm::vec3(-2.0f, 0.0f, 0.0f), false); //move to left
	Translation* translation_up = new Translation(glm::vec3(0.0f, 2.0f, 0.0f), false);
	Translation* translation_down = new Translation(glm::vec3(0.0f, -2.0f, 0.0f), false);

	sphere_ts->Add(translation_right);
	sphere_ts->Add(rotation);

	sphere2_ts->Add(translation_left);

	sphere3_ts->Add(translation_down);

	sphere4_ts->Add(translation_up);

	DrawableModel* d_sphere = new DrawableModel(models_map["sphere"], shaders_map["blinn"], sphere_ts, material);
	d_models.push_back(d_sphere);

	DrawableModel* d_sphere2 = new DrawableModel(models_map["sphere"], shaders_map["blinn"], sphere2_ts, material2);
	d_models.push_back(d_sphere2);

	DrawableModel* d_sphere3 = new DrawableModel(models_map["sphere"], shaders_map["lightning_shader"], sphere3_ts, material);
	d_models.push_back(d_sphere3);

	DrawableModel* d_sphere4 = new DrawableModel(models_map["sphere"], shaders_map["lightning_shader"], sphere4_ts, material);
	d_models.push_back(d_sphere4);
}

void Scene::SolarSystem(std::vector<DrawableModel*>& d_models)
{
	Material* material = new Material(glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(0.2f, 0.2f, 0.2f),
		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(0.5f, 0.5f, 0.5f), 32);
	Material* material2 = new Material(glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(0.2f, 0.2f, 0.2f),
		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(0.5f, 0.5f, 0.5f), 1);

	d_models.clear();

	Rotation* rotation = new Rotation(0.5f, glm::vec3(0.0f, -1.0f, 0.0f), true);
	Rotation* rotation2 = new Rotation(0.4f, glm::vec3(0.0f, -1.0f, 0.0f), true);
	Rotation* rotation3 = new Rotation(3.0f, glm::vec3(0.0f, 1.0f, 0.0f), true);
	Scale* sun_scale = new Scale(1.2f, false);
	Scale* earth_scale = new Scale(0.5f, false);
	Scale* moon_scale = new Scale(0.2f, false);

	TransformationComposite* sun_ts = new TransformationComposite();
	sun_ts->Add(rotation);
	DrawableModel* sun = new DrawableModel(models_map["sphere"], shaders_map["sun_shader"], sun_ts, material);
	d_models.push_back(sun);

	TransformationComposite* earth_ts = new TransformationComposite();
	earth_ts->Add(rotation2);
	earth_ts->Add(new Translation(glm::vec3(-5.0f, 0.0f, 0.0f), false));
	earth_ts->Add(earth_scale);
	DrawableModel* earth = new DrawableModel(models_map["sphere"], shaders_map["lightning_shader"], earth_ts, material);
	d_models.push_back(earth);


	TransformationComposite* moon_ts = new TransformationComposite();
	moon_ts->Add(earth_ts);
	moon_ts->Add(rotation3);
	moon_ts->Add(new Translation(glm::vec3(-2.0f, 0.0f, 0.0f), false));
	
	moon_ts->Add(moon_scale);
	DrawableModel* moon = new DrawableModel(models_map["sphere"], shaders_map["lightning_shader"], moon_ts, material);
	d_models.push_back(moon);
}

void Scene::Forest(std::vector<DrawableModel*>& d_models)
{
	d_models.clear();
	Texture* houseTex = new Texture("../Project_ZPG_FIU0013/ObjModels/HouseModel/model.png", 1);
	Material* houseMat = new Material(glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(0.5f, 0.5f, 0.5f), 32.0f, houseTex);
	TransformationComposite* house_ts = new TransformationComposite();
	house_ts->Add(new Translation(glm::vec3(30.0f, 0.0f, 30.0f), false));
	house_ts->Add(new Scale(0.5f, false));

	DrawableModel* house = new DrawableModel(models_map["house"], shaders_map["lightning_shader"], house_ts, houseMat);
	d_models.push_back(house);

	Texture* cottageTex = new Texture("../Project_ZPG_FIU0013/ObjModels/Cottage/Cottage_Texture.jpg", 1);
	Material* cottageMat = new Material(glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(0.5f, 0.5f, 0.5f), 32.0f, cottageTex);
	TransformationComposite* cottage_ts = new TransformationComposite();
	cottage_ts->Add(new Translation(glm::vec3(20.0f, 0.0f, 20.0f), false));
	cottage_ts->Add(new Rotation(-90.0f, glm::vec3(0.0f, 1.0f, 0.0f), false));
	cottage_ts->Add(new Scale(0.05f, false));

	DrawableModel* cottage = new DrawableModel(models_map["cottage"], shaders_map["lightning_shader"], cottage_ts, cottageMat);
	d_models.push_back(cottage);

	Texture* zombieTex = new Texture("../Project_ZPG_FIU0013/ObjModels/Zombie/zombie.png", 1);
	Material* zombieMat = new Material(glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(0.5f, 0.5f, 0.5f), 32.0f, zombieTex);

	for (int i = 0; i < 20; i++) {
		float randomFloat = 1.0f + static_cast<float>(std::rand()) / RAND_MAX * 59.0f;
		float randomFloat2 = 1.0f + static_cast<float>(std::rand()) / RAND_MAX * 59.0f;
		float randomScale = 0.2f + static_cast<float>(std::rand()) / RAND_MAX;
		TransformationComposite* zombie_ts = new TransformationComposite();
		zombie_ts->Add(new Translation(glm::vec3(randomFloat, 0.0f, randomFloat2), false));
		zombie_ts->Add(new Scale(randomScale, false));
		TransformationComposite* bush_dynamic_transformations = new TransformationComposite();
		DrawableModel* zombie = new DrawableModel(models_map["zombie"], shaders_map["lightning_shader"], zombie_ts, zombieMat);
		d_models.push_back(zombie);
	}
	
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	Texture* plainTex = new Texture("grass.png", 10);
	Material* texMat = new Material(glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(0.5f, 0.5f, 0.5f), 32.0f, plainTex);

	TransformationComposite* plain_ts = new TransformationComposite();
	plain_ts->Add(new Translation(glm::vec3(30.0f, 0.0f, 30.0f), false));
	plain_ts->Add(new Scale(30.0f, false));

	DrawableModel* plain = new DrawableModel(models_map["textured_plain"], shaders_map["lightning_shader"], plain_ts, texMat);
	d_models.push_back(plain);
	
	Material* material = new Material();

	Material* giftMat = new Material(glm::vec3(1.0f, 0.0f, 0.5f),
		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(0.5f, 0.5f, 0.5f), 32.0f);

	Material* bushMat = new Material(glm::vec3(0.8f, 0.8f, 0.5f),
		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(0.5f, 0.5f, 0.5f), 32.0f);

	Texture* treeTex = new Texture("../Project_ZPG_FIU0013/ObjModels/TexturedTree/tree.png", 1);
	Material* treeMat = new Material(glm::vec3(0.5f, 1.0f, 0.5f),
		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(0.5f, 0.5f, 0.5f), 32.0f, treeTex);

	for (int i = 0; i < 80; i++) {
		float randomFloat = 1.0f + static_cast<float>(std::rand()) / RAND_MAX * 59.0f;
		float randomFloat2 = 1.0f + static_cast<float>(std::rand()) / RAND_MAX * 59.0f;
		float randomScale = 0.01f + static_cast<float>(std::rand()) / RAND_MAX * 0.3f;
		TransformationComposite* tree_ts = new TransformationComposite();
		Translation* position = new Translation(glm::vec3(randomFloat, 0.0f, randomFloat2), false);
		Scale* size = new Scale(randomScale, false);
		tree_ts->Add(position);
		tree_ts->Add(size);
		TransformationComposite* tree_dynamic_transformations = new TransformationComposite();
		DrawableModel* tree = new DrawableModel(models_map["tex_tree"], shaders_map["lightning_shader"], tree_ts, treeMat);
		d_models.push_back(tree);
	}
	for (int i = 0; i < 30; i++) {
		float randomFloat = 1.0f + static_cast<float>(std::rand()) / RAND_MAX * 59.0f;
		float randomFloat2 = 1.0f + static_cast<float>(std::rand()) / RAND_MAX * 59.0f;
		float randomScale = 0.5f + static_cast<float>(std::rand()) / RAND_MAX;
		TransformationComposite* bush_ts = new TransformationComposite();
		Translation* position = new Translation(glm::vec3(randomFloat, 0.0f, randomFloat2), false);
		Scale* size = new Scale(randomScale, false);
		bush_ts->Add(position);
		bush_ts->Add(size);
		TransformationComposite* bush_dynamic_transformations = new TransformationComposite();
		DrawableModel* bush = new DrawableModel(models_map["bush"], shaders_map["lightning_shader"], bush_ts, bushMat);
		d_models.push_back(bush);
	}
	
	for (int i = 0; i < 15; i++) {
		float randomFloat = 30.0f + static_cast<float>(std::rand()) / RAND_MAX * 19.0f;
		float randomFloat2 = 30.0f + static_cast<float>(std::rand()) / RAND_MAX * 19.0f;
		float randomScale = 0.2f + static_cast<float>(std::rand()) / RAND_MAX;
		TransformationComposite* suzi_ts = new TransformationComposite();
		Translation* position = new Translation(glm::vec3(randomFloat, 1.0f, randomFloat2), false);
		Scale* size = new Scale(randomScale, false);
		suzi_ts->Add(position);
		suzi_ts->Add(size);
		TransformationComposite* bush_dynamic_transformations = new TransformationComposite();
		DrawableModel* suzi = new DrawableModel(models_map["smooth_suzi"], shaders_map["lightning_shader"], suzi_ts, material);
		d_models.push_back(suzi);
	}
	for (int i = 0; i < 50; i++) {
		float randomFloat = 1.0f + static_cast<float>(std::rand()) / RAND_MAX * 59.0f;
		float randomFloat2 = 1.0f + static_cast<float>(std::rand()) / RAND_MAX * 59.0f;
		float randomScale = 0.5f + static_cast<float>(std::rand()) / RAND_MAX;
		TransformationComposite* gift_ts = new TransformationComposite();
		Translation* position = new Translation(glm::vec3(randomFloat, 0.0f, randomFloat2), false);
		Scale* size = new Scale(randomScale, false);
		gift_ts->Add(position);
		gift_ts->Add(size);
		TransformationComposite* bush_dynamic_transformations = new TransformationComposite();
		DrawableModel* gift = new DrawableModel(models_map["gift"], shaders_map["lightning_shader"], gift_ts, giftMat);
		d_models.push_back(gift);
	}

	TransformationComposite* gift_spec_ts = new TransformationComposite();
	gift_spec_ts->Add(new Translation(glm::vec3(25.0f, 0.0f, 20.0f), false));
	DrawableModel* gift_spec = new DrawableModel(models_map["gift"], shaders_map["lightning_shader"], gift_spec_ts, giftMat);
	d_models.push_back(gift_spec);

	TransformationComposite* line_sphere_ts = new TransformationComposite();
	line_sphere_ts->Add(new Translation(glm::vec3(30.0f, 0.5f, 20.0f), false));
	line_sphere_ts->Add(new LineMovement(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
	line_sphere_ts->Add(new Scale(0.3f, false));

	DrawableModel* sphere_line = new DrawableModel(models_map["sphere"], shaders_map["lightning_shader"], line_sphere_ts, material);
	d_models.push_back(sphere_line);

	glm::mat4 A = glm::mat4(glm::vec4(-1.0, 3.0, -3.0, 1.0),
							glm::vec4(3.0, -6.0, 3.0, 0),
							glm::vec4(-3.0, 3.0, 0, 0),
							glm::vec4(1, 0, 0, 0));

	glm::mat4x3 B = glm::mat4x3(glm::vec3(-1, 0, 0),
								glm::vec3(0, 2, 0),
								glm::vec3(0, 1, 0),
								glm::vec3(1, 0, 0));

	glm::mat3x3 C = glm::mat3x3(glm::vec3(3, 0, 0), glm::vec3(0, 1, 0), glm::vec3(1, 0, 0));

	TransformationComposite* beziere_sphere_ts = new TransformationComposite();
	beziere_sphere_ts->Add(new Translation(glm::vec3(35.0f, 0.5f, 25.0f), false));
	BezierMovement* b_movement = new BezierMovement(B, A);
	b_movement->AddPoints(C);
	beziere_sphere_ts->Add(b_movement);
	beziere_sphere_ts->Add(new Scale(0.3f, false));

	DrawableModel* sphere_beziere = new DrawableModel(models_map["sphere"], shaders_map["lightning_shader"], beziere_sphere_ts, material);
	d_models.push_back(sphere_beziere);
}

void Scene::drawTree(glm::vec3 position, std::unordered_map<std::string, Shader*> shaders_map, std::vector<DrawableModel*>& d_models)
{
	Texture* treeTex = new Texture("../Project_ZPG_FIU0013/ObjModels/TexturedTree/tree.png", 1);
	Material* treeMat = new Material(glm::vec3(0.5f, 1.0f, 0.5f),
		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(0.5f, 0.5f, 0.5f), 32.0f, treeTex);

	float randomScale = 0.01f + static_cast<float>(std::rand()) / RAND_MAX * 0.3f;
	TransformationComposite* tree_ts = new TransformationComposite();
	Scale* size = new Scale(randomScale, false);
	tree_ts->Add(new Translation(position, false));
	tree_ts->Add(size);
	DrawableModel* tree = new DrawableModel(models_map["tex_tree"], shaders_map["lightning_shader"], tree_ts, treeMat);
	d_models.push_back(tree);
}

void Scene::deleteObject(int index, std::vector<DrawableModel*>& d_models)
{
	printf("index: %d\n", index);
	d_models.erase(d_models.begin() + index);
}
