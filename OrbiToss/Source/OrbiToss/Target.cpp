// Fill out your copyright notice in the Description page of Project Settings.

#include "Target.h"


// Sets default values
ATarget::ATarget(const FObjectInitializer& objInit) : Super(objInit)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = objInit.CreateDefaultSubobject<USphereComponent>(this, TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(0.3f);
	CollisionComp->SetSimulatePhysics(false);
	CollisionComp->SetEnableGravity(false);
	CollisionComp->SetNotifyRigidBodyCollision(true);
	CollisionComp->SetCollisionProfileName(TEXT("OverlapAll"));
	RootComponent = CollisionComp;

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

// TODO: Something's wrong in here, but idk what; weirdness happens even without the velocity set, though.
	// Maybe it's just the hit boxes?
void ATarget::bounce(AActor* SelfActor, class AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit) {
	if (OtherActor && (OtherActor != this) && OtherActor->IsA(APlanet::StaticClass())) {
		// Handle collision
		// GetActorRotation() returns as [pitch, roll, yaw]
		// R goes from body to world space; we want the inverse of this
		FRotationMatrix R(GetActorRotation());
		FMatrix worldToBody = R.Inverse();

		// Cumulative post-collision velocity
		FVector totalV(0, 0, 0);

		// Loop over xy, yz, xz planes to get total resultant velocity
		for (int i = 0; i < 3; ++i) {
			// Unit vector tangential to the target in this plane, in world space
			FVector tHat = R.GetColumn(i);
			if (tHat.Size() != 1) {
				tHat.Normalize();
			}

			// Unit vector normal to the target in this plane, in world space
			FVector nHat = R.GetColumn((i + 1) % 3);
			if (nHat.Size() != 1) {
				nHat.Normalize();
			}

			// Resulting velocity in world space; velocities in the normal direction get scaled by the COR
			FVector outVel = FVector::DotProduct(OtherActor->GetVelocity(), tHat) * tHat + e * FVector::DotProduct(OtherActor->GetVelocity(), nHat) * nHat;

			// Accumulate velocity
			totalV += outVel;
		}

		// Set resultant velocity
		OtherActor->GetRootComponent()->ComponentVelocity = totalV;
	}
}

