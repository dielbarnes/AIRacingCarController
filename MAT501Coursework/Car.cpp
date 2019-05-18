//
// Car.cpp
// Copyright © 2018 Diel Barnes. All rights reserved.
//

#include "Car.h"

Car::Car(sf::Texture texture, float fPositionX, float fPositionY, float fVelocity)
{
	m_texture = texture;
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition((int)fPositionX, (int)fPositionY);
	m_fVelocity = fVelocity;
}

Car::~Car()
{
}

sf::Sprite& Car::GetSprite()
{
	return m_sprite;
}

float Car::GetCenterX()
{
	return m_sprite.getPosition().x + (m_texture.getSize().x / 2);
}

void Car::SetSteeringFactor(float fSteeringFactor)
{
	m_fSteeringFactor = fSteeringFactor;
}

float Car::GetSteeringFactor()
{
	return m_fSteeringFactor;
}
