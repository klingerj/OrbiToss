// Fill out your copyright notice in the Description page of Project Settings.

#include "GameManager.h"
#include "UObject/ConstructorHelpers.h"


// Sets default values
AGameManager::AGameManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UBlueprint>Planet(TEXT("Blueprint'/Game/PlanetBP.PlanetBP'"));
	if (Planet.Object) {
		PlanetClass = (UClass*)Planet.Object->GeneratedClass;
	}

}

// Called when the game starts or when spawned
void AGameManager::BeginPlay()
{
	Super::BeginPlay();

	UWorld* const World = GetWorld();
	if (World) {
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = Instigator;

		FVector spawn(0, 0, 160);

		p = World->SpawnActor<APlanet>(PlanetClass, spawn, FRotator(0.0f));
	}
}

// Called every frame
void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

