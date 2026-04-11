// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "BaseCooldownCalculation.generated.h"

/**
 * 
 */
UCLASS()
class REVOLVER_API UBaseCooldownCalculation : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
public: 
	
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
};
