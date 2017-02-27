//----------------------------------------------------------------------------------------
/**
 * \file       kadrnmat.cpp
 * \author     Matouš Kadrnoška
 * \date       2016/31/05
 *
 *  Class that changes textures on object
 *
*/
//----------------------------------------------------------------------------------------



#pragma once
#include "Animation.h"
class ChangeTexAnimation: public Animation
{
public:

	char *tex1;
	char *tex2;

	GLuint texture1;
	GLuint texture2;

	unsigned int myTime;

	bool b;


	ChangeTexAnimation(void);

	ChangeTexAnimation(char*, char*);

	~ChangeTexAnimation(void);

	virtual void updateObject(SceneObject*, float);
};

