#include "PitchAnimation.h"


PitchAnimation::PitchAnimation(void)
{
}


PitchAnimation::~PitchAnimation(void)
{
}

void PitchAnimation::updateObject(SceneObject* object, float t){
	object->pitch(1.0f);
}
