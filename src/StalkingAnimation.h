#pragma once
#include "Animation.h"
class StalkingAnimation: public Animation
{
public:

	SceneObject* prey;
	SceneObject* stalker;

	StalkingAnimation(void);
	StalkingAnimation(SceneObject*, SceneObject* prey);
	~StalkingAnimation(void);

	virtual void updateObject(SceneObject*, float);
};

