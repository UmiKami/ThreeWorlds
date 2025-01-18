// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class THREEWORLDS_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category="Stats")
	float MaxHealth = 100;
	
	UPROPERTY(EditAnywhere, Category="Stats")
	float CurrentHealth = 0;
	
	UPROPERTY(EditAnywhere, Category = "Combat Events")
	TArray<UAnimMontage*> HitReactMontageList;
	
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float Damage, const FDamageEvent& DamageEvent, AController* EventInstigator,
		AActor* DamageCauser) override;
	
	UFUNCTION(BlueprintCallable)
	float GetHealth() const;
	
	UFUNCTION(BlueprintCallable)
	float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable)
	bool IsDead() const;

	UFUNCTION(BlueprintCallable, Category = "Combat Events")
	void HitReact();
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	
};
