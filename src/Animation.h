//----------------------------------------------------------------------------------------
/**
 * \file       kadrnmat.cpp
 * \author     Matou� Kadrno�ka
 * \date       2016/31/05
 *
 *  Base class template for animations
 *
*/
//----------------------------------------------------------------------------------------


#pragma once
#include "SceneObject.h"

class SceneObject;

class Animation
{
public:
	Animation(void);
	~Animation(void);

	virtual void updateObject(SceneObject*, float) = 0;

};

