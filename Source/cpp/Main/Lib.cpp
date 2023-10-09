// Fill out your copyright notice in the Description page of Project Settings.


#include "Lib.h"

void Lib::echo(float value, bool isLog)
{
	FString message = FString::Printf(TEXT("%f"), value);
	echo(message, isLog);
}

void Lib::echo(FString value, bool isLog)
{
	if(isLog)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *value);
	}
	else
	{
		GEngine -> AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, value);
	}
}
