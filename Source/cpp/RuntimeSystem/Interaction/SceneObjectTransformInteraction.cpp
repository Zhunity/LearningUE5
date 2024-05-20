// Fill out your copyright notice in the Description page of Project Settings.


#include "SceneObjectTransformInteraction.h"
#include <InteractiveGizmoManager.h>
#include <cpp/RuntimeSystem/RuntimeToolsFrameworkSubsystem.h>
#include <BaseGizmos/TransformGizmoUtil.h>

void USceneObjectTransformInteraction::Initialize(TUniqueFunction<bool()> GizmoEnabledCallbackIn)
{
	GizmoEnabledCallback = MoveTemp(GizmoEnabledCallbackIn);

	/*SelectionChangedEventHandle = URuntimeMeshSceneSubsystem::Get()->OnSelectionModified.AddLambda([this](URuntimeMeshSceneSubsystem* SceneSubsystem)
		{
			UpdateGizmoTargets(SceneSubsystem->GetSelection());
		});*/

}

void USceneObjectTransformInteraction::UpdateGizmoTargets(const TArray<UObject*>& Selection)
{
	UInteractiveGizmoManager* GizmoManager = URuntimeToolsFrameworkSubsystem::Get()->ToolsContext->GizmoManager;

	// destroy existing gizmos if we have any
	if (TransformGizmo != nullptr)
	{
		GizmoManager->DestroyAllGizmosByOwner(this);
		TransformGizmo = nullptr;
		TransformProxy = nullptr;
	}

	// if no selection, no gizmo
	if (Selection.Num() == 0 || GizmoEnabledCallback() == false)
	{
		return;
	}

	TransformProxy = NewObject<UTransformProxy>(this);
	for (UObject* SO : Selection)
	{
		// would be nice if this worked on Actors...
		//TransformProxy->AddComponent(SO->GetMeshComponent());
	}

	ETransformGizmoSubElements GizmoElements = ETransformGizmoSubElements::FullTranslateRotateScale;
	if (bEnableScaling == false)
	{
		GizmoElements = ETransformGizmoSubElements::StandardTranslateRotate;
	}
	else if (bEnableNonUniformScaling == false || Selection.Num() > 1)		// cannot nonuniform-scale multiple objects
	{
		GizmoElements = ETransformGizmoSubElements::TranslateRotateUniformScale;
	}

	TransformGizmo = UE::TransformGizmoUtil::CreateCustomTransformGizmo(GizmoManager, GizmoElements, this);
	TransformGizmo->SetActiveTarget(TransformProxy);

	// optionally ignore coordinate system setting
	//TransformGizmo->bUseContextCoordinateSystem = false;
	//TransformGizmo->CurrentCoordinateSystem = EToolContextCoordinateSystem::Local;
}