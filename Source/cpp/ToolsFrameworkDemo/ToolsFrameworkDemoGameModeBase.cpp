// Fill out your copyright notice in the Description page of Project Settings.


#include "ToolsFrameworkDemoGameModeBase.h"

AToolsFrameworkDemoGameModeBase::AToolsFrameworkDemoGameModeBase()
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
}


void AToolsFrameworkDemoGameModeBase::StartPlay()
{
	//Super::StartPlay();
	InitializeToolsSystem();
}

void AToolsFrameworkDemoGameModeBase::InitializeToolsSystem()
{
	UWorld* World = GetWorld();
	UGameInstance* GameInstance = GetGameInstance();
	check(World && GameInstance);

	// create Scene subsystem
	//SceneSystem = UGameInstance::GetSubsystem<URuntimeMeshSceneSubsystem>(GameInstance);
	//URuntimeMeshSceneSubsystem::InitializeSingleton(SceneSystem);

	// create Tools subsystem
	ToolsSystem = UGameInstance::GetSubsystem<URuntimeToolsFrameworkSubsystem>(GameInstance);
	URuntimeToolsFrameworkSubsystem::InitializeSingleton(ToolsSystem);

	check(/*SceneSystem && */ToolsSystem);

	// initialize Tools and Scene systems
	ToolsSystem->InitializeToolsContext(World);
	//SceneSystem->SetCurrentTransactionsAPI(ToolsSystem->GetTransactionsAPI());

	RegisterTools();
}