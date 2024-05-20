// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "RuntimeToolsFrameworkSubsystem.generated.h"
#include "Interaction/SceneObjectTransformInteraction.h"

/**
 * 
 */
UCLASS()
class CPP_API URuntimeToolsFrameworkSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
	//
	// Small hack to workaround the fact that you generally need the UGameInstance pointer to
	// look up a GameInstance subsystem. We store the pointer and then allow ::Get() to return it (ie actually a Singleton)
	//
public:
	static void InitializeSingleton(URuntimeToolsFrameworkSubsystem* Subsystem);
	static URuntimeToolsFrameworkSubsystem* Get();
protected:
	static URuntimeToolsFrameworkSubsystem* InstanceSingleton;

//
// UGameInstanceSubsystem API implementation
//
public:
	virtual void Deinitialize() override;


	//
	// Functions to setup/shutdown/operate the RuntimeToolsFramework
	//
public:
	void InitializeToolsContext(UWorld* TargetWorld);
	void ShutdownToolsContext();
	//void SetContextActor(AToolsContextActor* ActorIn);
	virtual void Tick(float DeltaTime);


	//
	// Tool creation/management BP API
	//

	UFUNCTION(BlueprintCallable)
	bool CanActivateToolByName(FString Name);

	UFUNCTION(BlueprintCallable)
	UInteractiveTool* BeginToolByName(FString Name);

	UFUNCTION(BlueprintCallable)
	bool HaveActiveTool();

	UFUNCTION(BlueprintCallable)
	UInteractiveTool* GetActiveTool();

	UFUNCTION(BlueprintCallable)
	bool IsActiveToolAcceptCancelType();

	UFUNCTION(BlueprintCallable)
	bool CanAcceptActiveTool();

	UFUNCTION(BlueprintCallable)
	bool AcceptActiveTool();

	UFUNCTION(BlueprintCallable)
	bool CancelOrCompleteActiveTool();

public:
	UPROPERTY()
	UWorld* TargetWorld;

	UPROPERTY()
	UInteractiveToolsContext* ToolsContext;

	UPROPERTY()
	USceneObjectTransformInteraction* TransformInteraction;

};
