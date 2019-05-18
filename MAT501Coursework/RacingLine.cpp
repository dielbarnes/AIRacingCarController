//
// RacingLine.cpp
// Copyright © 2018 Diel Barnes. All rights reserved.
//

#include "RacingLine.h"

RacingLine::RacingLine(sf::Color color, float fWidth, float fHeight, float fPositionX, float fPositionY, float fVelocity)
{
	m_shape.setPosition(fPositionX, fPositionY);
	m_shape.setSize(sf::Vector2f(fWidth, fHeight));
	m_shape.setFillColor(color);
	m_fVelocity = fVelocity;
	m_fRateOfChangeOfDistance = 0.0f;
}

RacingLine::~RacingLine()
{
}

sf::RectangleShape& RacingLine::GetShape()
{
	return m_shape;
}

float RacingLine::GetCenterX()
{
	return m_shape.getPosition().x + (m_shape.getSize().x / 2);
}

void RacingLine::SetRateOfChangeOfDistance(float fRateOfChangeOfDistance)
{
	m_fRateOfChangeOfDistance = fRateOfChangeOfDistance;
}

float RacingLine::GetRateOfChangeOfDistance()
{
	return m_fRateOfChangeOfDistance;
}
