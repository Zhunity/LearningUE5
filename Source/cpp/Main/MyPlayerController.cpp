// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

#include "Lib.h"
#include "GameFramework/CharacterMovementComponent.h"

AMyPlayerController::AMyPlayerController()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	this->Construct();
}

void AMyPlayerController::Construct()
{
	InputComponent = CreateDefaultSubobject<UInputComponent>(TEXT("here?"));
	
}


void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	Main = Cast<AMyCharacter>(GetCharacter());
}

// Called every frame
void AMyPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveAnimSwitch();
}

// Called to bind functionality to input
void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent -> BindAxis("MoveForward", this, &AMyPlayerController::MoveForward);
	InputComponent -> BindAxis("MoveRight", this, &AMyPlayerController::MoveRight);

	InputComponent -> BindAction("Jump", IE_Pressed, this, &AMyPlayerController::Jump);
	InputComponent -> BindAction("MouseWheelDown", IE_Pressed, this, &AMyPlayerController::MouseWheelDown);
	InputComponent -> BindAction("MouseWheelUp", IE_Pressed, this, &AMyPlayerController::MouseWheelUp);
}

void AMyPlayerController::MoveForward(float value)
{
	ForwardValue = value;
	Main -> IsMoving = ForwardValue || RightValue;
	if(ForwardValue)
	{
		const FRotator rotation = GetControlRotation();
		const FRotator yawRotation(0, rotation.Yaw, 0);
		const FVector direction = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
		Main -> AddMovementInput(direction, value);
	}

	if(Main -> IsMoving)
	{
		Main->Speed = 500;
	}
	else
	{
		Main->Speed = 0;
	}
}
void AMyPlayerController::MoveRight(float value)
{
	RightValue = value;
	Main -> IsMoving = ForwardValue || RightValue;
	if(RightValue)
	{
		const FRotator rotation = GetControlRotation();
		const FRotator yawRotation(0, rotation.Yaw, 0);
		const FVector direction = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);
		Main -> AddMovementInput(direction, value);
	}
	if(Main -> IsMoving)
	{
		Main->Speed = 500;
	}
	else
	{
		Main->Speed = 0;
	}
}
void AMyPlayerController::Jump()
{
	bool isFalling = Main->GetCharacterMovement()->IsFalling();
	Lib::echo(Main->GetCharacterMovement()->MovementMode);
	if(!isFalling)
	{
		Main->AnimPlay(Main->JumpA);
	}
	Main -> Jump();
}

void AMyPlayerController::MouseWheelDown()
{
	float armLength = Main ->SpringArmComponent ->TargetArmLength + 50;
	armLength = MAX(MIN(armLength, 600), 0);
	Main ->SpringArmComponent ->TargetArmLength = armLength;
	if(armLength <= 0)
	{
		if(IsThirldView)
		{
			IsThirldView = false;
			Main ->FirstPerson();
		}
		
	}
	else
	{
		if(!IsThirldView)
		{
			IsThirldView = true;
			Main ->ThirdPerson();
		}
	}
}

void AMyPlayerController::MouseWheelUp()
{
	float armLength = Main ->SpringArmComponent ->TargetArmLength -50;
	armLength = MAX(MIN(armLength, 600), 0);
	Main ->SpringArmComponent ->TargetArmLength = armLength;
	if(armLength <= 0)
	{
		if(IsThirldView)
		{
			IsThirldView = false;
			Main ->FirstPerson();
		}
		
	}
	else
	{
		if(!IsThirldView)
		{
			IsThirldView = true;
			Main ->ThirdPerson();
		}
	}
}

void AMyPlayerController::MoveAnimSwitch()
{
	bool isFalling = Main->GetCharacterMovement()->IsFalling();
	bool isPlaying = Main->GetMesh()->IsPlaying();
	bool isJumpStart = Main->GetPlayingAnimName()==Main->JumpA;
	if(isFalling && IsJumpCouldPlay)
	{
		IsJumpCouldPlay = false;
		IsJogCouldPlay = true;
		IsIdleCouldPlay = true;
		if(isJumpStart && !isPlaying)
		{
			Main->AnimPlay(Main->JumpLoop);
		}
	}
	else if(ForwardValue !=0 || RightValue !=0 )
	{
		if(IsJogCouldPlay && !isFalling)
		{
			IsJumpCouldPlay = true;
			IsJogCouldPlay = false;
			IsIdleCouldPlay = true;
			Main->AnimPlay(Main->Jog, true);
		}
	}
	else
	{
		if(IsIdleCouldPlay && !isFalling)
		{
			IsJumpCouldPlay = true;
			IsJogCouldPlay = true;
			IsIdleCouldPlay = false;
			Main->AnimPlay(Main->Idle, true);
		}
	}
}

