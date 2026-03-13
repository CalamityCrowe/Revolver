// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/Abilities/Weapon/BaseWeaponAbility.h"
#include "BaseMeleeAttack.generated.h"

/**
 * 
 */
UCLASS()
class REVOLVER_API UBaseMeleeAttack : public UBaseWeaponAbility
{
	GENERATED_BODY()
	
protected: 
	
	virtual void MontageStart() override;
	
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Event|Hit Scan")
	FGameplayTag HitStartTag; 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Event|Hit Scan")
	FGameplayTag HitEndTag; 
	
	UFUNCTION(BlueprintCallable)
	virtual void HandleHitScanStart(FGameplayEventData Payload); 
	
	UFUNCTION(BlueprintCallable)
	virtual void HandleHitScanEnd(FGameplayEventData Payload);
	
	
};
