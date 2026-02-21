// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/Ability/EnhancedGameplayAbility.h"
#include "DodgeAbility.generated.h"

/**
 * 
 */
UCLASS()
class REVOLVER_API UDodgeAbility : public UEnhancedGameplayAbility
{
	GENERATED_BODY()
public: 
	UDodgeAbility(); 
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
protected: 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> ForwardDodgeAnim; 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> BackwardDodgeAnim;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> LeftDodgeAnim;	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> RightDodgeAnim;
	
private: 
	
	void GetDirection(FVector& OutLastMovement) const; 

	UAnimMontage* SelectDodgeMontage(FVector Movement);
	
	
	UFUNCTION()
	void OnMontageCompleted();
	UFUNCTION()
	void OnMontageInterrupted();
	UFUNCTION()
	void OnMontageCancelled(); 
	
};
