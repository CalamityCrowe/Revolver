// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_BlendCamera.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBlendFinished); 

/**
 * 
 */
UCLASS(Blueprintable)
class REVOLVER_API UAbilityTask_BlendCamera : public UAbilityTask
{
	GENERATED_BODY()
	
public: 
	
	UPROPERTY(BlueprintAssignable)
	FOnBlendFinished OnBlendFinished;
	
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility"))
	static UAbilityTask_BlendCamera* BlendCamera(UGameplayAbility* OwningAbility, 
		FVector TargetOffset, 
		float TargetArmLength, 
		float BlendTime,
		UCurveFloat* BlendCurve = nullptr); 
	
	virtual void Activate() override;
	virtual void OnDestroy(bool bInOwnerFinished) override;
	virtual void TickTask(float DeltaTime) override;
	
private: 
	
	FVector StartSocketOffset; 
	FVector TargetSocketOffset;
	FVector OriginalSocketOffset;
	float StartArmLength; 
	float TargetArmLength;
	float OriginalArmLength; 
	
	float BlendTime;
	float ElapsedTime; 
	
	
	
	UPROPERTY()
	UCurveFloat* BlendCurve; 
	
};
