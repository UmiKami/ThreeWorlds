// Fill out your copyright notice in the Description page of Project Settings.


#include "ThreeWorldsPlayerController.h"

#include "Blueprint/UserWidget.h"

void AThreeWorldsPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (HealthBarUI)
	{
		UUserWidget* HUDScreen = CreateWidget(this, HealthBarUI);

		HUDScreen->AddToViewport();
	}
}
