// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/Abilities/Character/BaseChordedAbility.h"
#include "Abilities/GameplayAbilityTargetTypes.h"
#include "BaseAOEAbility.generated.h"

class ATargetActor_GroundDecal;
class AGameplayAbilityTargetActor;
/**
 * 
 */
UCLASS()
class REVOLVER_API UBaseAOEAbility : public UBaseChordedAbility
{
	GENERATED_BODY()
	
public: 
	UBaseAOEAbility(); 
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

protected: 
	
	virtual void MontageStarted() override;
	
	virtual void OnMontageCompleted() override;
	
	UFUNCTION()
	virtual void LoopTargetingAnimation(); 
	UFUNCTION()
	virtual void TargetingMontageCompleted(); 
	UFUNCTION()
	virtual void TargetingInterrupted(); 
	
	UFUNCTION()
	virtual void CastingInterrupted();
	UFUNCTION()
	virtual void CastingCompleted();
	
	
	UFUNCTION()
	void ValidTargeting(const FGameplayAbilityTargetDataHandle& Data); 
	
	
	virtual void MontageTriggeredEvent(FGameplayEventData Payload) override; 
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category = "Abilities|Properties|Animations")
	TObjectPtr<UAnimMontage> TargetingAnimation; 
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category = "Abilities|Properties|Animations")
	TObjectPtr<UAnimMontage> CastingMontage; 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category = "Abilities|Properties|Targeting")
	TSubclassOf<ATargetActor_GroundDecal> TargetingClass;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category = "Abilities|Properties|Targeting")
	TObjectPtr<UMaterialInterface> TargetingMaterial;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category = "Abilities|Properties|Targeting", meta = (UIMin = 0.0f, ClampMin = 0.0f))
	float AOERadius; 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category = "Abilities|Properties|Targeting", meta = (UIMin = 0.0f, ClampMin = 0.0f))
	float MaxRange;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category = "Abilities|Properties|Targeting")
	TEnumAsByte<EGameplayTargetingConfirmation::Type> TargetingConfirmation; 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities|Properties|Targeting")
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities|Properties|Targeting")
	FGameplayTag AOEDamageEffectTag;
	
	
	
private: 
	
	
	
	FVector ConfirmedAOE; 
	
	bool bIsWaitingTargetDetails;
	bool bIsReloopingMontage; 
	
	virtual void ConfirmStrike(); 
	
	virtual void AOEDamage(); 
};
