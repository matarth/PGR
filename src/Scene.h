//----------------------------------------------------------------------------------------
/**
 * \file       kadrnmat.cpp
 * \author     Matouš Kadrnoška
 * \date       2016/31/05
 *
 *  Class for the scene, takes care of animations and object and the drawing.
 *
*/
//----------------------------------------------------------------------------------------


#pragma once
#include "NewModel.h"
#include "NewCamera.h"
#include "Light.h"
#include "SkyBox.h"

class Scene
{
private:

	std::vector<NewModel*> models;
	std::vector<Light*> directionalLights;
	std::vector<Light*> spotLights;
	std::vector<Light*> pointLights;

	glm::mat4 projectionMatrix;	

	NewCamera *activeCamera;

	void drawObject(NewModel*);

public:
	Scene(void);
	~Scene(void);

	void checkColisions();

	SkyBox* skybox;

	NewModel* terrain;

	void setActiveCamera(NewCamera*);

	void addModel(NewModel*);
	
	void addDirectionalLight(Light*);
	void addSpotLight(Light*);
	void addPointLight(Light*);

	void drawScene();
	void drawSkyBox();
	NewModel* getModelById(int modelID);

	void updateAnimations(float);
};

