// Fill out your copyright notice in the Description page of Project Settings.

#include "Planet.h"


// Sets default values
APlanet::APlanet() : mass(rand() % 100 + 1), radius(rand() % 3001 + 4000), considerForce(false), pos(500, 0, 0), vel(0, 50, 0), acc(0, 0, 0), force(0, 0, 0)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetActorEnableCollision(true);

	AsteroidBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("RootComponent"));
	RootComponent = AsteroidBoxComponent;
	AsteroidBoxComponent->InitBoxExtent(FVector(12.0f, 15.0f, 12.0f));
	AsteroidBoxComponent->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	AsteroidBoxComponent->SetSimulatePhysics(false);
	AsteroidBoxComponent->SetEnableGravity(false);
	AsteroidBoxComponent->SetNotifyRigidBodyCollision(true);

}

// Called when the game starts or when spawned
void APlanet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlanet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (considerForce) {
		if (vel.Size() > 0) {
			// TODO: Query all active planets in some planet vector you create in GameManager
			// Create std::vector<APlanet> that stores all planets and loop over
				// if (considerForce && distanceBetween != 0)
					// totalForce += G*m1*m2 / (distanceBetween * distanceBetween)
		}

		// TEST: Have the planet orbit a nonexistent sun located at the origin
		FVector dist = pos - FVector(375, 0, 370); // Vector from sun to planet
		FVector dir = dist;
		dir.Normalize(); // Unit vector pointing from sun to planet
		force = -(G * mass * 20000) / (dist.Size() * dist.Size() * 0.01) * dir; // Apply Law of Universal Gravitation

		// Euler integration
		acc = FVector(0,0,0); //force / mass;
		vel = vel + acc * DeltaTime;
		pos = pos + vel * DeltaTime;

		// Update position and velocity accordingly
		GetRootComponent()->ComponentVelocity = vel;
		SetActorLocation(pos);
	}
}

