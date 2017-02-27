
//----------------------------------------------------------------------------------------
/**
 * \file       kadrnmat.cpp
 * \author     Matouš Kadrnoška
 * \date       2016/31/05
 *
 *  Base class for object. Takes care of turning and moving.
 *
*/
//----------------------------------------------------------------------------------------



#pragma once
#include "pgr.h"
#include "Animation.h"

class Animation;

class SceneObject
{
public: 

	glm::vec3 position;
	glm::quat rotationQuaternion;
	glm::vec3 color;
	
	float size;
	bool isCamera;

	std::vector<Animation*> animations;

	glm::vec2 textureMovement;

	void addTexture(char*);

	SceneObject(void);
	~SceneObject(void);

	void pitch(float);
	void yaw(float);
	void roll(float);


	glm::vec3 getDirection();
	glm::vec3 getLookingAt();
	glm::vec3 getUpVector();

	// Movement functions
	void translateBy(glm::vec3 direction);
	void translateTo(glm::vec3 position);

	void strafeRight(float);
	void strafeLeft(float);
	void moveForward(float);
	void moveBackward(float);
	void flyUp(float);
	void flyDown(float);

	void scale(float newSize);
	void rotate(float angle, glm::vec3 rotationAxis);
	void reset();

	float getYaw();
	float getRoll();
	float getPitch();

	/**
	 * changes objects direction towards point  given in parameter
	 */
	void lookAt(glm::vec3); 


	void updateAnimation(float);
	void addAnimation(Animation*);

};

