//
// FuzzyModule.cpp
// Copyright © 2018 Diel Barnes. All rights reserved.
//

#include <iostream>
#include "FuzzyModule.h"

#define PRINT_X_VALUES true
#define PRINT_INPUTS false
#define PRINT_DEGREES_OF_MEMBERSHIP false
#define PRINT_CENTROID false
#define PRINT_MEMBERSHIP_FUNCTIONS false

#pragma region Init

FuzzyModule::FuzzyModule()
{
}

FuzzyModule::~FuzzyModule()
{
	m_customValues.clear();
}

void FuzzyModule::DidSetMaxValues()
{
	// Far: 5.87 - 10.27 - 14.68 cars (max)
	// Medium: 0 - 2.94 - 5.87 - 10.27 cars
	// Close: 0 - 1.47 cars
	m_fFarLeftX0 = -0.7f * m_fMaxDistance;
	m_fFarLeftX1 = -0.4f * m_fMaxDistance;
	m_fMediumLeftX0 = -0.7f * m_fMaxDistance;
	m_fMediumLeftX1 = -0.4f * m_fMaxDistance;
	m_fMediumLeftX2 = -0.2f * m_fMaxDistance;
	m_fMediumLeftX3 = -0.005f * m_fMaxDistance;
	m_fCloseX0 = -0.1f * m_fMaxDistance;
	m_fCloseX1 = 0.0f * m_fMaxDistance;
	m_fCloseX2 = 0.1f * m_fMaxDistance;
	m_fMediumRightX0 = 0.005f * m_fMaxDistance;
	m_fMediumRightX1 = 0.2f * m_fMaxDistance;
	m_fMediumRightX2 = 0.4f * m_fMaxDistance;
	m_fMediumRightX3 = 0.7f * m_fMaxDistance;
	m_fFarRightX0 = 0.4f * m_fMaxDistance;
	m_fFarRightX1 = 0.7f * m_fMaxDistance;

	#if PRINT_X_VALUES
	std::cout << "MinDistance: " << m_fMinDistance << std::endl;
	std::cout << "Distance FarLeft x0: " << m_fFarLeftX0 << std::endl;
	std::cout << "Distance FarLeft x1: " << m_fFarLeftX1 << std::endl;
	std::cout << "Distance MediumLeft x0: " << m_fMediumLeftX0 << std::endl;
	std::cout << "Distance MediumLeft x1: " << m_fMediumLeftX1 << std::endl;
	std::cout << "Distance MediumLeft x2: " << m_fMediumLeftX2 << std::endl;
	std::cout << "Distance MediumLeft x3: " << m_fMediumLeftX3 << std::endl;
	std::cout << "Distance Close x0: " << m_fCloseX0 << std::endl;
	std::cout << "Distance Close x1: " << m_fCloseX1 << std::endl;
	std::cout << "Distance Close x2: " << m_fCloseX2 << std::endl;
	std::cout << "Distance MediumRight x0: " << m_fMediumRightX0 << std::endl;
	std::cout << "Distance MediumRight x1: " << m_fMediumRightX1 << std::endl;
	std::cout << "Distance MediumRight x2: " << m_fMediumRightX2 << std::endl;
	std::cout << "Distance MediumRight x3: " << m_fMediumRightX3 << std::endl;
	std::cout << "Distance FarRight x0: " << m_fFarRightX0 << std::endl;
	std::cout << "Distance FarRight x1: " << m_fFarRightX1 << std::endl;
	std::cout << "MaxDistance: " << m_fMaxDistance << std::endl;
	std::cout << std::endl;
	#endif

	// FastLeft/Right: 3 - 5 - 9 (max)
	// Left/Right: 0 - 1 - 4 - 5
	// NoMovement: 0 - 1
	m_fFastLeftX0 = -0.56f * m_fMaxRateOfChange;
	m_fFastLeftX1 = -0.34f * m_fMaxRateOfChange;
	m_fLeftX0 = -0.56f * m_fMaxRateOfChange;
	m_fLeftX1 = -0.45f * m_fMaxRateOfChange;
	m_fLeftX2 = -0.12f * m_fMaxRateOfChange;
	m_fLeftX3 = -0.05f * m_fMaxRateOfChange;
	m_fNoMovementX0 = -0.12f * m_fMaxRateOfChange;
	m_fNoMovementX1 = 0.0f * m_fMaxRateOfChange;
	m_fNoMovementX2 = 0.12f * m_fMaxRateOfChange;
	m_fRightX0 = 0.05f * m_fMaxRateOfChange;
	m_fRightX1 = 0.12f * m_fMaxRateOfChange;
	m_fRightX2 = 0.45f * m_fMaxRateOfChange;
	m_fRightX3 = 0.56f * m_fMaxRateOfChange;
	m_fFastRightX0 = 0.34f * m_fMaxRateOfChange;
	m_fFastRightX1 = 0.56f * m_fMaxRateOfChange;

	#if PRINT_X_VALUES
	std::cout << "MinRateOfChange: " << m_fMinRateOfChange << std::endl;
	std::cout << "RateOfChange FastLeft x0: " << m_fFastLeftX0 << std::endl;
	std::cout << "RateOfChange FastLeft x1: " << m_fFastLeftX1 << std::endl;
	std::cout << "RateOfChange Left x0: " << m_fLeftX0 << std::endl;
	std::cout << "RateOfChange Left x1: " << m_fLeftX1 << std::endl;
	std::cout << "RateOfChange Left x2: " << m_fLeftX2 << std::endl;
	std::cout << "RateOfChange Left x3: " << m_fLeftX3 << std::endl;
	std::cout << "RateOfChange NoMovement x0: " << m_fNoMovementX0 << std::endl;
	std::cout << "RateOfChange NoMovement x1: " << m_fNoMovementX1 << std::endl;
	std::cout << "RateOfChange NoMovement x2: " << m_fNoMovementX2 << std::endl;
	std::cout << "RateOfChange Right x0: " << m_fRightX0 << std::endl;
	std::cout << "RateOfChange Right x1: " << m_fRightX1 << std::endl;
	std::cout << "RateOfChange Right x2: " << m_fRightX2 << std::endl;
	std::cout << "RateOfChange Right x3: " << m_fRightX3 << std::endl;
	std::cout << "RateOfChange FastRight x0: " << m_fFastRightX0 << std::endl;
	std::cout << "RateOfChange FastRight x1: " << m_fFastRightX1 << std::endl;
	std::cout << "MaxRateOfChange: " << m_fMaxRateOfChange << std::endl;
	std::cout << std::endl;
	#endif

	// FastLeft/Right: 8 - 10 - 12 (max)
	// Left/Right: 0 - 6 - 9 - 11
	// NoMovement: 0 - 6
	m_fOutputFastLeftX0 = -0.83f * m_fMaxOutput;
	m_fOutputFastLeftX1 = -0.67f * m_fMaxOutput;
	m_fOutputLeftX0 = -0.92f * m_fMaxOutput;
	m_fOutputLeftX1 = -0.75f * m_fMaxOutput;
	m_fOutputLeftX2 = -0.5f * m_fMaxOutput;
	m_fOutputLeftX3 = -0.1f * m_fMaxOutput;
	m_fOutputNoMovementX0 = -0.5f * m_fMaxOutput;
	m_fOutputNoMovementX1 = 0.0f * m_fMaxOutput;
	m_fOutputNoMovementX2 = 0.5f * m_fMaxOutput;
	m_fOutputRightX0 = 0.1f * m_fMaxOutput;
	m_fOutputRightX1 = 0.5f * m_fMaxOutput;
	m_fOutputRightX2 = 0.75f * m_fMaxOutput;
	m_fOutputRightX3 = 0.92f * m_fMaxOutput;
	m_fOutputFastRightX0 = 0.67f * m_fMaxOutput;
	m_fOutputFastRightX1 = 0.83f * m_fMaxOutput;

	#if PRINT_X_VALUES
	std::cout << "MinOutput: " << m_fMinOutput << std::endl;
	std::cout << "Output FastLeft x0: " << m_fOutputFastLeftX0 << std::endl;
	std::cout << "Output FastLeft x1: " << m_fOutputFastLeftX1 << std::endl;
	std::cout << "Output Left x0: " << m_fOutputLeftX0 << std::endl;
	std::cout << "Output Left x1: " << m_fOutputLeftX1 << std::endl;
	std::cout << "Output Left x2: " << m_fOutputLeftX2 << std::endl;
	std::cout << "Output Left x3: " << m_fOutputLeftX3 << std::endl;
	std::cout << "Output NoMovement x0: " << m_fOutputNoMovementX0 << std::endl;
	std::cout << "Output NoMovement x1: " << m_fOutputNoMovementX1 << std::endl;
	std::cout << "Output NoMovement x2: " << m_fOutputNoMovementX2 << std::endl;
	std::cout << "Output Right x0: " << m_fOutputRightX0 << std::endl;
	std::cout << "Output Right x1: " << m_fOutputRightX1 << std::endl;
	std::cout << "Output Right x2: " << m_fOutputRightX2 << std::endl;
	std::cout << "Output Right x3: " << m_fOutputRightX3 << std::endl;
	std::cout << "Output FastRight x0: " << m_fOutputFastRightX0 << std::endl;
	std::cout << "Output FastRight x1: " << m_fOutputFastRightX1 << std::endl;
	std::cout << "MaxOutput: " << m_fMaxOutput << std::endl;
	std::cout << std::endl << std::endl << std::endl << std::endl;
	#endif
}

