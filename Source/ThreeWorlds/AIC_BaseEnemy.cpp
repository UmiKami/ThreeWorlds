// Fill out your copyright notice in the Description page of Project Settings.


#include "AIC_BaseEnemy.h"

#include "PlayerCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

AAIC_BaseEnemy::AAIC_BaseEnemy()
{
}


void AAIC_BaseEnemy::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	GetWorldTimerManager().SetTimer(DelayHandle, this, &AAIC_BaseEnemy::RunBehTree, .2f, false);
	
}


void AAIC_BaseEnemy::RunBehTree()
{
	
	GetWorldTimerManager().ClearTimer(DelayHandle);

	RunBehaviorTree(BehaviorTree);
	
	// UBlackboardComponent* BlackboardComponent = UAIBlueprintHelperLibrary::GetBlackboard(GetOwner());

	if (Blackboard)
	{
		UE_LOG(LogTemp, Warning, TEXT("Blackboard exists"));
		Blackboard->SetValueAsObject(AttackTargetKeyName, UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	}
}