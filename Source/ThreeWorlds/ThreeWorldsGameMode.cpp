// Copyright Epic Games, Inc. All Rights Reserved.

#include "ThreeWorldsGameMode.h"

#include "PlayerCharacter.h"
#include "UObject/ConstructorHelpers.h"

AThreeWorldsGameMode::AThreeWorldsGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<ACharacter> PlayerPawnBPClass(TEXT("/Game/Blueprints/Characters/BP_PlayerCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("Default Pawn Should Had been set"));
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
