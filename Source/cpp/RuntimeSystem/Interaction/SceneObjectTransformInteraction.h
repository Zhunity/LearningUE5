// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SceneObjectTransformInteraction.generated.h"


class UTransformProxy;
class UCombinedTransformGizmo;
class URuntimeMeshSceneObject;
/**
 * 
 */
UCLASS()
class CPP_API USceneObjectTransformInteraction : public UObject
{
	GENERATED_BODY()

public:

	/**
	 * Set up the transform interaction.
	 * @param GizmoEnabledCallbackIn callback that determines if Gizmo should be created and visible. For example during a Tool we generally want to hide the TRS Gizmo.
	 */
	void Initialize(TUniqueFunction<bool()> GizmoEnabledCallbackIn);

protected:

	FDelegateHandle SelectionChangedEventHandle;

	TUniqueFunction<bool()> GizmoEnabledCallback = [&]() { return true; };

	UPROPERTY()
	UTransformProxy* TransformProxy;

	UPROPERTY()
	UCombinedTransformGizmo* TransformGizmo;

	bool bEnableScaling = true;
	bool bEnableNonUniformScaling = true;

	void UpdateGizmoTargets(const TArray<UObject*>& Selection);
};
