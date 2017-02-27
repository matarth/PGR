//----------------------------------------------------------------------------------------
/**
 * \file       kadrnmat.cpp
 * \author     Matouš Kadrnoška
 * \date       2016/31/05
 *
 *  ¨Class for the representation of light. Stores all needed data.
 *
*/
//----------------------------------------------------------------------------------------


#pragma once
#include "SceneObject.h"

class Light: public SceneObject
{
public:

	int lightType;
	float spotLightAngle;
	float intensity;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	Light(void);
	~Light(void);
};

