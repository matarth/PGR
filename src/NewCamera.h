//----------------------------------------------------------------------------------------
/**
 * \file       kadrnmat.cpp
 * \author     Matouš Kadrnoška
 * \date       2016/31/05
 *
 *  Class representing a camera in the scene.
 *
*/
//----------------------------------------------------------------------------------------


#pragma once
#include "SceneObject.h"

class NewCamera: public SceneObject
{

private:

	glm::mat4 projectionMatrix;

public:

	glm::mat4 getViewMatrix();

	NewCamera(void);
	~NewCamera(void);

	glm::mat4 getProjectionMatrix();

	virtual void strafeRight(float);
	virtual void strafeLeft(float);
	virtual void moveForward(float);
	virtual void moveBackward(float);
	virtual void flyUp(float);
	virtual void flyDown(float);

	virtual void pitch(float);
	virtual void yaw(float);
	virtual void roll(float);
	virtual void lookAt(glm::vec3);
};

