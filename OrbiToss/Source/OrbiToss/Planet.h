// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <cmath>

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Planet.generated.h"

UCLASS()
class ORBITOSS_API APlanet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlanet();

	// Universal Gravitational Constant, modified to fit our simulation
	const float G = 6.67408; // SI units: 6.67408e-11 m^3/(kg * s^2); this way, all forces will be returned as F * 10^31. We will drop the coefficient
	
	// Unchanging aspects of planet
	// Mass, in (10^24) kg
	float mass;
	// Radius, in (10^3) m
	float radius;

	// If true, consider this planet/body in the force calculations of other bodies
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Planet Physics")
	bool considerForce;

	// Changing aspects of planet
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Planet Physics")
	FVector pos; 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Planet Physics")
	FVector vel;

	FVector acc;
	FVector force;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
