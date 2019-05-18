//
// AIModule.cpp
// Copyright © 2018 Diel Barnes. All rights reserved.
//

#include "AIModule.h"

void AIModule::SetMinValues(float fMinDistance, float fMinRateOfChange, float fMinOutput)
{
	m_fMinDistance = fMinDistance;
	m_fMinRateOfChange = fMinRateOfChange;
	m_fMinOutput = fMinOutput;
}

void AIModule::SetMaxValues(float fMaxDistance, float fMaxRateOfChange, float fMaxOutput)
{
	m_fMaxDistance = fMaxDistance;
	m_fMaxRateOfChange = fMaxRateOfChange;
	m_fMaxOutput = fMaxOutput;

	DidSetMaxValues();
}

void AIModule::UpdateRacingLine(float fPositionX, float fVelocity, float fRateOfChangeOfDistance)
{
	m_fRacingLinePositionX = fPositionX;
	m_fRacingLineVelocity = fVelocity;
	m_fRateOfChangeOfDistance = fRateOfChangeOfDistance;
}

void AIModule::UpdateCar(float fPositionX, float fVelocity)
{
	m_fCarPositionX = fPositionX;
	m_fCarVelocity = fVelocity;
}

void AIModule::SetCustomValue(std::string strKey, float value)
{
	m_customValues[strKey] = value;
}

float AIModule::GetCustomValue(std::string strKey)
{
	return m_customValues[strKey];
}
