// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/Ability/EnhancedGameplayAbility.h"
#include "GameplayEffect.h"
#include "BaseMeleeAbility.generated.h"

/**
 * 
 */
UCLASS()
class REVOLVER_API UBaseMeleeAbility : public UEnhancedGameplayAbility
{
	GENERATED_BODY()
	
public: 
	
	UBaseMeleeAbility(); 
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> AttackMontage; 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gameplay Effect")
	TSubclassOf<UGameplayEffect> EffectClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gameplay Effect")
	float EffectMagnitude; 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gameplay Effect")
	FGameplayTag EffectCallerTag;
	
	UFUNCTION(BlueprintCallable)
	virtual void HandleHitScanStart(); 
	
	UFUNCTION(BlueprintCallable)
	virtual void HandleHitScanEnd();
	
private: 
	
	UFUNCTION()
	void OnMontageCompleted();
	UFUNCTION()
	void OnMontageCancelled(); 
	UFUNCTION()
	void OnMontageInterupted(); 
};
