// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "WaveData.generated.h"

class AEnemyCharacter; 

USTRUCT(BlueprintType)
struct FWaveModifiers
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<TSubclassOf<AEnemyCharacter>, int32> EnemyPool; 
};

USTRUCT(BlueprintType)
struct FWaveDataRow : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FWaveModifiers WaveModifiers; 
};