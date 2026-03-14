// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/Ability/EnhancedGameplayAbility.h"
#include "BaseChordedAbility.generated.h"

/**
 * I have labled this as base chorded ability purely for read ability on my part.
 * 
 * This will only be used as a template for other abilities that will be granted to the player that required the "chorded action" in order to use
 * them. Think Along the lines of Warframes abilities or even god of war ragnaroks abilities
 */

UCLASS()
class REVOLVER_API UBaseChordedAbility : public UEnhancedGameplayAbility
{
	GENERATED_BODY()
	
public: 
	UBaseChordedAbility();
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities|Animations")
	TObjectPtr<UAnimMontage> AbilityMontage; 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities|Effects")
	TSubclassOf<UGameplayEffect> EffectClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities|Effects")
	FGameplayTag EffectMagnitudeTag;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities|Effects")
	float EffectMagnitude; 
	
	
	UFUNCTION()
	virtual void MontageStarted(); 
	
private: 
	UFUNCTION()
	void OnMontageCompleted(); 
	
	UFUNCTION()
	void OnMontageCancelled(); 
	
	UFUNCTION()
	void OnMontageInterupted(); 
	
};