#pragma endregion

#pragma region Process Inputs

float FuzzyModule::GetCarSteeringFactor()
{
	// Compute the distance of the line from the car
	// Positive distance means the line is at the right of the car; the car has to steer right
	// Negative distance means the line is at the left of the car; the car has to steer left
	float fDistance = m_fRacingLinePositionX - m_fCarPositionX;

	#if PRINT_INPUTS || PRINT_DEGREES_OF_MEMBERSHIP || PRINT_CENTROID || PRINT_MEMBERSHIP_FUNCTIONS
	std::cout << "----------// START //----------" << std::endl;
	std::cout << "Distance: " << fDistance << "   RateOfChange: " << m_fRateOfChangeOfDistance << std::endl;
	#endif

	// Fuzzification
	// Get degrees of membership of the distance

	#if PRINT_DEGREES_OF_MEMBERSHIP
	std::cout << "----------// Distance //----------" << std::endl;
	#endif

	float fFarLeftDegree = FuzzyReverseGrade(fDistance, m_fFarLeftX0, m_fFarLeftX1);
	#if PRINT_DEGREES_OF_MEMBERSHIP
	std::cout << "Distance FarLeft: " << fFarLeftDegree << std::endl;
	#endif

	float fMediumLeftDegree = FuzzyTrapezoid(fDistance, m_fMediumLeftX0, m_fMediumLeftX1, m_fMediumLeftX2, m_fMediumLeftX3);
	#if PRINT_DEGREES_OF_MEMBERSHIP
	std::cout << "Distance MediumLeft: " << fMediumLeftDegree << std::endl;
	#endif

	float fCloseDegree = FuzzyTriangle(fDistance, m_fCloseX0, m_fCloseX1, m_fCloseX2);
	#if PRINT_DEGREES_OF_MEMBERSHIP
	std::cout << "Distance Close: " << fCloseDegree << std::endl;
	#endif

	float fMediumRightDegree = FuzzyTrapezoid(fDistance, m_fMediumRightX0, m_fMediumRightX1, m_fMediumRightX2, m_fMediumRightX3);
	#if PRINT_DEGREES_OF_MEMBERSHIP
	std::cout << "Distance MediumRight: " << fMediumRightDegree << std::endl;
	#endif

	float fFarRightDegree = FuzzyGrade(fDistance, m_fFarRightX0, m_fFarRightX1);
	#if PRINT_DEGREES_OF_MEMBERSHIP
	std::cout << "Distance FarRight: " << fFarRightDegree << std::endl;
	#endif

	// Get degrees of membership of the rate of change

	#if PRINT_DEGREES_OF_MEMBERSHIP
	std::cout << "----------// RateOfChange //----------" << std::endl;
	#endif

	float fFastLeftDegree = FuzzyReverseGrade(m_fRateOfChangeOfDistance, m_fFastLeftX0, m_fFastLeftX1);
	#if PRINT_DEGREES_OF_MEMBERSHIP
	std::cout << "RateOfChange FastLeft: " << fFastLeftDegree << std::endl;
	#endif

	float fLeftDegree = FuzzyTrapezoid(m_fRateOfChangeOfDistance, m_fLeftX0, m_fLeftX1, m_fLeftX2, m_fLeftX3);
	#if PRINT_DEGREES_OF_MEMBERSHIP
	std::cout << "RateOfChange Left: " << fLeftDegree << std::endl;
	#endif

	float fNoMovementDegree = FuzzyTriangle(m_fRateOfChangeOfDistance, m_fNoMovementX0, m_fNoMovementX1, m_fNoMovementX2);
	#if PRINT_DEGREES_OF_MEMBERSHIP
	std::cout << "RateOfChange NoMovement: " << fNoMovementDegree << std::endl;
	#endif

	float fRightDegree = FuzzyTrapezoid(m_fRateOfChangeOfDistance, m_fRightX0, m_fRightX1, m_fRightX2, m_fRightX3);
	#if PRINT_DEGREES_OF_MEMBERSHIP
	std::cout << "RateOfChange Right: " << fRightDegree << std::endl;
	#endif

	float fFastRightDegree = FuzzyGrade(m_fRateOfChangeOfDistance, m_fFastRightX0, m_fFastRightX1);
	#if PRINT_DEGREES_OF_MEMBERSHIP
	std::cout << "RateOfChange FastRight: " << fFastRightDegree << std::endl;
	#endif

	// Implementation of fuzzy rules
	// Get degrees of membership of the output

	float fOutputFastLeftDegree = GetOutputFastLeftDegree(fFarLeftDegree, fFastLeftDegree, fLeftDegree, fNoMovementDegree, fRightDegree, fMediumLeftDegree);
	float fOutputLeftDegree = GetOutputLeftDegree(fFarLeftDegree, fFastRightDegree, fMediumLeftDegree, fLeftDegree, fNoMovementDegree, fRightDegree, fCloseDegree, fFastLeftDegree);
	float fOutputNoMovementDegree = GetOutputNoMovementDegree(fMediumLeftDegree, fFastRightDegree, fCloseDegree, fLeftDegree, fNoMovementDegree, fRightDegree, fMediumRightDegree, fFastLeftDegree);
	float fOutputRightDegree = GetOutputRightDegree(fCloseDegree, fFastRightDegree, fMediumRightDegree, fLeftDegree, fNoMovementDegree, fRightDegree, fFarRightDegree, fFastLeftDegree);
	float fOutputFastRightDegree = GetOutputFastRightDegree(fMediumRightDegree, fFastRightDegree, fFarRightDegree, fLeftDegree, fNoMovementDegree, fRightDegree);

	#if PRINT_DEGREES_OF_MEMBERSHIP
	std::cout << "----------// Output //----------" << std::endl;
	std::cout << "Output FastLeft: " << fOutputFastLeftDegree << std::endl;
	std::cout << "Output Left: " << fOutputLeftDegree << std::endl;
	std::cout << "Output NoMovement: " << fOutputNoMovementDegree << std::endl;
	std::cout << "Output Right: " << fOutputRightDegree << std::endl;
	std::cout << "Output FastRight: " << fOutputFastRightDegree << std::endl;
	#endif

	// Defuzzification
	// Find the centroid

	#if PRINT_CENTROID
	std::cout << "----------// Centroid //----------" << std::endl;
	#endif

	// Get the new x values after clipping the membership functions to the degrees of membership of the output
	// Equation of slope of line: m = (y1 - y0)/(x1 x0)

	float fNewFastLeftX0 = 0.0f;
	if (fOutputFastLeftDegree == 1)
	{
		fNewFastLeftX0 = m_fOutputFastLeftX0;
	}
	else if (fOutputFastLeftDegree > 0)
	{
		float m = 1 / (m_fOutputFastLeftX1 - m_fOutputFastLeftX0);
		fNewFastLeftX0 = m_fOutputFastLeftX1 - (fOutputFastLeftDegree / m);
	}

	float fNewLeftX1 = 0.0f;
	float fNewLeftX2 = 0.0f;
	if (fOutputLeftDegree == 1)
	{
		fNewLeftX1 = m_fOutputLeftX1;
		fNewLeftX2 = m_fOutputLeftX2;
	}
	else if (fOutputLeftDegree > 0)
	{
		float m = 1 / (m_fOutputLeftX1 - m_fOutputLeftX0);
		fNewLeftX1 = (fOutputLeftDegree / m) + m_fOutputLeftX0;

		m = 1 / (m_fOutputLeftX3 - m_fOutputLeftX2);
		fNewLeftX2 = m_fOutputLeftX3 - (fOutputLeftDegree / m);
	}

	bool bNoMovementIsTriangle = false;
	float fNewNoMovementX1a = 0.0f;
	float fNewNoMovementX1b = 0.0f;
	if (fOutputNoMovementDegree == 1)
	{
		bNoMovementIsTriangle = true;
	}
	else if (fOutputNoMovementDegree > 0)
	{
		float m = 1 / (m_fOutputNoMovementX1 - m_fOutputNoMovementX0);
		fNewNoMovementX1a = (fOutputNoMovementDegree / m) + m_fOutputNoMovementX0;

		m = 1 / (m_fOutputNoMovementX2 - m_fOutputNoMovementX1);
		fNewNoMovementX1b = m_fOutputNoMovementX2 - (fOutputNoMovementDegree / m);
	}

	float fNewRightX1 = 0.0f;
	float fNewRightX2 = 0.0f;
	if (fOutputRightDegree == 1)
	{
		fNewRightX1 = m_fOutputRightX1;
		fNewRightX2 = m_fOutputRightX2;
	}
	else if (fOutputRightDegree > 0)
	{
		float m = 1 / (m_fOutputRightX1 - m_fOutputRightX0);
		fNewRightX1 = (fOutputRightDegree / m) + m_fOutputRightX0;

		m = 1 / (m_fOutputRightX3 - m_fOutputRightX2);
		fNewRightX2 = m_fOutputRightX3 - (fOutputRightDegree / m);
	}

	float fNewFastRightX1 = 0.0f;
	if (fOutputFastRightDegree == 1)
	{
		fNewFastRightX1 = m_fOutputFastRightX1;
	}
	else if (fOutputFastRightDegree > 0)
	{
		float m = 1 / (m_fOutputFastRightX1 - m_fOutputFastRightX0);
		fNewFastRightX1 = (fOutputFastRightDegree / m) + m_fOutputFastRightX0;
	}

	// Get degrees of membership of sample points

	const int iNumberOfSamples = 21;
	float fTotalOutput = m_fMaxOutput - m_fMinOutput;
	float fInterval = fTotalOutput / (iNumberOfSamples - 1);
	float samplePoints[iNumberOfSamples];
	float degreesOfSamples[iNumberOfSamples];

	for (int i = 0; i < iNumberOfSamples; i++)
	{
		float fSamplePoint = m_fMinOutput + (i * fInterval);
		samplePoints[i] = fSamplePoint;
		#if PRINT_CENTROID
		std::cout << "Sample Point: " << fSamplePoint << std::endl;
		#endif
		
		float fSampleOutputFastLeftDegree = fOutputFastLeftDegree == 0 ? 0.0f : FuzzyReverseGrade(fSamplePoint, fNewFastLeftX0, m_fOutputFastLeftX1);
		#if PRINT_CENTROID
		std::cout << "Sample OutputFastLeft: " << fSampleOutputFastLeftDegree << std::endl;
		#endif
		
		float fSampleOutputLeftDegree = fOutputLeftDegree == 0 ? 0.0f : FuzzyTrapezoid(fSamplePoint, m_fOutputLeftX0, fNewLeftX1, fNewLeftX2, m_fOutputLeftX3);
		#if PRINT_CENTROID
		std::cout << "Sample OutputLeft: " << fSampleOutputLeftDegree << std::endl;
		#endif

		float fSampleOutputNoMovementDegree = 0.0f;
		if (bNoMovementIsTriangle)
		{
			fSampleOutputNoMovementDegree = FuzzyTriangle(fSamplePoint, m_fOutputNoMovementX0, m_fOutputNoMovementX1, m_fOutputNoMovementX2);
		}
		else if (fOutputNoMovementDegree > 0.0f) {
			fSampleOutputNoMovementDegree = FuzzyTrapezoid(fSamplePoint, m_fOutputNoMovementX0, fNewNoMovementX1a, fNewNoMovementX1b, m_fOutputNoMovementX2);
		}
		#if PRINT_CENTROID
		std::cout << "Sample OutputNoMovement: " << fSampleOutputNoMovementDegree << std::endl;
		#endif

		float fSampleOutputRightDegree = fOutputRightDegree == 0 ? 0.0f : FuzzyTrapezoid(fSamplePoint, m_fOutputRightX0, fNewRightX1, fNewRightX2, m_fOutputRightX3);
		#if PRINT_CENTROID
		std::cout << "Sample OutputRight: " << fSampleOutputRightDegree << std::endl;
		#endif

		float fSampleOutputFastRightDegree = fOutputFastRightDegree == 0 ? 0.0f : FuzzyGrade(fSamplePoint, m_fOutputFastRightX0, fNewFastRightX1);
		#if PRINT_CENTROID
		std::cout << "Sample OutputFastRight: " << fSampleOutputFastRightDegree << std::endl;
		#endif

		// Get the sum of the degrees of membership of the sample point

		degreesOfSamples[i] = fSampleOutputFastLeftDegree + fSampleOutputLeftDegree + fSampleOutputNoMovementDegree + fSampleOutputRightDegree + fSampleOutputFastRightDegree;
		#if PRINT_CENTROID
		std::cout << "Sum: " << degreesOfSamples[i] << std::endl;
		#endif
	}

	float fNumerator = 0.0f;
	for (int i = 0; i < iNumberOfSamples; i++)
	{
		fNumerator += (samplePoints[i] * degreesOfSamples[i]);
	}

	float fDenominator = 0.0f;
	for (int i = 0; i < iNumberOfSamples; i++)
	{
		fDenominator += degreesOfSamples[i];
	}

	float fCrispValue = fNumerator / fDenominator;

	#if PRINT_CENTROID
	std::cout << "Numerator: " << fNumerator << "  /  Denominator: " << fDenominator << std::endl;
	std::cout << "Crisp Value: " << fCrispValue << std::endl;
	#endif

	#if PRINT_INPUTS || PRINT_DEGREES_OF_MEMBERSHIP || PRINT_CENTROID || PRINT_MEMBERSHIP_FUNCTIONS
	std::cout << "----------// END //----------" << std::endl << std::endl << std::endl;
	#endif

	return fCrispValue;
}

