// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Planet.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Target.generated.h"

UCLASS()
class ORBITOSS_API ATarget : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATarget();

	// Coefficient of restitution
	const float e = 0.75;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION() void bounce(AActor* SelfActor, class AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);
	
};
