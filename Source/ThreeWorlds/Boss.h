// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "Boss.generated.h"

/**
 * 
 */
UCLASS()
class THREEWORLDS_API ABoss : public ABaseCharacter
{
	GENERATED_BODY()
public:	
	ABoss();

protected:
	virtual void BeginPlay() override;

public:
	virtual float TakeDamage(float Damage, const FDamageEvent& DamageEvent, AController* EventInstigator,
		AActor* DamageCauser) override;
};
