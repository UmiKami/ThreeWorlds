// Fill out your copyright notice in the Description page of Project Settings.

/*
* This is the base for the player character, the bosses, and any derivatives.
* */


#include "BaseCharacter.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseCharacter::HitReact()
{
	if (HitReactMontageList.Num() > 0)
	{
		UAnimMontage* HitReactMontage = HitReactMontageList[FMath::RandRange(0, HitReactMontageList.Num() - 1)];
		float AnimDuration = PlayAnimMontage(HitReactMontage);

		if (AnimDuration == 0.f)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to play Hit react montage"));
		}
		
	}
}

float ABaseCharacter::TakeDamage(float Damage, const FDamageEvent& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	
	DamageToApply = FMath::Min(DamageToApply, CurrentHealth);
	
	CurrentHealth -= DamageToApply;

	return DamageToApply;
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

bool ABaseCharacter::IsDead() const
{
	return CurrentHealth < 0;
}

float ABaseCharacter::GetHealth() const
{
	return CurrentHealth / MaxHealth;
}

float ABaseCharacter::GetMaxHealth() const
{
	return MaxHealth;
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}