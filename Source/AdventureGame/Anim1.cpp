// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim1.h"

#include "AdventureGame.h"
#include "PlayerBase.h"
#include "SAdvancedTransformInputBox.h"
#include "../../../../../../Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/clang/13.1.6/include/stddef.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

UAnim1::UAnim1()
{
	ConstructorHelpers::FObjectFinder<USoundWave>Audio0Obj(TEXT("SoundWave'/Game/Game/Audios/Footsteps/FootsetpCeramique.FootsetpCeramique'"));
	Audio0 = Audio0Obj.Object;
	ConstructorHelpers::FObjectFinder<USoundWave>Audio1Obj(TEXT("SoundWave'/Game/Game/Audios/Footsteps/FootsetpConcrete.FootsetpConcrete'"));
	Audio1 = Audio1Obj.Object;
	ConstructorHelpers::FObjectFinder<USoundWave>Audio2Obj(TEXT("SoundWave'/Game/Game/Audios/Footsteps/FootsetpWood.FootsetpWood'"));
	Audio2 = Audio2Obj.Object;
	
	Audios = {Audio0, Audio1, Audio2};
}

void UAnim1::Notify(USkeletalMeshComponent* MeshComponent, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComponent, Animation);

	if(!MeshComponent) return;

	FString AnimName = Animation->GetName();
	FString ClassName = MeshComponent->GetOwner()->GetClass()->GetName();

	UE_LOG(LogTemp, Warning, TEXT("Notify: AnimName = %s"), *AnimName);
	UE_LOG(LogTemp, Warning, TEXT("Notify: ClassName = %s"), *ClassName);
	// AActor*  Actor = MeshComponent->GetOwner();
	// APlayerBase Player = Cast<APlayerBase>(Actor);
	
	FVector Location = MeshComponent->GetOwner()->GetActorLocation();
	
	if(GetSurface)
	{
		int N = GetPMaterial(MeshComponent);
		PlayAudio(MeshComponent, Location, N);
	}
	else
	{
		PlayAudio(MeshComponent, Location, Audio);
	}
}

/**
 * Permette di instanziare un suono in un luogo ben preciso
 * @brief 
 * @param Object 
 * @param Location 
 * @param Ref 
 */
void UAnim1::PlayAudio(const UObject* Object, FVector Location, int Ref)
{
	if(Ref>-1 && Ref<3) // se non ho un pavimento specifico
	{
		if(Audios[Ref] != nullptr)
			UGameplayStatics::PlaySoundAtLocation(Object, Audios[Ref], Location);
	}
}

int UAnim1::GetPMaterial(USkeletalMeshComponent* MeshComponent)
{
	// Punto di partenza del suono
	FVector Start = MeshComponent->GetComponentLocation();
	
	FVector Forward = MeshComponent->GetOwner()->GetActorForwardVector();
	Start += Forward*50.f;
	Start.Z += 30.f;

	FVector End = Start;
	End.Z -= 1000.f;

	FHitResult HitResult;
	FCollisionQueryParams InfoProperties;
	InfoProperties.AddIgnoredActor(MeshComponent->GetOwner());
	InfoProperties.bReturnPhysicalMaterial = true;

	// DrawDebugLine(MeshComponent->GetOwner()->GetWorld(), Start, End, EColor::Red, false, 5.f, (uint8) 0, 5.f);

	// Definisce il raggio per ottenere il tipo di suolo sotto il personaggio
	MeshComponent->GetOwner()->GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_Visibility, InfoProperties);

	int nMat = 1;

	if(HitResult.GetActor())
	{
		UPhysicalMaterial* PH = HitResult.PhysMaterial.Get();

		if(PH)
		{
			if(PH->SurfaceType == EPS_Concrete)
				nMat = 0;
			if(PH->SurfaceType == EPS_Tile)
				nMat = 1;
			if(PH->SurfaceType == EPS_Wood)
				nMat = 2;
		}
	}
	
	return nMat;
}
