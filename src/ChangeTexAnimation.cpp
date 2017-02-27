#include "ChangeTexAnimation.h"
#include "NewModel.h"


ChangeTexAnimation::ChangeTexAnimation(void)
{
}


ChangeTexAnimation::~ChangeTexAnimation(void)
{
}


ChangeTexAnimation::ChangeTexAnimation(char* x, char* y){
	this->tex1 = y;
	this->tex2 = x;
	this->b=true;

	this->texture1 = pgr::createTexture(x);
	this->texture2 = pgr::createTexture(y);

	this->myTime = 0;

}


void ChangeTexAnimation::updateObject(SceneObject *object, float time){

	if((int) time != this->myTime || this->myTime == 0){
		this->myTime = (int) time;
	}
	else{
		return;
	}

	NewModel* x;

	x = (NewModel*) object;

	if(this->b){
		x->texture = this->texture1;
	}
	else{
		x->texture = this->texture2;
	}

	b=!b;

}