// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Boss.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAttackEnd);

UCLASS()
class THREEWORLDS_API ABoss : public ABaseCharacter
{
	GENERATED_BODY()
public:	
	ABoss();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category="Animation")
	UAnimMontage* PunchMontage;

	UPROPERTY(EditAnywhere, Category="Combat")
	TArray<TEnumAsByte<EObjectTypeQuery>> HitObjectTypes;

	TArray<AActor*> ActorsToIgnore = {this};

	UPROPERTY(EditAnywhere, Category="Combat")
	float PunchDamage = 10;


public:
	virtual float TakeDamage(float Damage, const FDamageEvent& DamageEvent, AController* EventInstigator,
		AActor* DamageCauser) override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void MontageEnded(UAnimMontage* Montage, bool bInterrupted);
	
	UFUNCTION(BlueprintCallable)
	void Punch();
	
	UFUNCTION(BlueprintCallable)
	void HitDetection();

	UFUNCTION(BlueprintCallable)
	void LaserAttack();

	UFUNCTION(BlueprintCallable)
	void VortexProjectileAttack();

	UPROPERTY(BlueprintAssignable, Category="Event Dispatcher")
	FAttackEnd OnAttackEnd;
};
