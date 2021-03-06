// Fill out your copyright notice in the Description page of Project Settings.

#include "CosmicManager.h"
#include "Planet.h"
#include "OverallManager.h"

int ACosmicManager::id = 0;

// Sets default values
ACosmicManager::ACosmicManager() : numCompleteGoals(0), optimalSolution(0), numPlanetsUsed(0), numTargetsHit(0), numTargetsRequired(0), levelID(id++)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACosmicManager::BeginPlay()
{
	Super::BeginPlay();

    //UIntProperty* IntPropPlanets = FindField<UIntProperty>(PlayerBP)
	
    TArray<AActor*> FoundStars;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AStar::StaticClass(), FoundStars);
    for (AActor* s : FoundStars) {
        stars.push_back((AStar*) s);
        if (dynamic_cast<AGoalStar*>(s))
        {
            goalStars.push_back((AGoalStar*) s);
        }
    }

    TArray<AActor*> FoundPlanets;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlanet::StaticClass(), FoundPlanets);
    for (AActor* p : FoundPlanets) {
        planets.push_back((APlanet*) p);
    }

    TArray<AActor*> FoundTargets;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATarget::StaticClass(), FoundTargets);
    for (AActor* t : FoundTargets) {
        targets.push_back((ATarget*) t);
    }
    numTargetsRequired = targets.size();
}

// Called every frame
void ACosmicManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    for (int i = 0; i < goalStars.size(); ++i) {
        AGoalStar* curr = goalStars.at(i);
        if (curr->numPlanetsOrbiting == curr->numPlanetsRequired && !curr->completionChecked) {
            curr->completionChecked = true;
            numCompleteGoals++;
        }
    }

    int hitCount = 0;
    for (int i = 0; i < targets.size(); ++i) {
        ATarget* curr = targets.at(i);
        if (curr->beenHit) {
            hitCount++;
        }
    }
    numTargetsHit = (hitCount > numTargetsHit) ? (hitCount) : (numTargetsHit);

    if (numCompleteGoals == goalStars.size() && numTargetsHit == numTargetsRequired) {
        
        TArray<AActor*> OverallManagers;
        UGameplayStatics::GetAllActorsOfClass(GetWorld(), AOverallManager::StaticClass(), OverallManagers);
        for (AActor* m : OverallManagers) {
            switch(levelID) {
            case 0:
                static_cast<AOverallManager*>(m)->level1Score = optimalSolution - numPlanetsUsed;
                static_cast<AOverallManager*>(m)->level1Complete = true;
                break;
            case 1:
                static_cast<AOverallManager*>(m)->level2Score = optimalSolution - numPlanetsUsed;
                static_cast<AOverallManager*>(m)->level2Complete = true;
                break;
            case 2:
                static_cast<AOverallManager*>(m)->level3Score = optimalSolution - numPlanetsUsed;
                static_cast<AOverallManager*>(m)->level3Complete = true;
                break;
            }
        }
    }
}
