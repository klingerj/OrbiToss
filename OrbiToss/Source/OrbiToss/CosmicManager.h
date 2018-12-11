// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GoalStar.h"
#include "Kismet/GameplayStatics.h"
#include <vector>

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CosmicManager.generated.h"

class APlanet;

UCLASS()
class ORBITOSS_API ACosmicManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACosmicManager();

    std::vector<APlanet*> planets;
    std::vector<AStar*> stars;
    std::vector<AGoalStar*> goalStars;

    int numCompleteGoals;
    int numTargetsHit;
    int numTargetsRequired;

    int levelID;
    static int id;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
