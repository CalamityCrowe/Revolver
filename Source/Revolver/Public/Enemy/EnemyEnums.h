// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EEnemyStates: uint8
{
	Passive  UMETA(DisplayName = "Passive"),
	Attacking UMETA(DisplayName = "Attacking"), 
	Dead UMETA(DisplayName = "Dead"),
	None UMETA(DisplayName = "None")
};

UENUM(BlueprintType)
enum class EMovementSpeed : uint8
{
	Idle UMETA(DisplayName = "Idle"), 
	Walking UMETA(DisplayName = "Walking"),
	Running UMETA(DisplayName = "Running"),
};

