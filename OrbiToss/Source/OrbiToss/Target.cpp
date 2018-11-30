// Fill out your copyright notice in the Description page of Project Settings.

#include "Target.h"


// Sets default values
ATarget::ATarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetActorEnableCollision(true);
}

// Called when the game starts or when spawned
void ATarget::BeginPlay()
{
	Super::BeginPlay();
	
	// Call bounce() when the target is hit
	OnActorHit.AddDynamic(this, &ATarget::bounce);
}

// Called every frame
void ATarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Ensure the targets don't move
	GetRootComponent()->ComponentVelocity = FVector(0, 0, 0);

}

void ATarget::bounce(AActor* SelfActor, class AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit) {
	if (OtherActor && (OtherActor != this) && OtherActor->IsA(APlanet::StaticClass())) {
		// Handle collision
		// GetActorRotation() returns as [pitch, roll, yaw] (Y, X, Z)
		FRotationMatrix R(GetActorRotation());

		// Cumulative post-collision velocity
		FVector totalV(0, 0, 0);

		// Loop over xy, yz, xz planes to get total resultant velocity
		for (int i = 0; i < 3; ++i) {
			// Unit vector tangential to the target in this plane, in world space
			FVector tHat = R.GetColumn(i);

			// Unit vector normal to the target in this plane, in world space
			FVector nHat = R.GetColumn((i + 1) % 3);

			// Initial velocity in our plane
			FVector inVel(OtherActor->GetVelocity()[i], OtherActor->GetVelocity()[(i + 1) % 3], 0);

			// Unit vector representing the planet's velocity
			FVector vHat(inVel);
			vHat.Normalize();

			// Angle of collision
			float alpha = FVector::DotProduct(vHat, tHat);

			// Resulting velocity in body space
			FVector outVel(inVel.Size() * cos(alpha), inVel.Size() * e * sin(alpha), 0);

			// Accumulate velocity
			totalV += outVel;
		}

		// Set resultant velocity
		OtherActor->GetRootComponent()->ComponentVelocity = totalV;
	}
}

