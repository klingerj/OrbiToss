// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Star.h"
#include "GoalStar.generated.h"

/**
 * 
 */
UCLASS()
class ORBITOSS_API AGoalStar : public AStar
{
	GENERATED_BODY()
	
public:
    AGoalStar();

    int numPlanetsOrbiting;
    int numPlanetsRequired;
    bool completionChecked;
	
    virtual void Tick(float DeltaTime) override;
};
