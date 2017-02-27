//----------------------------------------------------------------------------------------
/**
 * \file       kadrnmat.cpp
 * \author     Matouš Kadrnoška
 * \date       2016/31/05
 *
 *  Animation rotating model around its X axis.
 *
*/
//----------------------------------------------------------------------------------------



#pragma once
#include "Animation.h"

class PitchAnimation: public Animation
{
public:
	PitchAnimation(void);
	~PitchAnimation(void);

	virtual void updateObject(SceneObject*, float);
};

