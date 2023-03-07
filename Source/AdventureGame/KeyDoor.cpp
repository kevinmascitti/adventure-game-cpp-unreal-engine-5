// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyDoor.h"

#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AKeyDoor::AKeyDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// BOX COMPONENT
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	RootComponent = Box;

	// StaticMeshComponent - contiene la chiave
	KeyComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Key"));
	KeyComp->SetupAttachment(Box);
	KeyComp->SetWorldScale3D(FVector(0.04,0.04,0.04));
	KeyComp->SetRelativeLocation(FVector(-8.f,30.f,-30.f));

	// StaticMesh
	ConstructorHelpers::FObjectFinder<UStaticMesh> KeyObj(TEXT("StaticMesh'/Game/MAPS_ELEMENT/Meshes/KeyOK.KeyOK'"));
	if(KeyObj.Object)
	{
		Key = KeyObj.Object;
		KeyComp->SetStaticMesh(Key);
	}

	// PARTICLES

	ParticleComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Paricles FX"));
	ParticleComp->SetupAttachment(KeyComp);
	ParticleComp->bAutoActivate = false;
	
	// ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleObj(TEXT(""));
	// if(ParticleObj.Object)
	// {
	//	Particles = ParticleObj.Object;
	//	ParticleComp->SetTemplate(Particles);
	// }

	ConstructorHelpers::FObjectFinder<USoundWave>Audio0Obj(TEXT("SoundWave'/Game/Game/Audios/Effects/BipChiave.BipChiave'"));
	Audio0 = Audio0Obj.Object;
	
	Audios = {Audio0};
	
}

// Called when the game starts or when spawned
void AKeyDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKeyDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AKeyDoor::PlayAudio(const UObject* Object, FVector Location, int Ref)
{
	if(Ref == 0) // se non ho un pavimento specifico
		{
		if(Audios[Ref] != nullptr)
			UGameplayStatics::PlaySoundAtLocation(Object, Audios[Ref], Location);
		}
}

