// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyCharacter.h"
#include "Animation/AnimInstance.h"
#include "CloneAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class CPP_API UCloneAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	inline static FString CloneAnim = "Class'/Game/Characters/Mannequins/Animations/Manny/MannyBp.MannyBp_C'";
	
	UCloneAnimInstance();
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AMyCharacter* Main;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Direction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsFalling;
};
