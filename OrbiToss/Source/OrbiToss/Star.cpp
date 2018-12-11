// Fill out your copyright notice in the Description page of Project Settings.

#include "Star.h"


// Sets default values
AStar::AStar() : pos(375, 0, 370), mass(/*rand() % 15001 +*/ 20000), radius(rand() % 10001 + 1000)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    // Make sure the stars don't move
    GetRootComponent()->ComponentVelocity = FVector(0, 0, 0);
}
