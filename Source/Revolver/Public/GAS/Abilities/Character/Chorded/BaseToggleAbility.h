// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/Abilities/Character/BaseChordedAbility.h"
#include "BaseToggleAbility.generated.h"

/**
 * 
 */
UCLASS(Abstract, HideDropdown)
class REVOLVER_API UBaseToggleAbility : public UBaseChordedAbility
{
	GENERATED_BODY()
	
	public:
	UBaseToggleAbility();
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
protected: 
	
//	UPROPERTY(EditDefaultsOnly, BLueprintReadOnly, Category = "Abilities|Effects")

	virtual void OnMontageCompleted() override;
	
	virtual void OnMontageCancelled() override;
	
	virtual void OnMontageInterupted() override;
};
