// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Planet.h"
#include "Components/BoxComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Target.generated.h"

UCLASS()
class ORBITOSS_API ATarget : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATarget(const FObjectInitializer& objInit);

	// Coefficient of restitution
	const float e = 0.75;

	UBoxComponent* CollisionComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Target Collision")
	void bounce(AActor* OverlappedActor, AActor* OtherActor);
	
	UFUNCTION(BlueprintCallable, Category = "Target Collision")
	void HitByPlanet();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	bool beenHit;

};
