// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "KeyDoor.generated.h"

UCLASS()
class ADVENTUREGAME_API AKeyDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKeyDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Key")
	UBoxComponent* Box;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Key")
	UStaticMeshComponent* KeyComp;
	
	UStaticMesh* Key;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Key")
	UParticleSystemComponent* ParticleComp;

	UParticleSystem* Particles;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Key")
	USoundWave* Audio0;
	TArray<USoundWave*> Audios;
	void PlayAudio(const UObject* Object, FVector Location, int Ref);
	
};
