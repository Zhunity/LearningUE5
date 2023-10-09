// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildSystem.h"
#include "../Main/MyCharacter.h"
#include "Floor.h"
#include "Animation/BlendSpaceBase.h"

// Sets default values for this component's properties
UBuildSystem::UBuildSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBuildSystem::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBuildSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBuildSystem::SetPlayer(AMyCharacter* value)
{
	this -> Player = value;
}

void UBuildSystem::SetBuild()
{
	if(BuildItem != nullptr)
	{
		return;
	}
	BuildItem = GetWorld() -> SpawnActor<AFloor>(FVector(0, 0, -100000), FRotator::ZeroRotator);
	Cast<AFloor>(BuildItem) -> SetCollision(ECollisionEnabled::QueryOnly);
}

void UBuildSystem::UnsetBuild()
{
	if(BuildItem == nullptr)
	{
		return;
	}
	GetWorld()->DestroyActor(Cast<AFloor>(BuildItem));
	BuildItem = nullptr;
}

bool UBuildSystem::Building()
{
	return true;
}





