// Fill out your copyright notice in the Description page of Project Settings.

#include "Planet.h"
#include "Target.h"

// Sets default values
APlanet::APlanet() : mass(rand() % 100 + 1), radius(rand() % 3001 + 4000), manager(nullptr), captureStar(nullptr), isCaptured(false), considerForce(true), pos(-195, -30, 100), vel(0, 0, 0), acc(0, 0, 0), force(0, 0, 0)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APlanet::BeginPlay()
{
	Super::BeginPlay();

    // Find and set the game manager
    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACosmicManager::StaticClass(), FoundActors);
    manager = (ACosmicManager*)FoundActors[0];

    // Add this planet to the list of tracked planets
    manager->planets.push_back(this);
}

// Called every frame
void APlanet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    if (!isCaptured) {
        if (considerForce) {
            force = FVector(0, 0, 0);
            for (int i = 0; i < manager->stars.size(); ++i)
            {
                FVector dist = pos - manager->stars.at(i)->pos;
                FVector dir = dist;
                dir.Normalize();
                force += -(G * mass * manager->stars.at(i)->mass) / (dist.Size() * dist.Size() * 0.01) * dir;
            }
            // Update position and velocity accordingly
            acc = force / mass;
            vel = vel + acc * DeltaTime;
            pos = pos + vel * DeltaTime;

            GetRootComponent()->ComponentVelocity = vel;
            SetActorLocation(pos);
        }

        // Check for capture
        for (int i = 0; i < manager->goalStars.size(); ++i) {
            AGoalStar* goal = manager->goalStars.at(i);
            FVector toGoal = pos - goal->pos;
            float orbit = goal->radius + goal->numPlanetsOrbiting * 30;
            if (toGoal.Size() <= orbit) {
                isCaptured = true;
                considerForce = false;
                captureStar = goal;
                goal->numPlanetsOrbiting++;

                float t = UGameplayStatics::GetTimeSeconds(GetWorld());
                FVector goalToPlanet = pos - captureStar->pos;
                goalToPlanet.Normalize();
                float theta = atan2(goalToPlanet.Y, goalToPlanet.X);
                float orbit = captureStar->radius + captureStar->numPlanetsOrbiting * 30;
                pos = captureStar->pos + FVector(orbit * cos(0.1 * (t - theta)), orbit * sin(0.1 * (t - theta)), 0);

                SetActorLocation(pos);
                vel = FVector(0);
                acc = FVector(0);
            }
        }
	}
    // The planet has been captured in a goal star's orbit
    else {
        // Make sure these are set appropriately
        considerForce = false;

        float t = UGameplayStatics::GetTimeSeconds(GetWorld());
        FVector goalToPlanet = pos - captureStar->pos;
        goalToPlanet.Normalize();
        float theta = atan2(goalToPlanet.Y, goalToPlanet.X);
        float orbit = captureStar->radius + captureStar->numPlanetsOrbiting * 30;
        pos = captureStar->pos + FVector(orbit * cos(0.5 * (t - theta)), orbit * sin(0.5 * (t - theta)), 0);

        SetActorLocation(pos);
        vel = FVector(0);
        acc = FVector(0);
    }
}

void APlanet::BounceOffTarget(ATarget* target) {
	FRotationMatrix R(target->GetActorRotation());
	FMatrix worldToBody = R.Inverse();

	// Post-collision velocity
	FVector outvel(0, 0, 0);

	// Based on glm::reflect(); initial surface normal = [0, 0, 1], so grab the Z axis from R
	FVector surfaceNormal = R.GetUnitAxis(EAxis::Z);
	surfaceNormal.Normalize();

	//FVector invel = vel;

	// Outgoing vector
	outvel = vel - 2.0 * FVector::DotProduct(vel, surfaceNormal) * surfaceNormal;
	FVector tmp = 2.0 * FVector::DotProduct(vel, surfaceNormal) * surfaceNormal;
    UE_LOG(LogClass, Log, TEXT("Intermediate vector: (%f, %f, %f)"), tmp[0], tmp[1], tmp[2])
		UE_LOG(LogClass, Log, TEXT("Surface normal: (%f, %f, %f)"), surfaceNormal[0], surfaceNormal[1], surfaceNormal[2])
	
	// Set resultant velocity
	//GetRootComponent()->ComponentVelocity = 10 * outvel;
	UE_LOG(LogClass, Log, TEXT("Velocity before collision was: (%f, %f, %f)"), vel[0], vel[1], vel[2]);
	vel = outvel;
	UE_LOG(LogClass, Log, TEXT("Velocity after collision is: (%f, %f, %f)"), vel[0], vel[1], vel[2]);
}
