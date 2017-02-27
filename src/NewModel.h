//----------------------------------------------------------------------------------------
/**
 * \file       kadrnmat.cpp
 * \author     Matouš Kadrnoška
 * \date       2016/31/05
 *
 *  Class representing all drawable objects in the scene.
 *
*/
//----------------------------------------------------------------------------------------


#pragma once
#include "SceneObject.h"
#include "Animation.h"


class NewModel: public SceneObject
{



public:

	GLuint vbo;
	GLuint eao;
	GLuint vao;
	GLuint texture;
	GLuint texSamplerLocation;

	glm::vec3 materialAmbient;
	glm::vec3 materialDiffuse;
	glm::vec3 materialSpecular;
	float materialShininess;

	bool useTexture;
	int modelID;

	GLuint shaderProgram;

	char *dataFile;

	NewModel(void);
	NewModel(char*);
	~NewModel(void);

	int numberOfVertices;
	int numberOfFaces;

	glm::mat4 getModelMatrix();

	virtual void addTexture(char*);

	virtual void scale(float);

protected:

	void loadShaders();
	void init();
	bool loadModelFromSource(char *); // loads vao, vbo and eao from sourceFile to buffers.
	void connectDataToShaders(); // sends buffered data to shaders

protected:

	std::string vertexShaderSrc;
	std::string fragmentShaderSrc;

};