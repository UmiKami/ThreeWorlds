// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "KismetTraceUtils.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Spring Arm"));

	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));

	Camera->SetupAttachment(SpringArm);

	Sword = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SwordCompt"));
	
	Sword->SetupAttachment(GetMesh(), TEXT("S_SwordR_v2"));
}


void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	SetupInputMappingContext();

	// CurrentHealth = MaxHealth;
}


void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	Input->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &APlayerCharacter::MoveForward);
	Input->BindAction(LookUpAction, ETriggerEvent::Triggered, this, &APlayerCharacter::LookUp);
	Input->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &APlayerCharacter::MoveRight);
	Input->BindAction(LookRightAction, ETriggerEvent::Triggered, this, &APlayerCharacter::LookRight);
	Input->BindAction(JumpAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Jump);
	Input->BindAction(CameraScrollDistanceAction, ETriggerEvent::Triggered, this, &APlayerCharacter::CameraScroll);
	Input->BindAction(BasicAttackAction, ETriggerEvent::Triggered, this, &APlayerCharacter::BasicAttack);
	
}

void APlayerCharacter::HitDetect() 
{
	
	if (Sword && Sword->GetStaticMesh() == nullptr) 
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid Sword reference"));
		return;
	}
	
	if (HitObjectTypes.Num() <= 0)
	{
		UE_LOG(LogTemp, Error, TEXT("No hit object types defined"));
		return;
	}

	FVector HitStart = Sword->GetSocketLocation(TEXT("start"));
	FVector HitEnd = Sword->GetSocketLocation(TEXT("end"));

	FHitResult HitResult;
	TArray<AActor*> ValidActorsToIgnore;
    
	// Filter out invalid actors
	for (AActor* Actor : ActorsToIgnore)
	{
		if (IsValid(Actor))
		{
			ValidActorsToIgnore.Add(Actor);
		}
	}
    
	bool hit = UKismetSystemLibrary::SphereTraceSingleForObjects(
		GetWorld(), 
		HitStart, 
		HitEnd, 
		10, 
		HitObjectTypes, 
		false, 
		ValidActorsToIgnore,  
		EDrawDebugTrace::None, 
		HitResult, 
		true
	);
    
	if (hit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Other actor: %s"), *HitResult.GetActor()->GetActorNameOrLabel());

		ABaseCharacter* OtherActor = Cast<ABaseCharacter>(HitResult.GetActor());

		if (OtherActor)
		{
			OtherActor->HitReact();

			float RandomizedDamage = FMath::RandRange(SwordDamage * 0.10f, SwordDamage);
			
			UGameplayStatics::ApplyDamage(OtherActor, RandomizedDamage, GetController(), this, nullptr);
		}
	}
}

void APlayerCharacter::Falling()
{
	Super::Falling();
	
	AttackCounter = 0;
	IsAttacking = false;
}

void APlayerCharacter::BasicAttack(const FInputActionValue& Value)
{
	if (!IsAttacking && !GetMovementComponent()->IsFalling())
	{
		IsAttacking = true;

		// UE_LOG(LogTemp, Warning, TEXT("Counter: %d"), AttackCounter);

		UAnimMontage* NextAttack = AttackMontage1;

		switch (AttackCounter)
		{
			case 0:
				NextAttack = AttackMontage1;
				break;
			case 1:
				NextAttack = AttackMontage2;
				break;
			default:
				NextAttack = AttackMontage1;
				AttackCounter = 0;
				break;
		}
		
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		
		
		if (NextAttack)
		{
			float DidAnimPlay = PlayAnimMontage(NextAttack);
			
			if (!DidAnimPlay)
			{
				UE_LOG(LogTemp, Error, TEXT("Basic Combo Attack Failed to Play"));
			}
			
			AnimInstance->Montage_SetPlayRate(NextAttack, 1.5);

			
		}
	}
	
}




void APlayerCharacter::SetIsAttacking(UAnimMontage* Montage, bool bInterrupted)
{
	AttackCounter = (AttackCounter + 1) % 2;
	
	IsAttacking = false;
}

void APlayerCharacter::MoveForward(const FInputActionValue& Value)
{
	float AxisValue = Value.Get<float>();

	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void APlayerCharacter::LookUp(const FInputActionValue& Value)
{
	float AxisValue = Value.Get<float>();
	
	AddControllerPitchInput(-AxisValue);
}

void APlayerCharacter::MoveRight(const FInputActionValue& Value)
{
	float AxisValue = Value.Get<float>();
    
    AddMovementInput(GetActorRightVector() * AxisValue);
}

void APlayerCharacter::LookRight(const FInputActionValue& Value)
{
	float AxisValue = Value.Get<float>();

	AddControllerYawInput(AxisValue);
}

void APlayerCharacter::CameraScroll(const FInputActionValue& Value)
{
	float ScrollValueScalar = -Value.Get<float>();

	if (SpringArm)
	{
		float TargetArmLength = SpringArm->TargetArmLength;


		MinScrollDistance = 100;
		MaxScrollDistance = 600;
		
		if (TargetArmLength >= MinScrollDistance && TargetArmLength <= MaxScrollDistance)
		{
			SpringArm->TargetArmLength += CameraScrollAmount * ScrollValueScalar;

			if (SpringArm->TargetArmLength < MinScrollDistance)
			{
				SpringArm->TargetArmLength = MinScrollDistance;
			}

			if (SpringArm->TargetArmLength > MaxScrollDistance)
			{
				SpringArm->TargetArmLength = MaxScrollDistance;
				
			}
			
		}
	}

}

void APlayerCharacter::SetupInputMappingContext()
{
	PlayerController = Cast<APlayerController>(GetController());

	if (PlayerController)
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			if (!InputMapping.IsNull())
			{
				InputSystem->AddMappingContext(InputMapping.LoadSynchronous(), 0);
			}
		}
	}
}
