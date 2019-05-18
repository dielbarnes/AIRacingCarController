//
// GameObject.h
// Copyright © 2018 Diel Barnes. All rights reserved.
//

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SFML/Graphics.hpp>

#define DEFAULT_VELOCITY 1.0f

// Base class for all game objects
class GameObject
{
public:
	virtual float GetCenterX() = 0;
	float GetVelocity();

protected:
	float m_fVelocity;
};

#endif
