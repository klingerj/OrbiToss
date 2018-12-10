// Fill out your copyright notice in the Description page of Project Settings.

#include "Planet.h"
#include "Target.h"

// Sets default values
APlanet::APlanet(const FObjectInitializer& objInit) : Super(objInit), mass(rand() % 100 + 1), radius(rand() % 3001 + 4000), considerForce(false), pos(500, 0, 0), vel(0, 50, 0), acc(0, 0, 0), force(0, 0, 0)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//UE_LOG(LogClass, Log, TEXT("Consider force?????? %d"), considerForce);
	/*CollisionComp = objInit.CreateDefaultSubobject<USphereComponent>(this, TEXT("SphereComponent"));
	CollisionComp->InitSphereRadius(15.f);
	CollisionComp->SetSimulatePhysics(false);
	CollisionComp->SetEnableGravity(false);
	CollisionComp->SetNotifyRigidBodyCollision(true);
	CollisionComp->SetCollisionProfileName(TEXT("OverlapAll"));
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	RootComponent = CollisionComp;*/

	//ProjectileMovement = objInit.CreateDefaultSubobject<UProjectileMovementComponent>(this, TEXT("ProjectileComp"));
	//ProjectileMovement->UpdatedComponent = CollisionComp;
	//ProjectileMovement->InitialSpeed = 100.f;
	//ProjectileMovement->MaxSpeed = 100.f;
	//ProjectileMovement->bRotationFollowsVelocity = true;
	//ProjectileMovement->bShouldBounce = true;
	//ProjectileMovement->ProjectileGravityScale = 0.0f;

	//SetActorEnableCollision(true);
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
	//UE_LOG(LogClass, Log, TEXT("Consider force? %d"), considerForce);
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

		/*CollisionComp->AddForce(force, NAME_None, false);*/

		//UWorld* const world = GetWorld();
		//if (world) {
		//	CollisionComp->AddForce(force, NAME_None, false);
		//}
	}
	// Euler integration
	acc = FVector(0, 0, 0); //force / mass;
	vel = vel + acc * DeltaTime;
	pos = pos + vel * DeltaTime;

	// Update position and velocity accordingly
	GetRootComponent()->ComponentVelocity = vel;
	SetActorLocation(pos);
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
