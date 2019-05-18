//
// PathFollowingModule.h
// Copyright © 2018 Diel Barnes. All rights reserved.
//

#ifndef PATHFOLLOWINGMODULE_H
#define PATHFOLLOWINGMODULE_H

#include <iostream>
#include <cmath>
#include <algorithm>
#include "AIModule.h"

#define RADIUS 5.0f

// Path Following is on one of the AI techniques described in a paper 
// entitled "Steering Behaviors For Autonomous Characters" by Craig Reynolds
// which can be found here: https://www.red3d.com/cwr/steer/gdc99
class PathFollowingModule : public AIModule
{
public:
	PathFollowingModule();
	~PathFollowingModule();

	float GetCarSteeringFactor();

private:
	void DidSetMaxValues();
};

#endif
