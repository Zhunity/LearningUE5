// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Floor.generated.h"

UCLASS()
class CPP_API AFloor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditInstanceOnly, Category="Basic Config")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditInstanceOnly, Category="Basic Config")
	UBoxComponent* BoxComponent;

	UPROPERTY(EditInstanceOnly, Category="Basic Config")
	float HalfXY = 200;

	UPROPERTY(EditInstanceOnly, Category="Basic Config")
	float HalfZ = 30;

	UPROPERTY(EditInstanceOnly, Category="Basic Config")
	float XYZScale = 50;

	UPROPERTY(EditInstanceOnly, Category="Basic Config")
	bool IsBlock = false;

	UPROPERTY(EditInstanceOnly, Category="Basic Config")
	FString BlockActorName;

	void SetCollision(ECollisionEnabled::Type type = ECollisionEnabled::NoCollision);

	void SetMaterail(FString value);

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBody, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBody);
};
