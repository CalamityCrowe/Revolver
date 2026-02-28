// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/Ability/EnhancedGameplayAbility.h"
#include "GameplayEffect.h"
#include "BaseMeleeAbility.generated.h"

class AWeaponBase;
/**
 * 
 */
UCLASS(Abstract, HideDropdown)
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
	
	UPROPERTY()
	AWeaponBase* EquippedWeapon; 
	
	UFUNCTION(BlueprintCallable)
	virtual void HandleHitScanStart(FGameplayEventData Payload); 
	
	UFUNCTION(BlueprintCallable)
	virtual void HandleHitScanEnd(FGameplayEventData Payload);
	
	virtual void MontageStart(){};
	
	
private: 
	
	UFUNCTION()
	void OnMontageCompleted();
	UFUNCTION()
	void OnMontageCancelled(); 
	UFUNCTION()
	void OnMontageInterupted(); 
};
