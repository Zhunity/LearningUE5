// Fill out your copyright notice in the Description page of Project Settings.


#include "CloneAnimInstance.h"

#include "KismetAnimationLibrary.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/KismetArrayLibrary.h"

UCloneAnimInstance::UCloneAnimInstance()
{
	Speed = 0;
	Direction = 0;
}

void UCloneAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Main = Cast<AMyCharacter>(GetOwningActor());
}

void UCloneAnimInstance::NativeUpdateAnimation(float delta)
{
	Super::NativeUpdateAnimation(delta);
	if(Main == nullptr)
	{
		return;
	}
	const FVector velocity = Main ->GetVelocity();
	IsFalling = Main->GetMovementComponent()->IsFalling();
	Speed = Main -> Speed;
	Direction = UKismetAnimationLibrary::CalculateDirection(velocity, Main->GetActorRotation());
}