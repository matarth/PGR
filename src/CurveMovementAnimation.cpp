#include "CurveMovementAnimation.h"


glm::vec3 curveLeadingPoints[] = {
	glm::vec3( 1.2f, 0.3f,  0.0f),

	glm::vec3(1.0f,  -0.80f, 0.0f),
	glm::vec3(0.7f,  -2.0f, 0.0f),
	glm::vec3(-1.0f,  -2.0f, 0.0f),
	glm::vec3(-1.5f, -0.5f, 0.0f),
	glm::vec3(-2.0f, 0.0f, 0.0f),

	glm::vec3( -1.0f,  0.8f, 0.0f),

	glm::vec3( 0.0f,  1.1f, 0.0f),
	glm::vec3( 0.7f,  1.9f, 0.0f),
	glm::vec3( 1.8f,  2.4f, 0.0f),
	glm::vec3( 2.0f, 2.0f, 0.0f),
	glm::vec3( 2.0f, 1.7f, 0.0f)
};


CurveMovementAnimation::CurveMovementAnimation(void)
{
}

CurveMovementAnimation::CurveMovementAnimation(glm::vec3 startingPosition){
	this->startingPosition = startingPosition;
	this->numberOfLeadingPoints = 12;
}


CurveMovementAnimation::~CurveMovementAnimation(void)
{
}

void CurveMovementAnimation::updateObject(SceneObject* object, float t){

	float tt = t - ((int) t);

	int wholeT = (int) t;
	wholeT = wholeT % numberOfLeadingPoints;
	
	t = wholeT + (t - (int) t);

	const float tt2 = tt*tt;
	const float tt3 = tt2*tt;

	//printf("wholeT %d\n", wholeT);

	glm::vec3 p1 = curveLeadingPoints[(wholeT + 0) % numberOfLeadingPoints];
	glm::vec3 p2 = curveLeadingPoints[(wholeT + 1) % numberOfLeadingPoints];
	glm::vec3 p3 = curveLeadingPoints[(wholeT + 2) % numberOfLeadingPoints];
	glm::vec3 p4 = curveLeadingPoints[(wholeT + 3) % numberOfLeadingPoints];
	/*
	printf("%d, %d, %d, %d\n", (wholeT + 1) % numberOfLeadingPoints,
								(wholeT + 2) % numberOfLeadingPoints,
								(wholeT + 3) % numberOfLeadingPoints,
								(wholeT + 4) % numberOfLeadingPoints);
*/
	//tt = tt % numberOfLeadingPoints;

	glm::vec3 newPosition = p1 * (-tt3 + 2.0f*tt2 - tt);
	newPosition += p2 * (3.0f*tt3 - 5.0f*tt2 + 2.0f);
	newPosition += p3 * (-3.0f*tt3 + 4.0f*tt2 + tt);
	newPosition += p4 * (tt3 - tt2);

	object->translateTo(newPosition + this->startingPosition);
	//object->lookingAt = glm::vec3(50.0f, 0.0f, 0.0f);

	glm::vec3 newDirection = p1 * (-3.0f*tt2 + 4.0f*tt -1.0f);
	newDirection += p2 * (9.0f*tt2 - 10.0f*tt);
	newDirection += p3 * (-9.0f*tt2 + 8.0f*tt + 1.0f);
	newDirection += p4 * (3.0f*tt2 - 2.0f*tt);

	newDirection = glm::normalize(newDirection);

	object->lookAt(object->position + newDirection);

}


glm::vec3 CurveMovementAnimation::computePosition(float t){
	return(glm::vec3(0.0f));
}

void CurveMovementAnimation::getSegmentPoints(glm::vec3 *p1, glm::vec3 *p2, glm::vec3 *p3, glm::vec3 *p4, float t){
	int tt = (int) t;

	tt += 2*numberOfLeadingPoints;
}
