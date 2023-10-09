// Fill out your copyright notice in the Description page of Project Settings.


#include "Floor.h"

// Sets default values
AFloor::AFloor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFloor::BeginPlay()
{
	Super::BeginPlay();

	//BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AFloor::OnOverlapBegin);
}

// Called every frame
void AFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AFloor::SetCollision(ECollisionEnabled::Type type)
{
	StaticMeshComponent->SetCollisionEnabled(type);
	if(type == ECollisionEnabled::QueryOnly)
	{
		StaticMeshComponent->SetCollisionResponseToChannels(ECR_Ignore);
	}
	else
	{
		StaticMeshComponent->SetCollisionResponseToChannels(ECR_Block);
	}
}

void AFloor::SetMaterail(FString value)
{
	UMaterialInterface* material = LoadObject<UMaterialInterface>(NULL, *value);
	StaticMeshComponent->SetMaterial(0, material);
}


void AFloor::OnOverlapBegin(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBody)
{
	BlockActorName = otherActor->GetName();
	IsBlock = true;
}

void AFloor::OnOverlapEnd(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBody)
{
	BlockActorName = nullptr;
	IsBlock = false;
}





