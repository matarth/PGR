#pragma once
#include "NewModel.h"
class SkyBox: public NewModel
{
public:
	SkyBox(void);
	~SkyBox(void);

	bool loadCubeMap(char*);

	virtual void loadShaders();
	virtual glm::mat4 getModelMatrix();

	GLuint coordLocation;
	GLuint inversePVLocation;
};

