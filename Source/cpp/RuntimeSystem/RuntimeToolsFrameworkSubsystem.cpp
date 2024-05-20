// Fill out your copyright notice in the Description page of Project Settings.


#include "RuntimeToolsFrameworkSubsystem.h"
#include "Interaction/SceneObjectTransformInteraction.h"

URuntimeToolsFrameworkSubsystem* URuntimeToolsFrameworkSubsystem::InstanceSingleton = nullptr;

void URuntimeToolsFrameworkSubsystem::InitializeSingleton(URuntimeToolsFrameworkSubsystem* Subsystem)
{
	check(InstanceSingleton == nullptr);
	InstanceSingleton = Subsystem;
}


URuntimeToolsFrameworkSubsystem* URuntimeToolsFrameworkSubsystem::Get()
{
	check(InstanceSingleton);
	return InstanceSingleton;
}

void URuntimeToolsFrameworkSubsystem::InitializeToolsContext(UWorld* TargetWorldIn)
{
	TargetWorld = TargetWorldIn;

	//ToolsContext = NewObject<UInteractiveToolsContext>();

	//ContextQueriesAPI = MakeShared<FRuntimeToolsContextQueriesImpl>(ToolsContext, TargetWorld);
	//if (ContextActor)
	//{
	//	ContextQueriesAPI->SetContextActor(ContextActor);
	//}

	//ContextTransactionsAPI = MakeShared<FRuntimeToolsContextTransactionImpl>();

	//ToolsContext->Initialize(ContextQueriesAPI.Get(), ContextTransactionsAPI.Get());

	//// register event handlers
	//ToolsContext->ToolManager->OnToolStarted.AddUObject(this, &URuntimeToolsFrameworkSubsystem::OnToolStarted);
	//ToolsContext->ToolManager->OnToolEnded.AddUObject(this, &URuntimeToolsFrameworkSubsystem::OnToolEnded);

	//// create scene history
	//SceneHistory = NewObject<USceneHistoryManager>(this);
	//SceneHistory->OnHistoryStateChange.AddUObject(this, &URuntimeToolsFrameworkSubsystem::OnSceneHistoryStateChange);


	//// register selection interaction
	//SelectionInteraction = NewObject<USceneObjectSelectionInteraction>();
	//SelectionInteraction->Initialize([this]()
	//	{
	//		return HaveActiveTool() == false;
	//	});
	//ToolsContext->InputRouter->RegisterSource(SelectionInteraction);


	// create transform interaction
	TransformInteraction = NewObject<USceneObjectTransformInteraction>();
	TransformInteraction->Initialize([this]()
		{
			return HaveActiveTool() == false;
		});


	//// create PDI rendering bridge Component
	//FActorSpawnParameters SpawnInfo;
	//PDIRenderActor = TargetWorld->SpawnActor<AActor>(FVector::ZeroVector, FRotator(0, 0, 0), SpawnInfo);
	//PDIRenderComponent = NewObject<UToolsContextRenderComponent>(PDIRenderActor);
	//PDIRenderActor->SetRootComponent(PDIRenderComponent);
	//PDIRenderComponent->RegisterComponent();


	//// have to disable this for current tools framework handling of property defaults.
	//GShouldVerifyGCAssumptions = false;

	////// make sure we have registered FPrimitiveComponentTarget factories
	////FSimpleDynamicMeshComponentTargetFactory::RegisterFactory();

	//// register target factory for dynamic mesh components
	////ToolsContext->TargetManager->AddTargetFactory(NewObject<URuntimeDynamicMeshComponentToolTargetFactory>(ToolsContext->ToolManager));
	//ToolsContext->TargetManager->AddTargetFactory(NewObject<URuntimeDynamicMeshComponentToolTargetFactory>(this));

	//// register transform gizmo util helper
	//UE::TransformGizmoUtil::RegisterTransformGizmoContextObject(ToolsContext);

	//// register object creation API
	//URuntimeModelingObjectsCreationAPI* ModelCreationAPI = URuntimeModelingObjectsCreationAPI::Register(ToolsContext);

}

bool URuntimeToolsFrameworkSubsystem::HaveActiveTool()
{
	return true;/*(ToolsContext != nullptr)
		&& (ToolsContext->ToolManager != nullptr)
		&& ToolsContext->ToolManager->HasActiveTool(EToolSide::Mouse);*/
}