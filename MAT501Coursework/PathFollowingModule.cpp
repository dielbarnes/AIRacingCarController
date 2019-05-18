//
// PathFollowingModule.cpp
// Copyright © 2018 Diel Barnes. All rights reserved.
//

#include "PathFollowingModule.h"

#define PRINT_VALUES false

PathFollowingModule::PathFollowingModule()
{
	m_fCarSteeringFactor = 0.0f;
}

PathFollowingModule::~PathFollowingModule()
{
	m_customValues.clear();
}

void PathFollowingModule::DidSetMaxValues()
{
}

float PathFollowingModule::GetCarSteeringFactor()
{
	// Predict position of the car at the next time step
	float fFutureCarPositionX = m_fCarPositionX + (m_fCarVelocity * m_fCarSteeringFactor);

	// Find the point on the path nearest the predicted future car position
	// Since the car is not moving along the y-axis, that point will always be the racing line's center
	// Since the racing line is also moving, it's position at the next time step should also be predicted 
	float fFutureRacingLinePositionX = m_fRacingLinePositionX + (m_fRacingLineVelocity * m_fRateOfChangeOfDistance);

	float fFutureDistance = fFutureRacingLinePositionX - fFutureCarPositionX;

	#if PRINT_VALUES
	std::cout << "CAR CurrentPosition: " << m_fCarPositionX << "   FuturePosition: " << fFutureCarPositionX << std::endl;
	std::cout << "LINE CurrentPosition: " << m_fRacingLinePositionX << "   FuturePosition: " << fFutureRacingLinePositionX << std::endl;
	std::cout << "FutureDistance: " << fFutureDistance << std::endl;
	#endif

	if (std::abs(fFutureDistance) > RADIUS)
	{
		// If the car is not within the path's radius, compute the steering factor
		float fSteeringFactor = fFutureDistance / m_fCarVelocity;
		// Enforce limit on the steering factor
		fSteeringFactor = fSteeringFactor > 0 ? std::min(fSteeringFactor, m_fMaxRateOfChange) : std::max(fSteeringFactor, m_fMinRateOfChange); //m_fMaxOutput
		#if PRINT_VALUES
		std::cout << "OUTPUT SteeringFactor: " << fSteeringFactor << std::endl;
		std::cout << std::endl;
		#endif
		return fSteeringFactor;
	}
	else
	{
		// No corrective steering is required
		#if PRINT_VALUES
		std::cout << "No corrective steering required" << std::endl;
		std::cout << std::endl;
		#endif
		return 0.0f;
	}
}
