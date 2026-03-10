// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/Ability/EnhancedGameplayAbility.h"
#include "BaseFireGun.generated.h"

/**
 * 
 */

class AGameplayAbilityTargetActor;

UCLASS(Abstract, HideDropdown)
class REVOLVER_API UBaseFireGun : public UEnhancedGameplayAbility
{
	GENERATED_BODY()
public: 
	UBaseFireGun(); 
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
protected: 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities|Montage")
	TObjectPtr<UAnimMontage> FireMontage; 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities|Effects")
	TSubclassOf<UGameplayEffect> DamageEffect;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities|Effects")
	FGameplayTag DamageTag;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities|Effects")
	float Damage;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities|Effects")
	FGameplayTag FireWeaponTag; 

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities|Projectile")
	TSubclassOf<AGameplayAbilityTargetActor> TargetingClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities|Projectile")
	TSubclassOf<AActor> ProjectileClass;
	
	UFUNCTION()
	virtual void ValidDataEvent(const FGameplayAbilityTargetDataHandle& PayLoad); 
	
	UFUNCTION()
	virtual void FireWeaponEvent(FGameplayEventData Payload); 
	
private:
	
	UFUNCTION()
	void OnMontageCompleted(); 
	UFUNCTION()
	void OnMontageCancelled();
};
