// Fill out your copyright notice in the Description page of Project Settings.

#include "Target.h"


// Sets default values
ATarget::ATarget(const FObjectInitializer& objInit) : Super(objInit), beenHit(false)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = objInit.CreateDefaultSubobject<UBoxComponent>(this, TEXT("BoxComp"));
	CollisionComp->InitBoxExtent(FVector(50.f, 50.f, 10.f));
	CollisionComp->SetSimulatePhysics(false);
	CollisionComp->SetEnableGravity(false);
	CollisionComp->SetNotifyRigidBodyCollision(true);
	CollisionComp->SetCollisionProfileName(TEXT("OverlapAll"));
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	RootComponent = CollisionComp;

	SetActorEnableCollision(true);
}

// Called when the game starts or when spawned
void ATarget::BeginPlay()
{
	Super::BeginPlay();
	
	// Call bounce() when the target is hit
	CollisionComp->OnComponentHit.AddDynamic(this, &ATarget::bounce);
}

// Called every frame
void ATarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Ensure the targets don't move
	GetRootComponent()->ComponentVelocity = FVector(0, 0, 0);

}

// TODO: The collision isn't triggering for some reason?
void ATarget::bounce(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {
	if (OtherActor && (OtherActor != this) && OtherActor->IsA(APlanet::StaticClass())) {
		UE_LOG(LogClass, Log, TEXT("TARGET COLLISION"));
		// Handle collision
		// GetActorRotation() returns as [pitch, roll, yaw]
		// R's columns are the coordinate axes of the target expressed in world coordinates
		FRotationMatrix R(GetActorRotation());
		FMatrix worldToBody = R.Inverse();

		// Post-collision velocity
		FVector outvel(0, 0, 0);

		// Loop over xy, yz, xz planes to get total resultant velocity
		//for (int i = 0; i < 3; ++i) {
		//	// Unit vector tangential to the target in this plane, in world space
		//	FVector tHat = R.GetColumn(i);
		//	if (tHat.Size() != 1) {
		//		tHat.Normalize();
		//	}

		//	// Unit vector normal to the target in this plane, in world space
		//	FVector nHat = R.GetColumn((i + 1) % 3);
		//	if (nHat.Size() != 1) {
		//		nHat.Normalize();
		//	}

		//	// Resulting velocity in world space; velocities in the normal direction get scaled by the COR
		//	FVector outVel = FVector::DotProduct(OtherActor->GetVelocity(), tHat) * tHat + e * FVector::DotProduct(OtherActor->GetVelocity(), nHat) * nHat;

		//	// Accumulate velocity
		//	totalV += outVel;
		//}

		// Based on glm::reflect(); initial surface normal = [0, 0, 1], so grab the Z axis from R
		FVector surfaceNormal = R.GetUnitAxis(EAxis::Z);
		surfaceNormal.Normalize();

		FVector invel = OtherActor->GetVelocity();

		// Outgoing vector
		outvel = invel - 2.0 * FVector::DotProduct(invel, surfaceNormal) * surfaceNormal;
		

		// If this target's yet to be hit, set it as such
		if (!beenHit) {
			beenHit = true;
			// TODO: numTargetsHit++;
		}

		// Set resultant velocity
		OtherActor->GetRootComponent()->ComponentVelocity = outvel;
	}
}

