// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseMeleeAbility.h"
#include "MeleeComboAbility.generated.h"

/**
 * 
 */
UCLASS(Abstract, HideDropdown)
class REVOLVER_API UMeleeComboAbility : public UBaseMeleeAbility
{
	GENERATED_BODY()
public: 
	UMeleeComboAbility(); 
	
	virtual void MontageStart() override;
	
	virtual void HandleHitScanStart(FGameplayEventData Payload) override;
private: 
	
	UFUNCTION()
	virtual void ContinueComboStartEvent(FGameplayEventData Payload); 
	UFUNCTION()
	virtual void ContinueComboEndEvent(FGameplayEventData Payload); 
	UFUNCTION()
	virtual void InputRecievedEvent(FGameplayEventData Payload); 
	
	int ComboCount; 
	
	
	bool bIsWithinComboWindow; 
	bool bRecievedInputAtRightTime;
};
