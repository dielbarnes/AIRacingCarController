//
// AIModule.h
// Copyright © 2018 Diel Barnes. All rights reserved.
//

#ifndef AIMODULE_H
#define AIMODULE_H

#include <string>
#include <map>

// Base class for all AI modules
class AIModule
{
public:
	void SetMinValues(float fMinDistance, float fMinRateOfChange, float fMinOutput);
	void SetMaxValues(float fMaxDistance, float fMaxRateOfChange, float fMaxOutput);
	void UpdateRacingLine(float fPositionX, float fVelocity, float fRateOfChangeOfDistance);
	void UpdateCar(float fPositionX, float fVelocity);
	void SetCustomValue(std::string strKey, float value);
	float GetCustomValue(std::string strKey);
	virtual float GetCarSteeringFactor() = 0;

protected:
	float m_fRacingLinePositionX;
	float m_fRacingLineVelocity;
	float m_fRateOfChangeOfDistance;
	float m_fCarPositionX;
	float m_fCarVelocity;
	float m_fCarSteeringFactor;
	float m_fMinDistance;
	float m_fMaxDistance;
	float m_fMinRateOfChange;
	float m_fMaxRateOfChange;
	float m_fMinOutput;
	float m_fMaxOutput;
	std::map<std::string, float> m_customValues;

	virtual void DidSetMaxValues() = 0;
};

#endif