#pragma endregion

#pragma region Fuzzy Rules

float FuzzyModule::GetOutputFastLeftDegree(float fFarLeftDegree, float fFastLeftDegree, float fLeftDegree, float fNoMovementDegree, float fRightDegree, float fMediumLeftDegree)
{
	// IF (Distance is FarLeft) AND (RateOfChange is FastLeft) THEN (Steering is FastLeft)  
	float fOutputFastLeftDegree = FuzzyAND(fFarLeftDegree, fFastLeftDegree);
	// IF (Distance is FarLeft) AND (RateOfChange is Left) THEN (Steering is FastLeft) 
	fOutputFastLeftDegree = FuzzyOR(fOutputFastLeftDegree, FuzzyAND(fFarLeftDegree, fLeftDegree));
	// IF (Distance is FarLeft) AND (RateOfChange is NoMovement) THEN (Steering is FastLeft) 
	fOutputFastLeftDegree = FuzzyOR(fOutputFastLeftDegree, FuzzyAND(fFarLeftDegree, fNoMovementDegree));
	// IF (Distance is FarLeft) AND (RateOfChange is Right) THEN (Steering is FastLeft) 
	fOutputFastLeftDegree = FuzzyOR(fOutputFastLeftDegree, FuzzyAND(fFarLeftDegree, fRightDegree));
	// IF (Distance is MediumLeft) AND (RateOfChange is FastLeft) THEN (Steering is FastLeft)
	fOutputFastLeftDegree = FuzzyOR(fOutputFastLeftDegree, FuzzyAND(fMediumLeftDegree, fFastLeftDegree));

	return fOutputFastLeftDegree;
}

