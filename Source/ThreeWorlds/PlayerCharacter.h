// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "PlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
class UUserWidget;
/**
 * 
 */
UCLASS()
class THREEWORLDS_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()
public:
	APlayerCharacter();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat Properties")
	TObjectPtr<UStaticMeshComponent> Sword;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* AttackMontage1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* AttackMontage2;

	UFUNCTION(Blueprintable, BlueprintCallable)
	void SetIsAttacking(UAnimMontage* Montage, bool bInterrupted);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void HitDetect();
	
	UPROPERTY(EditAnywhere)
	TArray<TEnumAsByte<EObjectTypeQuery>> HitObjectTypes;

	virtual void Falling() override;


private:
	UPROPERTY(EditAnywhere, Category="Input")
	TSoftObjectPtr<UInputMappingContext> InputMapping;

	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MoveForwardAction;

	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* LookUpAction;
	
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MoveRightAction;

	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* LookRightAction;
	
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* BasicAttackAction;

	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* CameraScrollDistanceAction;

private:
	APlayerController* PlayerController;

	UPROPERTY(EditAnywhere, Category="Player Camera")
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, Category="Player Camera")
	UCameraComponent* Camera;
	
	UPROPERTY(EditAnywhere, Category="Player Camera")
	int MinScrollDistance = 100;
	
	UPROPERTY(EditAnywhere, Category="Player Camera")
	int MaxScrollDistance = 600;
	
	
	TArray<AActor*> ActorsToIgnore = {this};
	
	void MoveForward(const FInputActionValue& Value);
	void LookUp(const FInputActionValue& Value);
	void MoveRight(const FInputActionValue& Value);
	void LookRight(const FInputActionValue& Value);
	void CameraScroll(const FInputActionValue& Value);
	
	void BasicAttack(const FInputActionValue& Value);
	
	float CameraScrollAmount = 10;

	int AttackCounter = 0;
	bool IsAttacking = false;

	UPROPERTY(EditAnywhere)
	float SwordDamage = 10;
	
	void SetupInputMappingContext();
};
