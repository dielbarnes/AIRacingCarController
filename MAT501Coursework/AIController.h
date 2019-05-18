//
// AIController.h
// Copyright © 2018 Diel Barnes. All rights reserved.
//

#ifndef AICONTROLLER_H
#define AICONTROLLER_H

#include "FuzzyModule.h"
#include "PathFollowingModule.h"
#include "Utils.h"

#define MODULE_COUNT 2

// Enumerate AI modules for easier mapping in an array
enum ModuleIndex : int
{
	FuzzyLogic = 0,
	PathFollowing
};

class AIController
{
public:
	AIController();
	~AIController();

	// Define the range of inputs and output
	void SetMinValues(float fMinDistance, float fMinRateOfChange, float fMinOutput);
	void SetMaxValues(float fMaxDistance, float fMaxRateOfChange, float fMaxOutput);

	// Receive inputs from the UI Manager
	void UpdateRacingLine(int iModuleIndex, float fPositionX, float fVelocity, float fRateOfChangeOfDistance);
	void UpdateCar(int iModuleIndex, float fPositionX, float fVelocity);

	// For additional data required by an AI module that are irrelevant to others
	void SetCustomValue(int iModuleIndex, std::string strKey, float value);
	float GetCustomValue(int iModuleIndex, std::string strKey);

	// Return the output to the UI Manager
	float GetCarSteeringFactor(int iModuleIndex);

private:
	// Store the AI modules in an array for scalability
	AIModule* m_modules[MODULE_COUNT];
};

#endif
