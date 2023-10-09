// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"

#include "CloneAnimInstance.h"
#include "Lib.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->Construct();
	this->CreateModel();
	this->ThirdPerson();
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	this->AnimPlay(Idle, true);
	SpringArmComponent -> TargetArmLength = 600;

	UClass* AnimationClass = LoadObject<UClass>(nullptr, *UCloneAnimInstance::CloneAnim);
	if(AnimationClass)
	{
		GetMesh()->SetAnimInstanceClass(AnimationClass);
	}
	else
	{
		Lib::echo(TEXT("no class"), false);
	}
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); 

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent -> BindAxis("LookRight", this, &AMyCharacter::AddControllerYawInput);
	PlayerInputComponent -> BindAxis("LookForward", this, &AMyCharacter::AddControllerPitchInput);
}

void AMyCharacter::FirstPerson()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = true;


	CameraComponent ->SetupAttachment(GetMesh());
	CameraComponent -> SetRelativeLocation(FVector(-2.5, -10, 140));
	CameraComponent->SetRelativeRotation(FRotator(0, 90, 0));
	CameraComponent -> bUsePawnControlRotation = true;
}

void AMyCharacter::ThirdPerson()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	GetCharacterMovement() -> RotationRate = FRotator(0, 540, 0);
	SpringArmComponent -> SetupAttachment(RootComponent);
	SpringArmComponent -> SetRelativeLocation(FVector(0,0,100));
	SpringArmComponent -> SetRelativeRotation(FRotator(-15, 0, 0));
	SpringArmComponent ->bUsePawnControlRotation = true;

	CameraComponent ->SetupAttachment(SpringArmComponent);
	CameraComponent -> SetRelativeLocation(FVector::ZeroVector);
	CameraComponent -> bUsePawnControlRotation = false;
}


void AMyCharacter::Construct()
{
	SkeletalMesh = LoadObject<USkeletalMesh>(NULL, TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Manny.SKM_Manny'"));
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Cameradsfsfs"));
	GetCharacterMovement() -> bOrientRotationToMovement = true;
	GetCharacterMovement() ->JumpZVelocity = 1200;
	GetCharacterMovement() -> AirControl = 1;
	GetCharacterMovement() -> GravityScale = 1;
	Lib::echo(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Manny.SKM_Manny'"));
}

void AMyCharacter :: CreateModel()
{
	GetMesh()-> SetRelativeRotation(FRotator(0,-90,0));
	GetMesh()-> SetRelativeLocation(FVector(0,0, -100));
	GetMesh() -> SetSkeletalMesh(SkeletalMesh);
	GetCapsuleComponent()-> InitCapsuleSize(42, 100);
}

void AMyCharacter :: AnimPlay(FString value, bool loop)
{
	// AnimSequence = LoadObject<UAnimSequence>(NULL, *value);
	// GetMesh()->SetAnimationMode(EAnimationMode::AnimationSingleNode);
	// GetMesh() -> SetAnimation(AnimSequence);
	// GetMesh()->Play(loop);
}

FString AMyCharacter::GetPlayingAnimName()
{
	return AnimSequence->GetPathName();
}


