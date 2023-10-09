// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "MyCharacter.generated.h"

UCLASS()
class CPP_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	float Speed;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditInstanceOnly, Category="Basic Config")
	USkeletalMesh* SkeletalMesh;


	UPROPERTY(EditInstanceOnly, Category="Basic Config")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditInstanceOnly, Category="Basic Config")
	UCameraComponent* CameraComponent;

	UPROPERTY(EditInstanceOnly, Category="Basic Config")
	UAnimSequence* AnimSequence;

	// 是否移动
	UPROPERTY(EditInstanceOnly, Category= "Basic Config")
	bool IsMoving = false;

	void ThirdPerson();
	void FirstPerson();

	FString Idle = TEXT("/Script/Engine.AnimSequence'/Game/Characters/Mannequins/Animations/Manny/MM_Idle.MM_Idle'");
	FString Jog = TEXT("/Script/Engine.AnimSequence'/Game/Characters/Mannequins/Animations/Manny/MM_Run_Fwd.MM_Run_Fwd'");
	FString JumpA = TEXT("/Script/Engine.AnimSequence'/Game/Characters/Mannequins/Animations/Manny/MM_Jump.MM_Jump'");
	FString JumpLoop = TEXT("/Script/Engine.AnimSequence'/Game/Characters/Mannequins/Animations/Manny/MM_Fall_Loop.MM_Fall_Loop'");

	void AnimPlay(FString value, bool loop = false);
	FString GetPlayingAnimName();
	

private :
	void Construct();
	void CreateModel();
};
