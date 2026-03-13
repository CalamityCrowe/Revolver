// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/Ability/EnhancedGameplayAbility.h"
#include "GameplayEffect.h"
#include "BaseWeaponAbility.generated.h"

class AWeaponBase;
/**
 * 
 */
UCLASS(Abstract, HideDropdown)
class REVOLVER_API UBaseWeaponAbility : public UEnhancedGameplayAbility
{
	GENERATED_BODY()
	
public: 
	
	UBaseWeaponAbility(); 
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities|Animations")
	TObjectPtr<UAnimMontage> AttackMontage; 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities|Effects")
	TSubclassOf<UGameplayEffect> EffectClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities|Effects")
	float EffectMagnitude; 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities|Effects")
	FGameplayTag EffectCallerTag;
	

	UPROPERTY()
	AWeaponBase* EquippedWeapon; 
	

	virtual void MontageStart(){};
	virtual FVector GetSpawnLocation(); 
	
private: 
	
	UFUNCTION()
	void OnMontageCompleted();
	UFUNCTION()
	void OnMontageCancelled(); 
	UFUNCTION()
	void OnMontageInterupted(); 
};
