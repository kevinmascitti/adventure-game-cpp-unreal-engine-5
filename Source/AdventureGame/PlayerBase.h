// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "PlayerBase.generated.h"

UCLASS()
class ADVENTUREGAME_API APlayerBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	float CapsuleRadius;
	float CapsuleHalfHeight;
	float JumpVelocity;
	float AirControlValue;
	float TheDeltaTime;

	bool IsGunVisible;
	bool IsCrouching;

protected:
	// Braccio della telecamera
	// per private: UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera", meta = (AllowPrivateAccess="true"))
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera")
	USpringArmComponent* ArmComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera")
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Custom")
	float MouseSpeedX;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Custom")
	float MouseSpeedY;
	
public:
	void FMoveToX(float Value);
	void FMoveToY(float Value);
	void FRotate(float Value);
	void FLookUpDown(float Value);
	void FZoom(float Value);
	void FToRun();
	void FNotToRun();
	void FToJump();
	// void FNotToJump();
	void FToCrouch();
	void FNotToCrouch();
	void FToArm();

	void GunCrouch();
	
	float VSpeed;
	float VCrouch;
	bool VIsInAir;

	// Movimento regolare
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=DEPRECATED_CHARACTER_MOVEMENT_RPC, meta=(AllowPrivateAccess="true"))
	float BaseMovementSpeed;
};
