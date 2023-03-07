// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Anim1.generated.h"

/**
 * 
 */
UCLASS()
class ADVENTUREGAME_API UAnim1 : public UAnimNotify
{
	GENERATED_BODY()

public:
	UAnim1();

protected:
	virtual void Notify(USkeletalMeshComponent* MeshComponent, UAnimSequenceBase* Animation) override;
	
	USoundWave* Audio0;
	USoundWave* Audio1;
	USoundWave* Audio2;
	
	TArray<USoundWave*> Audios;
	
	UPROPERTY(EditAnywhere)
	bool GetSurface;

	UPROPERTY(EditAnywhere)
	int Audio = -1;
	
	void PlayAudio(const UObject* Object, FVector Location, int Ref);
	int GetPMaterial(USkeletalMeshComponent* MeshComponent);
};
