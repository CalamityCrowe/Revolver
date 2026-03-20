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
	Toggle UMETA(DisplayName = "Toggle Ability"), 
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
	

	
	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	
	virtual void OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	
protected: 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities|Tag")
	FGameplayTag CoolDownTag; 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities|Tag")
	EEnhancedActivationPolicy ActivationPolicy;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Abilities")
	bool bActivateOnGranted; 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	bool bShouldShowInHUD;
	
	
	
};
