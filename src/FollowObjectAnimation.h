
//----------------------------------------------------------------------------------------
/**
 * \file       kadrnmat.cpp
 * \author     Matouš Kadrnoška
 * \date       2016/31/05
 *
 *  Animation making one object follow another.
 *
*/
//----------------------------------------------------------------------------------------

#pragma once
#include "Animation.h"
class FollowObjectAnimation: public Animation
{

private: 

	SceneObject* follower;
	SceneObject* prey;
	float distance;

public:
	FollowObjectAnimation(void);
	FollowObjectAnimation(SceneObject* follower, SceneObject* prey, float);
	~FollowObjectAnimation(void);

	virtual void updateObject(SceneObject*, float);
};

