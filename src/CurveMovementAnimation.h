//----------------------------------------------------------------------------------------
/**
 * \file       kadrnmat.cpp
 * \author     Matouš Kadrnoška
 * \date       2016/31/05
 *
 *  Class for moving model on a curve.
 *
*/
//----------------------------------------------------------------------------------------


#pragma once
#include "Animation.h"

class CurveMovementAnimation: public Animation
{
public:
	int numberOfLeadingPoints;

	CurveMovementAnimation(void);
	CurveMovementAnimation(glm::vec3 startingPosition);
	~CurveMovementAnimation(void);

	virtual void updateObject(SceneObject*, float);

private:

	void getSegmentPoints(glm::vec3*, glm::vec3*, glm::vec3*, glm::vec3*, float);

	glm::vec3 computePosition(float t);
	glm::vec3 startingPosition;
};

