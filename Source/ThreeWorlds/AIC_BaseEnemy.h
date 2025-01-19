// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIC_BaseEnemy.generated.h"

/**
 * 
 */
UCLASS()
class THREEWORLDS_API AAIC_BaseEnemy : public AAIController
{
	GENERATED_BODY()

public:
	AAIC_BaseEnemy();

private:
	
	UPROPERTY(EditAnywhere)
	UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere)
	FName AttackTargetKeyName;
	
	FTimerHandle DelayHandle;

	void RunBehTree();

protected:
	virtual void OnPossess(APawn* InPawn) override;
};
