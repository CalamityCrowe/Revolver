// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "EnhancedGameplayAbility.generated.h"

/**
 * 
 */

class ACharacter;

UENUM(BlueprintType)
enum class EEnhancedActivationPolicy:uint8
{
	OnInputTriggered UMETA(DisplayName = "On Input Triggered"),
	WhileInputActive UMETA(DisplayName = "While Input Active"),
	None UMETA(Hidden)
};

UCLASS(Abstract , Blueprintable, meta= (HideFromSelection = true))
class ENHANCEDGAMEPLAYABILITYSYSTEM_API UEnhancedGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
public: 
	
	UEnhancedGameplayAbility(); 
	EEnhancedActivationPolicy GetActivationPolicy() const{return ActivationPolicy; };
	
	UFUNCTION(BlueprintCallable,Category = "GAS|Ability")
	ACharacter* GetCharacterFromActorInfo() const; 
	
protected: 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities|Tag")
	FGameplayTag GameplayCueTag; 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities|Tag")
	EEnhancedActivationPolicy ActivationPolicy;
};