float FuzzyModule::GetOutputLeftDegree(float fFarLeftDegree, float fFastRightDegree, float fMediumLeftDegree, float fLeftDegree, float fNoMovementDegree, float fRightDegree, float fCloseDegree, float fFastLeftDegree)
{
	// IF (Distance is FarLeft) AND (RateOfChange is FastRight) THEN (Steering is Left) 
	float fOutputLeftDegree = FuzzyAND(fFarLeftDegree, fFastRightDegree);
	// IF (Distance is MediumLeft) AND (RateOfChange is Left) THEN (Steering is Left) 
	fOutputLeftDegree = FuzzyOR(fOutputLeftDegree, FuzzyAND(fMediumLeftDegree, fLeftDegree));
	// IF (Distance is MediumLeft) AND (RateOfChange is NoMovement) THEN (Steering is Left) 
	fOutputLeftDegree = FuzzyOR(fOutputLeftDegree, FuzzyAND(fMediumLeftDegree, fNoMovementDegree));
	// IF (Distance is MediumLeft) AND (RateOfChange is Right) THEN (Steering is Left) 
	fOutputLeftDegree = FuzzyOR(fOutputLeftDegree, FuzzyAND(fMediumLeftDegree, fRightDegree));
	// IF (Distance is Close) AND (RateOfChange is FastLeft) THEN (Steering is Left) 
	fOutputLeftDegree = FuzzyOR(fOutputLeftDegree, FuzzyAND(fCloseDegree, fFastLeftDegree));

	return fOutputLeftDegree;
}

