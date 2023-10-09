// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyCharacter.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CPP_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()


public:
	// Sets default values for this character's properties
	AMyPlayerController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupInputComponent() override;

	UPROPERTY(EditInstanceOnly, Category= "Basic Config")
	AMyCharacter* Main;


	UPROPERTY(EditInstanceOnly, Category= "Basic Config")
	bool IsJumpCouldPlay = true;
	UPROPERTY(EditInstanceOnly, Category= "Basic Config")
	bool IsJogCouldPlay = true;
	UPROPERTY(EditInstanceOnly, Category= "Basic Config")
	bool IsIdleCouldPlay = true;
	
	float ForwardValue;
	float RightValue;
	

	UPROPERTY(EditInstanceOnly, Category= "Basic Config")
	bool IsThirldView = true;
	
	void MoveForward(float value);
	void MoveRight(float value);
	void Jump();
	void MouseWheelUp();
	void MouseWheelDown();
	

private :
	void Construct();

	void MoveAnimSwitch();
};
