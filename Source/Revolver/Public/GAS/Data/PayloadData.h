// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PayloadData.generated.h"

USTRUCT(BlueprintType)
struct FSocketCollisionParams
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName SocketName = NAME_None;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CollisionRadius = 0.0f; 
};

UCLASS(BlueprintType)
class USocketCollisionParamsObject: public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSocketCollisionParams Params;
};
