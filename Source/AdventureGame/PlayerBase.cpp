// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBase.h"

// Sets default values
APlayerBase::APlayerBase():
CapsuleRadius(34.0f),
CapsuleHalfHeight(88.0f),
JumpVelocity(600.0f),
AirControlValue(0.2f),
IsGunVisible(false),
IsCrouching(false),
MouseSpeedX(10.f),
MouseSpeedY(10.f),
VSpeed(0.f),
VCrouch(100.f),
VIsInAir(false),
BaseMovementSpeed(300.f)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// CAPSULE COMPONENT
	//Radius
	GetCapsuleComponent()->SetCapsuleRadius(CapsuleRadius);

	// Halfheight
	GetCapsuleComponent()->SetCapsuleHalfHeight(CapsuleHalfHeight);

	// CHARACTER MOVEMENT
	GetCharacterMovement()->JumpZVelocity = JumpVelocity;

	// Controllo del personaggio in aria
	GetCharacterMovement()->AirControl = AirControlValue;

	// Il personaggio si gira in direzione dell'input
	GetCharacterMovement()->bOrientRotationToMovement = true;

	// Controller
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->MaxWalkSpeed = 300.f;

	// SKELETAL MESH COMPONENT
	// SkeletalMesh: '/Game/Game/Actors/FemalePirate/Pirate_By_P__Konstantinov.Pirate_By_P__Konstantinov'

	// Recuperare la reference della skeletal mesh
	ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshObj(TEXT("'/Game/Game/Actors/FemalePirate/Pirate_By_P__Konstantinov.Pirate_By_P__Konstantinov'"));
	if(MeshObj.Object)
	{
		GetMesh()->SetSkeletalMesh(MeshObj.Object);

		// Location dello SkeletalMeshComponent
		// Abbassare il personaggio per farlo corrispondere all'altezza della capsula
		GetMesh()->SetRelativeLocation(FVector(0.f,0.f,-87.0f));

		// rotazione dello SkeletalMeshComponent
		// Roteare il personaggio di 90 gradi verso sinistra verso la freccia blu
		// PITCH - YAN - ROLL = Y, Z, X
		GetMesh()->SetRelativeRotation(FRotator(0.f,-90.0f,0.f));

		// scale dello SkeletalMeshComponent
		GetMesh()->SetWorldScale3D(FVector(3.f));
		
	}
	// CAMERA
	ArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Arm Component"));
	// Attaccare l'elemento al root component. Di default il root component è la capsula di collisione
	ArmComp->SetupAttachment(RootComponent);
	// Giriamo il braccio con il controller
	ArmComp->bUsePawnControlRotation = true;
	// Telecamera non attraversa gli ostacoli
	// ArmComp->bDoCollisionTest = false
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment((ArmComp));

	// Camera si impossessa di default dell'actor per il player 0
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// ANIMATION
	// AnimBlueprint: '/Game/Game/Actors/FemalePirate/AI_Player_Pirate.AI_Player_Pirate'

	// Animation Mode
	// GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint); // default
	ConstructorHelpers::FObjectFinder<UBlueprint> BP(TEXT("'/Game/Game/Actors/FemalePirate/AI_Player_Pirate.AI_Player_Pirate'"));
	GetMesh()->AnimClass = BP.Object->GeneratedClass;
}

// Called when the game starts or when spawned
void APlayerBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TheDeltaTime=DeltaTime;

	// Controllo del salto
	VIsInAir=GetCharacterMovement()->IsFalling();
	
	// Recuperare la velocità di spostamento del personaggio
	FVector V = GetVelocity();
	VSpeed = V.Size();
}

// Called to bind functionality to input
void APlayerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// AXIS
	PlayerInputComponent->BindAxis("MoveToX", this, &APlayerBase::FMoveToX);
	PlayerInputComponent->BindAxis("MoveToY", this, &APlayerBase::FMoveToY);
	PlayerInputComponent->BindAxis("Rotate", this, &APlayerBase::FRotate);
	PlayerInputComponent->BindAxis("LookUpDown", this, &APlayerBase::FLookUpDown);
	PlayerInputComponent->BindAxis("Zoom", this, &APlayerBase::FZoom);

	// ACTION
	PlayerInputComponent->BindAction("ToRun", IE_Pressed, this, &APlayerBase::FToRun);
	PlayerInputComponent->BindAction("ToRun", IE_Released, this, &APlayerBase::FNotToRun);
	PlayerInputComponent->BindAction("ToJump", IE_Pressed, this, &APlayerBase::FToJump);
	// PlayerInputComponent->BindAction("ToJump", IE_Released, this, &APlayerBase::FNotToJump);
	PlayerInputComponent->BindAction("ToCrouch", IE_Pressed, this, &APlayerBase::FToCrouch);
	PlayerInputComponent->BindAction("ToCrouch", IE_Released, this, &APlayerBase::FNotToCrouch);
	
	PlayerInputComponent->BindAction("ToArm", IE_Pressed, this, &APlayerBase::FToArm);
	
}

void APlayerBase::FMoveToX(float Value)
{
	if(Controller && Value!=0.0f)
	{
		FRotator Rotation = Controller->GetControlRotation();
		FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
		FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void APlayerBase::FMoveToY(float Value)
{
	if(Controller && Value!=0.0f)
	{
		FRotator Rotation = Controller->GetControlRotation();
		FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
		FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void APlayerBase::FRotate(float Value)
{
	AddControllerYawInput(Value*MouseSpeedX*TheDeltaTime);
}

void APlayerBase::FLookUpDown(float Value)
{
	AddControllerPitchInput(Value*MouseSpeedY*TheDeltaTime);
}

void APlayerBase::FZoom(float Value)
{
	float F= ArmComp->TargetArmLength-(Value*40.f);
	if(F<130.f) F = 130.f;
	if(F>2000.f) F = 2000.f;
	ArmComp->TargetArmLength = F;
}

void APlayerBase::FToRun()
{
	GetCharacterMovement()->MaxWalkSpeed=600.f;
}

void APlayerBase::FNotToRun()
{
	GetCharacterMovement()->MaxWalkSpeed=300.f;
}

void APlayerBase::GunCrouch()
{
	if(IsGunVisible)
	{
		if(IsCrouching)
			VCrouch = 200.f;
		else
			VCrouch = 0.f;
	}
	else{
		if(IsCrouching)
			VCrouch = 200.f;
		else
			VCrouch = 100.f;
	}
}

void APlayerBase::FToJump()
{
	if(VCrouch)
	{
		VCrouch=false;
		GetCharacterMovement()->MaxWalkSpeed=BaseMovementSpeed;
	}
	ACharacter::Jump();
	
	GunCrouch();
}

/*
void APlayerBase::FNotToJump()
{
	StopJumping();
}*/

void APlayerBase::FToCrouch()
{
	IsCrouching = true;
	VCrouch = 200.f;
}

void APlayerBase::FNotToCrouch()
{
	IsCrouching  = false;
	if(IsGunVisible)
		VCrouch = 0.f;
	else
		VCrouch = 100.f;
}

void APlayerBase::FToArm()
{ 
	IsGunVisible = !IsGunVisible;
	GunCrouch();
}