float FuzzyModule::GetOutputNoMovementDegree(float fMediumLeftDegree, float fFastRightDegree, float fCloseDegree, float fLeftDegree, float fNoMovementDegree, float fRightDegree, float fMediumRightDegree, float fFastLeftDegree)
{
	// IF (Distance is MediumLeft) AND (RateOfChange is FastRight) THEN (Steering is NoMovement) 
	float fOutputNoMovementDegree = FuzzyAND(fMediumLeftDegree, fFastRightDegree);
	// IF (Distance is Close) AND (RateOfChange is Left) THEN (Steering is NoMovement) 
	fOutputNoMovementDegree = FuzzyOR(fOutputNoMovementDegree, FuzzyAND(fCloseDegree, fLeftDegree));
	// IF (Distance is Close) AND (RateOfChange is NoMovement) THEN (Steering is NoMovement) 
	fOutputNoMovementDegree = FuzzyOR(fOutputNoMovementDegree, FuzzyAND(fCloseDegree, fNoMovementDegree));
	// IF (Distance is Close) AND (RateOfChange is Right) THEN (Steering is NoMovement) 
	fOutputNoMovementDegree = FuzzyOR(fOutputNoMovementDegree, FuzzyAND(fCloseDegree, fRightDegree));
	// IF (Distance is MediumRight) AND (RateOfChange is FastLeft) THEN (Steering is NoMovement) 
	fOutputNoMovementDegree = FuzzyOR(fOutputNoMovementDegree, FuzzyAND(fMediumRightDegree, fFastLeftDegree));

	return fOutputNoMovementDegree;
}

