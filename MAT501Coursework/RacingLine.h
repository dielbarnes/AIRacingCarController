//
// RacingLine.h
// Copyright © 2018 Diel Barnes. All rights reserved.
//

#ifndef RACINGLINE_H
#define RACINGLINE_H

#include "GameObject.h"

#define LINE_WIDTH 3.0f

class RacingLine : public GameObject
{
public:
	RacingLine(sf::Color color, float fWidth, float fHeight, float fPositionX, float fPositionY, float fVelocity);
	~RacingLine();

	sf::RectangleShape& GetShape();
	float GetCenterX();
	void SetRateOfChangeOfDistance(float fRateOfChangeOfDistance);
	float GetRateOfChangeOfDistance();

private:
	sf::RectangleShape m_shape;
	float m_fRateOfChangeOfDistance;
};

#endif
