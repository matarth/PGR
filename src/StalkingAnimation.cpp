#include "StalkingAnimation.h"


StalkingAnimation::StalkingAnimation(void)
{
}

StalkingAnimation::StalkingAnimation(SceneObject* stalker, SceneObject* prey){
	this->prey = prey;
	this->stalker = stalker;
}

StalkingAnimation::~StalkingAnimation(void)
{
}


void StalkingAnimation::updateObject(SceneObject* object, float t){
	this->stalker->lookAt(this->prey->position);
}
