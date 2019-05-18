//
// FuzzyModule.h
// Copyright © 2018 Diel Barnes. All rights reserved.
//

#ifndef FUZZYMODULE_H
#define FUZZYMODULE_H

#include <algorithm>
#include "AIModule.h"

class FuzzyModule : public AIModule
{
public:
	FuzzyModule();
	~FuzzyModule();

	float GetCarSteeringFactor();

private:
	void DidSetMaxValues();

	// Distance
	float m_fFarLeftX0;
	float m_fFarLeftX1;
	float m_fMediumLeftX0;
	float m_fMediumLeftX1;
	float m_fMediumLeftX2;
	float m_fMediumLeftX3;
	float m_fCloseX0;
	float m_fCloseX1;
	float m_fCloseX2;
	float m_fMediumRightX0;
	float m_fMediumRightX1;
	float m_fMediumRightX2;
	float m_fMediumRightX3;
	float m_fFarRightX0;
	float m_fFarRightX1;

	// Rate of change of distance
	float m_fFastLeftX0;
	float m_fFastLeftX1;
	float m_fLeftX0;
	float m_fLeftX1;
	float m_fLeftX2;
	float m_fLeftX3;
	float m_fNoMovementX0;
	float m_fNoMovementX1;
	float m_fNoMovementX2;
	float m_fRightX0;
	float m_fRightX1;
	float m_fRightX2;
	float m_fRightX3;
	float m_fFastRightX0;
	float m_fFastRightX1;

	// Output (steering factor)
	float m_fOutputFastLeftX0;
	float m_fOutputFastLeftX1;
	float m_fOutputLeftX0;
	float m_fOutputLeftX1;
	float m_fOutputLeftX2;
	float m_fOutputLeftX3;
	float m_fOutputNoMovementX0;
	float m_fOutputNoMovementX1;
	float m_fOutputNoMovementX2;
	float m_fOutputRightX0;
	float m_fOutputRightX1;
	float m_fOutputRightX2;
	float m_fOutputRightX3;
	float m_fOutputFastRightX0;
	float m_fOutputFastRightX1;

	// Fuzzy rules
	float GetOutputFastLeftDegree(float fFarLeftDegree, float fFastLeftDegree, float fLeftDegree, float fNoMovementDegree, float fRightDegree, float fMediumLeftDegree);
	float GetOutputLeftDegree(float fFarLeftDegree, float fFastRightDegree, float fMediumLeftDegree, float fLeftDegree, float fNoMovementDegree, float fRightDegree, float fCloseDegree, float fFastLeftDegree);
	float GetOutputNoMovementDegree(float fMediumLeftDegree, float fFastRightDegree, float fCloseDegree, float fLeftDegree, float fNoMovementDegree, float fRightDegree, float fMediumRightDegree, float fFastLeftDegree);
	float GetOutputRightDegree(float fCloseDegree, float fFastRightDegree, float fMediumRightDegree, float fLeftDegree, float fNoMovementDegree, float fRightDegree, float fFarRightDegree, float fFastLeftDegree);
	float GetOutputFastRightDegree(float fMediumRightDegree, float fFastRightDegree, float fFarRightDegree, float fLeftDegree, float fNoMovementDegree, float fRightDegree);

	// Membership functions
	float FuzzyGrade(float x, float x0, float x1);
	float FuzzyReverseGrade(float x, float x0, float x1);
	float FuzzyTriangle(float x, float x0, float x1, float x2);
	float FuzzyTrapezoid(float x, float x0, float x1, float x2, float x3);

	// Logical Operators
	float FuzzyAND(float a, float b);
	float FuzzyOR(float a, float b);
};

#endif
