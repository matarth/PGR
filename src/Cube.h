//----------------------------------------------------------------------------------------
/**
 * \file       kadrnmat.cpp
 * \author     Matou� Kadrno�ka
 * \date       2016/31/05
 *
 *  Class for stone in the scene.. with hardcoded data.
 *
*/
//----------------------------------------------------------------------------------------


#pragma once
#include "NewModel.h"


class Cube: public NewModel
{

public:
	Cube(void);
	~Cube(void);

	virtual void connectDataToShaders();
};

