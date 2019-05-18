//
// AIController.cpp
// Copyright © 2018 Diel Barnes. All rights reserved.
//

#include "AIController.h"

AIController::AIController()
{
	m_modules[ModuleIndex::FuzzyLogic] = new FuzzyModule();
	m_modules[ModuleIndex::PathFollowing] = new PathFollowingModule();
}

AIController::~AIController()
{
	for (int iModuleIndex = 0; iModuleIndex < MODULE_COUNT; iModuleIndex++)
	{
		SAFE_DELETE(m_modules[iModuleIndex]);
	}
}

void AIController::SetMinValues(float fMinDistance, float fMinRateOfChange, float fMinOutput)
{
	for (int iModuleIndex = 0; iModuleIndex < MODULE_COUNT; iModuleIndex++)
	{
		m_modules[iModuleIndex]->SetMinValues(fMinDistance, fMinRateOfChange, fMinOutput);
	}
}

void AIController::SetMaxValues(float fMaxDistance, float fMaxRateOfChange, float fMinOutput)
{
	for (int iModuleIndex = 0; iModuleIndex < MODULE_COUNT; iModuleIndex++)
	{
		m_modules[iModuleIndex]->SetMaxValues(fMaxDistance, fMaxRateOfChange, fMinOutput);
	}
}

void AIController::UpdateRacingLine(int iModuleIndex, float fPositionX, float fVelocity, float fRateOfChangeOfDistance)
{
	m_modules[iModuleIndex]->UpdateRacingLine(fPositionX, fVelocity, fRateOfChangeOfDistance);
}

void AIController::UpdateCar(int iModuleIndex, float fPositionX, float fVelocity)
{
	m_modules[iModuleIndex]->UpdateCar(fPositionX, fVelocity);
}

void AIController::SetCustomValue(int iModuleIndex, std::string strKey, float value)
{
	m_modules[iModuleIndex]->SetCustomValue(strKey, value);
}

float AIController::GetCustomValue(int iModuleIndex, std::string strKey)
{
	return m_modules[iModuleIndex]->GetCustomValue(strKey);
}

float AIController::GetCarSteeringFactor(int iModuleIndex)
{
	return m_modules[iModuleIndex]->GetCarSteeringFactor();
}
