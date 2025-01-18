// Fill out your copyright notice in the Description page of Project Settings.


#include "Boss.h"


ABoss::ABoss()
{
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
