// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildSystem.h"
#include "../Main/MyCharacter.h"
#include "Floor.h"
#include "Animation/BlendSpaceBase.h"
#include "cpp/Main/Lib.h"

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

	BlurAttach();
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
	BuildItem = GetWorld() -> SpawnActor<AFloor>(FVector(-200, 0, 110), FRotator::ZeroRotator);
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
	if(BuildItem == nullptr)
	{
		return false;
	}
	bool isBlock = Cast<AFloor>(BuildItem) -> IsBlock;
	if(isBlock)
	{
		Lib::echo(TEXT("block"));
		return false;
	}
	Cast<AFloor>(BuildItem) ->StaticMeshComponent ->SetMobility(EComponentMobility::Stationary);
	Cast<AFloor>(BuildItem) -> SetCollision(ECollisionEnabled::QueryAndPhysics);
	Cast<AFloor>(BuildItem) -> SetMaterail(TEXT("/Script/Engine.MaterialFunction'/Game/Characters/Mannequin_UE4/Materials/Layers/ML_ShinyPlastic_Beige.ML_ShinyPlastic_Beige'"));

	FBuildCache cache;
	cache.HealthPoints = 100;
	cache.Type = TEXT("Floor");
	cache.Building = BuildItem;
	cache.Location = BuildLocation;
	cache.Rotation = Cast<AFloor>(BuildItem) -> GetActorRotation();
	Saving.Emplace(cache);

	BuildItem = nullptr;
	return true;
}

void UBuildSystem::BlurAttach()
{
	if(BuildItem == nullptr)
	{
		return;
	}
	FRotator viewRotation = Player ->GetController() -> GetControlRotation();
	FVector mainLocation = Player -> GetActorLocation();
	float angle = 90 - (360 - viewRotation.Pitch );
	if(angle <= 0)
	{
		angle = 89;
	}
	BuildDistance = FMath::Tan(FMath::DegreesToRadians(angle)) * mainLocation.Z;
	if(BuildDistance > 1000)
	{
		BuildDistance = 1000;
	}
	float x = FMath::Cos(FMath::DegreesToRadians(viewRotation.Yaw)) * BuildDistance;
	float y = FMath::Sin(FMath::DegreesToRadians(viewRotation.Yaw)) * BuildDistance;
	BuildLocation = FVector(mainLocation.X, mainLocation.Y, mainLocation.Z) + FVector(x, y, -100);
	Cast<AFloor>(BuildItem) -> SetActorLocation(BuildLocation);
	Cast<AFloor>(BuildItem) -> SetActorRotation(FRotator(0, viewRotation.Yaw, 0));
}






