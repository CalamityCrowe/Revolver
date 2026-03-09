// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/Ability/EnhancedGameplayAbility.h"
#include "BasePassiveAbility.generated.h"

class UGameplayEffect; 

/**
 * 
 */
UCLASS(Abstract, HideDropdown)
class REVOLVER_API UBasePassiveAbility : public UEnhancedGameplayAbility
{
	GENERATED_BODY()
	
public: 
	UBasePassiveAbility(); 
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	virtual void OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
protected: 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Abilities|Passive")
	TSubclassOf<UGameplayEffect> PassiveEffect;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities|Passive")
	float PassiveIntensity; 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities|Passive")
	FGameplayTag PassiveEffectTag;
	
	UPROPERTY(EditDefaultsOnly, BLueprintReadOnly, Category = "Abilities|Passive")
	bool bHasDuration;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities|Passive", meta = (EditCondition = "bHasDuration", EditConditionHides))
	float EffectDuration;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities|Passive", meta = (EditCondition = "bHasDuration", EditConditionHides))
	FGameplayTag DurationTag; 
};
