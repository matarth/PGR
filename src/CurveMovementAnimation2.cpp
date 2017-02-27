#include "CurveMovementAnimation2.h"
#include "NewCamera.h"


int numberOfLeadingPoints = 13;

glm::vec3 curveLeadingPoints2[] = {
	glm::vec3( -30.6f, 2.6f,  4.6f),
	glm::vec3(-21.4f,  0.5f, -4.4f),
	glm::vec3(-9.8f,  -4.3f, -18.8f),
	glm::vec3(5.9f,  2.1f, -9.6f),
	glm::vec3(13.6f, 2.7f, 9.7f),
	glm::vec3(-8.5f, -1.9f, 24.6f),
	glm::vec3( -23.5f,  7.6f, -6.2f),
	glm::vec3( -9.9f,  7.4f, -37.1f),
	glm::vec3( 5.9f,  24.6f, -41.4f),
	glm::vec3( 16.0f,  12.4f, -10.8f),
	glm::vec3( 8.9f, -0.7f, 14.4f),
	glm::vec3(15.0f, 1.0f, 9.0f),
	glm::vec3(25.0f, 1.9f, 6.0f),
};


CurveMovementAnimation2::CurveMovementAnimation2(void)
{
}

CurveMovementAnimation2::CurveMovementAnimation2(glm::vec3 startingPosition){
	this->startingPosition = startingPosition;
	this->numberOfLeadingPoints = 11;
}


CurveMovementAnimation2::~CurveMovementAnimation2(void)
{
}

void CurveMovementAnimation2::updateObject(SceneObject* object, float t){

	float tt = t - ((int) t);

	int wholeT = (int) t;
	wholeT = wholeT % numberOfLeadingPoints;
	
	t = wholeT + (t - (int) t);

	const float tt2 = tt*tt;
	const float tt3 = tt2*tt;

	//printf("wholeT %d\n", wholeT);

	glm::vec3 p1 = curveLeadingPoints2[(wholeT + 0) % numberOfLeadingPoints];
	glm::vec3 p2 = curveLeadingPoints2[(wholeT + 1) % numberOfLeadingPoints];
	glm::vec3 p3 = curveLeadingPoints2[(wholeT + 2) % numberOfLeadingPoints];
	glm::vec3 p4 = curveLeadingPoints2[(wholeT + 3) % numberOfLeadingPoints];
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

	newPosition = newPosition/(2.0f);

	object->translateTo(newPosition + this->startingPosition);
	//object->lookingAt = glm::vec3(50.0f, 0.0f, 0.0f);

	glm::vec3 newDirection = p1 * (-3.0f*tt2 + 4.0f*tt -1.0f);
	newDirection += p2 * (9.0f*tt2 - 10.0f*tt);
	newDirection += p3 * (-9.0f*tt2 + 8.0f*tt + 1.0f);
	newDirection += p4 * (3.0f*tt2 - 2.0f*tt);

	newDirection = glm::normalize(newDirection);

	object->lookAt(object->position + newDirection);
	object->yaw(-90.0f);

}


glm::vec3 CurveMovementAnimation2::computePosition(float t){
	return(glm::vec3(0.0f));
}

void CurveMovementAnimation2::getSegmentPoints(glm::vec3 *p1, glm::vec3 *p2, glm::vec3 *p3, glm::vec3 *p4, float t){
	int tt = (int) t;

	tt += 2*numberOfLeadingPoints;
}
