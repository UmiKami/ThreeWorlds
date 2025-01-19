// Fill out your copyright notice in the Description page of Project Settings.


#include "Boss.h"

#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"


ABoss::ABoss()
{
}

void ABoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABoss::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
}

float ABoss::TakeDamage(float Damage, const FDamageEvent& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	float Damage1 = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);


	if (CurrentHealth <= 0)
	{
		// TODO what happens when health reaches 0 for the boss?
		
	}
	
	return  Damage1;
}



void ABoss::Punch()
{
	if (PunchMontage)
	{
		PlayAnimMontage(PunchMontage);

		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

		AnimInstance->OnMontageEnded.AddDynamic(this, &ABoss::MontageEnded);
	}
}


void ABoss::MontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (Montage == PunchMontage)
	{
		OnAttackEnd.Broadcast();
	}
}

void ABoss::HitDetection()
{
	
	FVector PunchStart = GetMesh()->GetBoneLocation("ik_hand_r");

	PunchStart -= FVector(30, 10, 0);

	FHitResult HitResult;
	
	bool hit = UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), PunchStart, PunchStart, 15, HitObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::None, HitResult, true);
	
	if (hit)
	{
		float RandomDamageRange = FMath::RandRange(PunchDamage * .4f, PunchDamage);
		
		UGameplayStatics::ApplyDamage(HitResult.GetActor(), RandomDamageRange, GetController(), this, nullptr);
	}
}

void ABoss::LaserAttack()
{
}

void ABoss::VortexProjectileAttack()
{
}
