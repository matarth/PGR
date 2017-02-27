#include "FollowObjectAnimation.h"


FollowObjectAnimation::FollowObjectAnimation(SceneObject* follower, SceneObject* prey, float distance){
	this->follower = follower;
	this->prey = prey;
	this->distance = distance;
}

FollowObjectAnimation::~FollowObjectAnimation(void)
{
}

void FollowObjectAnimation::updateObject(SceneObject* object, float time){

	if(object == NULL || this->prey == NULL || this->follower == NULL){
		return;
	}
	
	glm::vec3 newPosition;
	glm::vec3 preyPosition = this->prey->position;
	glm::vec3 preyDirection = this->prey->getDirection();



	newPosition = preyPosition + this->distance*preyDirection;
		
	this->follower->translateTo(newPosition);
	this->follower->lookAt(preyPosition);


}