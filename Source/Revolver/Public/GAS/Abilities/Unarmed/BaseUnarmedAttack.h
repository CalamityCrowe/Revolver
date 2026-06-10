// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/Ability/EnhancedGameplayAbility.h"
#include "BaseUnarmedAttack.generated.h"

/**
 * 
 */
UCLASS()
class REVOLVER_API UBaseUnarmedAttack : public UEnhancedGameplayAbility
{
	GENERATED_BODY()
public: 
	UBaseUnarmedAttack(); 
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
protected: 
	
	/** This is the montage that we will be playing to handle this. This will have the  notify events assigned in frames to signal the game to start/stop hit attacks*/ 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities|Animations")
	TObjectPtr<UAnimMontage> MontageToPlay;
	
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities|Effects")
	TSubclassOf<UGameplayEffect> EffectClass; 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities|Effects")
	FGameplayTag EffectMagnitudeTag; 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities|Effects")
	float EffectMagnitude; 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities|Events")
	FGameplayTag HitScanStartTag;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities|Events")
	FGameplayTag HitScanEndTag;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities|Properties|Hit Scan")
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities|Properties|Hit Scan")
	float ScanInterval;
	
	
	UPROPERTY()
	FTimerHandle HitScanTimer;
	
	FName SocketName;
	float CollisionRadius; 
	
	UPROPERTY()
	TArray<AActor*> HitActors; 
	
	UFUNCTION()
	virtual void OnMontageCompleted(); 
	
	UFUNCTION()
	virtual void OnMontageCanceled();
	
	UFUNCTION()
	virtual void OnMontageBlendOut();
	
	UFUNCTION()
	virtual void HitScanStarted(FGameplayEventData PayLoad);
	
	UFUNCTION()
	virtual void HitScanEnded(FGameplayEventData PayLoad);
	
	UFUNCTION()
	virtual void HitScan();
};
