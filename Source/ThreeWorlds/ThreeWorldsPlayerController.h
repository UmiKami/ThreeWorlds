// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ThreeWorldsPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class THREEWORLDS_API AThreeWorldsPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category="UI")
	TSubclassOf<UUserWidget> HealthBarUI;
};
