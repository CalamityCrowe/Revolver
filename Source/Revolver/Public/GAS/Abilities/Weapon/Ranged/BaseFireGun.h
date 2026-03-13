// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/Abilities/Weapon/BaseWeaponAbility.h"
#include "BaseFireGun.generated.h"

/**
 * 
 */

class AWeaponBase;
class AGameplayAbilityTargetActor;

UCLASS(Abstract, HideDropdown)
class REVOLVER_API UBaseFireGun : public UBaseWeaponAbility
{
	GENERATED_BODY()
protected: 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities|Effects")
	FGameplayTag FireWeaponTag; 

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities|Projectile")
	TSubclassOf<AGameplayAbilityTargetActor> TargetingClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities|Projectile")
	TSubclassOf<AActor> ProjectileClass;
	
	UPROPERTY(EditDefaultsOnly, BLueprintReadOnly, Category = "Abilities|Projectile")
	float ProjectileSpeed;
	
	virtual void MontageStart() override;
	
	UFUNCTION()
	virtual void ValidDataEvent(const FGameplayAbilityTargetDataHandle& PayLoad); 
	
	UFUNCTION()
	virtual void FireWeaponEvent(FGameplayEventData Payload); 
	
};
