// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Main/MyCharacter.h"
#include "FramePro/FramePro.h"
#include "BuildSystem.generated.h"

USTRUCT(BlueprintType)
struct FBuildCache
{
	GENERATED_BODY()

	UPROPERTY(EditInstanceOnly, Category="Basic Config")
	float HealthPoints;

	UPROPERTY(EditInstanceOnly, Category="Basic Config")
	FString Type;

	UPROPERTY(EditInstanceOnly, Category="Basic Config")
	FString Token;

	UPROPERTY(EditInstanceOnly, Category="Basic Config")
	UObject* Building;

	UPROPERTY(EditInstanceOnly, Category="Basic Config")
	FVector Location;

	UPROPERTY(EditInstanceOnly, Category="Basic Config")
	FRotator Rotation;

	UPROPERTY(EditInstanceOnly, Category="Basic Config")
	bool Right = false;

	UPROPERTY(EditInstanceOnly, Category="Basic Config")
	bool Left = false;

	UPROPERTY(EditInstanceOnly, Category="Basic Config")
	bool Low = false;

	UPROPERTY(EditInstanceOnly, Category="Basic Config")
	bool Up = false;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPP_API UBuildSystem : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBuildSystem();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditInstanceOnly, Category="Basic Config")
	AMyCharacter* Player;

	UPROPERTY(EditInstanceOnly, Category="Basic Config")
	float BuildDistance = 500;

	UPROPERTY(EditInstanceOnly, Category="Basic Config")
	FVector BuildLocation;

	UPROPERTY(EditInstanceOnly, Category="Basic Config")
	UObject* BuildItem = nullptr;

	UPROPERTY(EditInstanceOnly, Category="Basic Config")
	TArray<FBuildCache> Saving;
	
	void SetPlayer(AMyCharacter* value);
	void SetBuild();
	void UnsetBuild();
	bool Building();
	void BlurAttach();
};