float FuzzyModule::GetOutputRightDegree(float fCloseDegree, float fFastRightDegree, float fMediumRightDegree, float fLeftDegree, float fNoMovementDegree, float fRightDegree, float fFarRightDegree, float fFastLeftDegree)
{
	// IF (Distance is Close) AND (RateOfChange is FastRight) THEN (Steering is Right) 
	float fOutputRightDegree = FuzzyAND(fCloseDegree, fFastRightDegree);
	// IF (Distance is MediumRight) AND (RateOfChange is Left) THEN (Steering is Right) 
	fOutputRightDegree = FuzzyOR(fOutputRightDegree, FuzzyAND(fMediumRightDegree, fLeftDegree));
	// IF (Distance is MediumRight) AND (RateOfChange is NoMovement) THEN (Steering is Right) 
	fOutputRightDegree = FuzzyOR(fOutputRightDegree, FuzzyAND(fMediumRightDegree, fNoMovementDegree));
	// IF (Distance is MediumRight) AND (RateOfChange is Right) THEN (Steering is Right) 
	fOutputRightDegree = FuzzyOR(fOutputRightDegree, FuzzyAND(fMediumRightDegree, fRightDegree));
	// IF (Distance is FarRight) AND (RateOfChange is FastLeft) THEN (Steering is Right) 
	fOutputRightDegree = FuzzyOR(fOutputRightDegree, FuzzyAND(fFarRightDegree, fFastLeftDegree));

	return fOutputRightDegree;
}

