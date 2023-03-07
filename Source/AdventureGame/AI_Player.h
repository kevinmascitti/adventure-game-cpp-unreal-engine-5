// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PlayerBase.h"
#include "CoreMinimal.h"
#include "PlayerBase.h"
#include "Animation/AnimInstance.h"
#include "AI_Player.generated.h"

/**
 * 
 */
UCLASS()
class ADVENTUREGAME_API UAI_Player : public UAnimInstance
{
	GENERATED_BODY()

	protected:
	// funzione che corrisponde al primo node dell'EventGraph dell'animation Blueprint (Event Blueprint Update Animation)
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	AActor* Actor;
	APlayerBase* PlayerBase;

	UPROPERTY(BlueprintReadOnly, Category="Conditions")
	float Speed;
	
	UPROPERTY(BlueprintReadOnly, Category="Conditions")
	float Crouch;

	UPROPERTY(BlueprintReadOnly, Category="Conditions")
	bool IsInAir;
};
