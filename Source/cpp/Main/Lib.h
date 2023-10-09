// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class CPP_API Lib
{
public:
	void static echo(float value, bool isLog = true);
	void static echo(FString value, bool isLog = true);
};
