// Fill out your copyright notice in the Description page of Project Settings.

#include "Target.h"


// Sets default values
ATarget::ATarget(const FObjectInitializer& objInit) : Super(objInit), beenHit(false)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*CollisionComp = objInit.CreateDefaultSubobject<UBoxComponent>(this, TEXT("BoxComp"));
	CollisionComp->InitBoxExtent(FVector(50.f, 50.f, 10.f));
	CollisionComp->SetSimulatePhysics(false);
	CollisionComp->SetEnableGravity(false);
	CollisionComp->SetNotifyRigidBodyCollision(true);
	CollisionComp->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	RootComponent = CollisionComp;

	SetActorEnableCollision(true);*/
}

// Called when the game starts or when spawned
void ATarget::BeginPlay()
{
	Super::BeginPlay();
	
	// Call bounce() when the target is hit
	//CollisionComp->OnComponentHit.AddDynamic(this, &ATarget::bounce);
}

// Called every frame
void ATarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Ensure the targets don't move
	GetRootComponent()->ComponentVelocity = FVector(0, 0, 0);

}

// TODO: The collision isn't triggering for some reason?
void ATarget::bounce(AActor* OverlappedActor, AActor* OtherActor) {

}

void ATarget::HitByPlanet() {
	if (!beenHit) {
		beenHit = true;
		// TODO: numTargetsHit++;
	}
}
