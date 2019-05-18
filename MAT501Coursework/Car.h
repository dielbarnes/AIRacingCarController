//
// Car.h
// Copyright © 2018 Diel Barnes. All rights reserved.
//

#ifndef CAR_H
#define CAR_H

#include "GameObject.h"

class Car : public GameObject
{
public:
	Car(sf::Texture texture, float fPositionX, float fPositionY, float fVelocity);
	~Car();

	sf::Sprite& GetSprite();
	float GetCenterX();
	void SetSteeringFactor(float fSteeringFactor);
	float GetSteeringFactor();

private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	float m_fSteeringFactor;
};

#endif
