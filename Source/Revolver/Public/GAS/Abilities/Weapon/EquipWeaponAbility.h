// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/Ability/EnhancedGameplayAbility.h"
#include "EquipWeaponAbility.generated.h"

class AWeaponBase;
/**
 * 
 */
UCLASS(Abstract, HideDropdown)
class REVOLVER_API UEquipWeaponAbility : public UEnhancedGameplayAbility
{
	GENERATED_BODY()
public: 
	UEquipWeaponAbility(); 
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	
protected: 
	UPROPERTY(EditDefaultsOnly,Category = "Weapon Class")
	TSubclassOf<AWeaponBase> MeleeWeaponClass; 
	
	UFUNCTION()
	void OnMontageCompleted(UAnimMontage* Montage, bool bWasCancelled);
	
};
