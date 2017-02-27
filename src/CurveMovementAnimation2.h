#pragma once
#include "Animation.h"

class CurveMovementAnimation2: public Animation
{
public:

	int numberOfLeadingPoints;
	CurveMovementAnimation2(void);
	CurveMovementAnimation2(glm::vec3 startingPosition);
	~CurveMovementAnimation2(void);

	virtual void updateObject(SceneObject*, float);

private:

	void getSegmentPoints(glm::vec3*, glm::vec3*, glm::vec3*, glm::vec3*, float);

	glm::vec3 computePosition(float t);
	glm::vec3 startingPosition;
};