float FuzzyModule::GetOutputFastRightDegree(float fMediumRightDegree, float fFastRightDegree, float fFarRightDegree, float fLeftDegree, float fNoMovementDegree, float fRightDegree)
{
	// IF (Distance is MediumRight) AND (RateOfChange is FastRight) THEN (Steering is FastRight)
	float fOutputFastRightDegree = FuzzyAND(fMediumRightDegree, fFastRightDegree);
	// IF (Distance is FarRight) AND (RateOfChange is Left) THEN (Steering is FastRight) 
	fOutputFastRightDegree = FuzzyOR(fOutputFastRightDegree, FuzzyAND(fFarRightDegree, fLeftDegree));
	// IF (Distance is FarRight) AND (RateOfChange is NoMovement) THEN (Steering is FastRight) 
	fOutputFastRightDegree = FuzzyOR(fOutputFastRightDegree, FuzzyAND(fFarRightDegree, fNoMovementDegree));
	// IF (Distance is FarRight) AND (RateOfChange is Right) THEN (Steering is FastRight) 
	fOutputFastRightDegree = FuzzyOR(fOutputFastRightDegree, FuzzyAND(fFarRightDegree, fRightDegree));
	// IF (Distance is FarRight) AND (RateOfChange is FastRight) THEN (Steering is FastRight) 
	fOutputFastRightDegree = FuzzyOR(fOutputFastRightDegree, FuzzyAND(fFarRightDegree, fFastRightDegree));

	return fOutputFastRightDegree;
}

#pragma endregion

// The following methods are based from the book "AI for Game Developers" by David Bourg & Glenn Seemann

#pragma region Membership Functions

float FuzzyModule::FuzzyGrade(float x, float x0, float x1)
{
	if (x <= x0)
	{
		#if PRINT_MEMBERSHIP_FUNCTIONS 
		std::cout << "   FuzzyGrade x (" << x << ") <= x0 (" << x0 << ") RETURN 0" << std::endl; 
		#endif
		return 0;
	}
	else if (x >= x1)
	{
		#if PRINT_MEMBERSHIP_FUNCTIONS 
		std::cout << "   FuzzyGrade x (" << x << ") >= x1 (" << x1 << ") RETURN 1" << std::endl;
		#endif
		return 1;
	}
	else // x0 < x < x1
	{
		#if PRINT_MEMBERSHIP_FUNCTIONS 
		std::cout << "   FuzzyGrade x0 (" << x0 << ") < x (" << x << ") < x1 (" << x1 << ")" << std::endl;
		#endif
		return (x / (x1 - x0)) - (x0 / (x1 - x0));
	}
}

