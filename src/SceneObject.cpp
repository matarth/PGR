#include "SceneObject.h"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>


glm::quat fromtwovectors(glm::vec3, glm::vec3);


SceneObject::SceneObject(void)
{
	this->reset();
}


SceneObject::~SceneObject(void)
{
}

void SceneObject::reset(){
	this->rotationQuaternion = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	this->position = glm::vec3(0.0f);
	this->textureMovement = glm::vec2(0.0f, 0.0f);
	this->isCamera = false;
}

void SceneObject::translateBy(glm::vec3 direction){
	this->position += direction;
}

void SceneObject::translateTo(glm::vec3 position){

	glm::vec3 direction = this->getDirection();

	this->position = position;
	//this->lookAt(position + direction);

}

glm::vec3 SceneObject::getDirection(){

	glm::vec3 direction = glm::vec3(0.0f, 0.0f, 1.0f);

	//direction = glm::vec3(glm::vec4(direction, 1.0f) * this->rotationQuaternion);

	direction = glm::normalize(this->rotationQuaternion * direction);

	return(direction);
}

void SceneObject::strafeRight(float speed){

	glm::vec3 delta = speed * glm::normalize(glm::cross(this->getDirection(), this->getUpVector()));
	this->translateBy(delta);

}

void SceneObject::strafeLeft(float speed){
	this->strafeRight(-speed);
}

void SceneObject::flyUp(float speed){

	glm::vec3 delta = speed * glm::normalize(this->getUpVector());

	this->translateBy(delta);
}

void SceneObject::flyDown(float speed){
	this->flyUp(-speed);
}

void SceneObject::moveForward(float speed){

	glm::vec3 delta = speed * this->getDirection();
	this->translateBy(delta);
}

void SceneObject::moveBackward(float speed){

	this->moveForward(-speed);
}

void SceneObject::pitch(float angle){

	float cosAlpha = cos(glm::radians(angle/2.0f));
	float sinAlpha = sin(glm::radians(angle/2));

	glm::vec3 rotationAxis = this->rotationQuaternion * glm::vec3(1.0f, 0.0f, 0.0f);

	glm::quat rotation = glm::quat(cosAlpha,sinAlpha*rotationAxis.x, sinAlpha*rotationAxis.y, sinAlpha*rotationAxis.z);
	this->rotationQuaternion = rotation * this->rotationQuaternion;
}

void SceneObject::yaw(float angle){

	float cosAlpha = cos(glm::radians(angle/2.0f));
	float sinAlpha = sin(glm::radians(angle/2));

	glm::vec3 rotationAxis = this->getUpVector();

	glm::quat rotation = glm::quat(cosAlpha,sinAlpha*rotationAxis.x, sinAlpha*rotationAxis.y, sinAlpha*rotationAxis.z);
	this->rotationQuaternion = rotation * this->rotationQuaternion;
}

void SceneObject::roll(float angle){

	float cosAlpha = cos(glm::radians(angle/2.0f));
	float sinAlpha = sin(glm::radians(angle/2));

	glm::vec3 rotationAxis = this->getDirection();

	glm::quat rotation = glm::quat(cosAlpha,sinAlpha*rotationAxis.x, sinAlpha*rotationAxis.y, sinAlpha*rotationAxis.z);
	this->rotationQuaternion = rotation * this->rotationQuaternion;
}

void SceneObject::addAnimation(Animation* animation){
	this->animations.push_back(animation);
}

void SceneObject::updateAnimation(float time){

	for(Animation* a: this->animations){
		a->updateObject(this, time);
	}
}

void SceneObject::lookAt(glm::vec3 newCenter){

	glm::vec3 startAxis = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 newDirection = glm::vec3(newCenter - this->position);
	int ii = 0;
	glm::quat newQuat;
	
	newQuat = fromtwovectors(startAxis, newCenter);

	this->rotationQuaternion = newQuat;

}

glm::vec3 SceneObject::getLookingAt(){
	return(this->position + this->getDirection());
}

glm::vec3 SceneObject::getUpVector(){
	glm::vec3 ret = glm::vec3(0.0f, 1.0f, 0.0f);

	ret = this->rotationQuaternion * ret;
	return(ret);
}


void SceneObject::addTexture(char* x){

}


glm::quat fromtwovectors(glm::vec3 u, glm::vec3 v)  // http://lolengine.net/blog/2014/02/24/quaternion-from-two-vectors-final
{
	float norm_u_norm_v = sqrt(glm::dot(u, u) * glm::dot(v, v));
	float real_part = norm_u_norm_v + glm::dot(u, v);
	glm::vec3 w;

	if (real_part < 1.e-6f * norm_u_norm_v)
	{
		/* If u and v are exactly opposite, rotate 180 degrees
		* around an arbitrary orthogonal axis. Axis normalisation
		* can happen later, when we normalise the quaternion. */
		real_part = 0.0f;
		w = abs(u.x) > abs(u.z) ? glm::vec3(-u.y, u.x, 0.f)
			: glm::vec3(0.f, -u.z, u.y);
	}
	else
	{
		/* Otherwise, build quaternion the standard way. */
		w = glm::cross(u, v);
	}

	return glm::normalize(glm::quat(real_part, w.x, w.y, w.z));
}
