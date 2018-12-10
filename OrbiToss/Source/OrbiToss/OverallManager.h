// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OverallManager.generated.h"

UCLASS()
class ORBITOSS_API AOverallManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOverallManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Completion State")
    bool level1Complete;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Completion State")
    bool level2Complete;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Completion State")
    bool level3Complete;
};
