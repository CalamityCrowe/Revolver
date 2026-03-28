// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/Abilities/Character/BaseChordedAbility.h"
#include "ChargeAbility.generated.h"

/**
 * 
 */
UCLASS()
class REVOLVER_API UChargeAbility : public UBaseChordedAbility
{
	GENERATED_BODY()
	
public: 
	UChargeAbility(); 
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
protected: 
	virtual void MontageStarted() override;
	
	virtual void OnMontageCancelled() override;
	
	virtual void OnMontageCompleted() override;
	
	virtual void OnMontageInterupted() override;
	
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities|Event")
	FGameplayTag HitScanStartTag;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities|Event")
	FGameplayTag HitScanEndTag;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities|Properties|Hit Scan", meta = (UIMin = 0.0f, UIMax = 1.0f, ClampMin = 0.0f, ClampMax = 1.0f))
	float HitRate;
	
	UPROPERTY(EditDefaultsonly, BlueprintReadOnly, Category = "Abilities|Properties|Hit Scan", meta	= (UIMin = 0.0f, ClampMin = 0.0f))
	float HitRadius; 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities|Properties|Hit Scan")
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities|Properties|Charge", meta = (UIMin = 0.0f, ClampMin = 0.0f))
	float DirectionMagnitude; 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities|Properties|Charge", meta = (UIMin = 0.0f, ClampMin = 0.0f))
	float ChargeStrength;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities|Properties|Charge", meta = (UIMin = 0.0f, ClampMin = 0.0f))
	float ChargeDuration;
	
	
	
	
private: 
	
	UPROPERTY()
	TArray<AActor*> HitActors; 
	
	UFUNCTION()
	virtual void MontageTriggerEvent(FGameplayEventData Payload); 
	
	UFUNCTION()
	virtual void HitScanStartEvent(FGameplayEventData Payload); 
	
	UFUNCTION()
	virtual void HitScanEndEvent(FGameplayEventData Payload);
	
	UFUNCTION()
	virtual void HitScan();
	
	UFUNCTION()
	virtual void ChargeForce(); 
	
	UFUNCTION()
	virtual void OnChargeFinish(); 
	
	
	FTimerHandle HitScanTimer; 
	
	FVector ChargeDirection; 
	
};
