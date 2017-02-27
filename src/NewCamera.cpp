#include "NewCamera.h"


NewCamera::NewCamera(void)
{
	this->reset();
	this->isCamera = true;
	this->projectionMatrix = glm::perspective(45.0f, 1200.0f / 600.0f, 0.1f, 100.0f);
}

NewCamera::~NewCamera(void)
{
}

glm::mat4 NewCamera::getViewMatrix(){
	return(glm::lookAt(this->position, this->getLookingAt(), this->getUpVector()));
}

glm::mat4 NewCamera::getProjectionMatrix(){
	return(this->projectionMatrix);
}

void NewCamera::flyUp(float speed){
	SceneObject::flyUp(-speed);
}

void NewCamera::flyDown(float speed){
	SceneObject::flyDown(-speed);
}

void NewCamera::strafeLeft(float speed){
	SceneObject::strafeLeft(speed);
}

void NewCamera::strafeRight(float speed){
	SceneObject::strafeRight(speed);
}

void NewCamera::moveBackward(float speed){
	SceneObject::moveBackward(speed);
}

void NewCamera::moveForward(float speed){
	SceneObject::moveForward(speed);
}

void NewCamera::pitch(float angle){
	SceneObject::pitch(angle);
}

void NewCamera::yaw(float angle){
	SceneObject::yaw(angle);
}

void NewCamera::roll(float angle){
	SceneObject::roll(-angle);
}

void NewCamera::lookAt(glm::vec3 newCenter){

	SceneObject::lookAt(-2.0f*(this->position - newCenter));

}