float FuzzyModule::FuzzyReverseGrade(float x, float x0, float x1)
{
	if (x <= x0)
	{
		#if PRINT_MEMBERSHIP_FUNCTIONS 
		std::cout << "   FuzzyReverseGrade x (" << x << ") <= x0 (" << x0 << ") RETURN 1" << std::endl;
		#endif
		return 1;
	}
	else if (x >= x1)
	{
		#if PRINT_MEMBERSHIP_FUNCTIONS 
		std::cout << "   FuzzyReverseGrade x (" << x << ") >= x1 (" << x1 << ") RETURN 0" << std::endl;
		#endif
		return 0;
	}
	else // x0 < x < x1
	{
		#if PRINT_MEMBERSHIP_FUNCTIONS 
		std::cout << "   FuzzyReverseGrade x0 (" << x0 << ") < x (" << x << ") < x1 (" << x1 << ")" << std::endl;
		#endif
		return (-x / (x1 - x0)) + (x1 / (x1 - x0));
	}
}

float FuzzyModule::FuzzyTriangle(float x, float x0, float x1, float x2)
{
	if (x <= x0 || x >= x2)
	{
		#if PRINT_MEMBERSHIP_FUNCTIONS 
		std::cout << "   FuzzyTriangle x (" << x << ") <= x0 (" << x0 << ") || x >= x2 (" << x2 << ") RETURN 0" << std::endl;
		#endif
		return 0;
	}
	else if (x == x1)
	{
		#if PRINT_MEMBERSHIP_FUNCTIONS 
		std::cout << "   FuzzyTriangle x (" << x << ") == x1 (" << x1 << ") RETURN 1" << std::endl;
		#endif
		return 1;
	}
	else if (x > x0 && x < x1)
	{
		#if PRINT_MEMBERSHIP_FUNCTIONS 
		std::cout << "   FuzzyTriangle x0 (" << x0 << ") < x (" << x << ") < x1 (" << x1 << ")" << std::endl;
		#endif
		return (x / (x1 - x0)) - (x0 / (x1 - x0));
	}
	else // x1 < x < x2
	{
		#if PRINT_MEMBERSHIP_FUNCTIONS 
		std::cout << "   FuzzyTriangle x1 (" << x1 << ") < x (" << x << ") < x2 (" << x2 << ")" << std::endl;
		#endif
		return (-x / (x2 - x1)) + (x2 / (x2 - x1));
	}
}

float FuzzyModule::FuzzyTrapezoid(float x, float x0, float x1, float x2, float x3)
{
	if (x <= x0 || x >= x3)
	{
		#if PRINT_MEMBERSHIP_FUNCTIONS 
		std::cout << "   FuzzyTrapezoid x (" << x << ") <= x0 (" << x0 << ") || x >= x3 (" << x3 << ") RETURN 0" << std::endl;
		#endif
		return 0;
	}
	else if (x >= x1 && x <= x2) // Plateau
	{
		#if PRINT_MEMBERSHIP_FUNCTIONS 
		std::cout << "   FuzzyTrapezoid x1 (" << x1 << ") <= x (" << x << ") <= x2 (" << x2 << ") RETURN 1" << std::endl;
		#endif
		return 1;
	}
	else if (x > x0 && x < x1)
	{
		#if PRINT_MEMBERSHIP_FUNCTIONS 
		std::cout << "   FuzzyTrapezoid x0 (" << x0 << ") < x (" << x << ") < x1 (" << x1 << ")" << std::endl;
		#endif
		return (x / (x1 - x0)) - (x0 / (x1 - x0));
	}
	else // x2 < x < x3
	{
		#if PRINT_MEMBERSHIP_FUNCTIONS 
		std::cout << "   FuzzyTrapezoid x2 (" << x2 << ") < x (" << x << ") < x3 (" << x3 << ")" << std::endl;
		#endif
		return (-x / (x3 - x2)) + (x3 / (x3 - x2));
	}
}

#pragma endregion

#pragma region Logical Operators

float FuzzyModule::FuzzyAND(float a, float b)
{
	return std::min(a, b);
}

float FuzzyModule::FuzzyOR(float a, float b)
{
	return std::max(a, b);
}

#pragma endregion
