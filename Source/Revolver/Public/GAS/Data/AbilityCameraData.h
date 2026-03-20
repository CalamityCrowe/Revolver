// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "AbilityCameraData.generated.h"

/**
 * 
 */
UCLASS()
class REVOLVER_API UAbilityCameraData : public UPrimaryDataAsset
{
	GENERATED_BODY()
public: 
	
	UAbilityCameraData(); 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera|Ability Tags", meta = (AllowPrivateAccess))
	FGameplayTag CameraTag; 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera|Properties")
	FVector AbilitySocketOffset; 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera|Properties")
	float AbilityTargetArm;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera|Properties")
	float AbilityFOV;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera|Properties", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float CameraTransition; 
};

USTRUCT(BlueprintType)
struct REVOLVER_API FAbilityCameraSetups
{
	GENERATED_BODY()
public: 
	bool IsDataSet() const
	{
		return (DefaultCameraSetup && FirstAbilityData && SecondAbilityData && ThirdAbilityData && FourthAbilityData); 
	}
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera Data")
	TObjectPtr<UAbilityCameraData> DefaultCameraSetup; 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera Data")
	TObjectPtr<UAbilityCameraData> FirstAbilityData;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera Data")
	TObjectPtr<UAbilityCameraData> SecondAbilityData;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera Data")
	TObjectPtr<UAbilityCameraData> ThirdAbilityData;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera Data")
	TObjectPtr<UAbilityCameraData> FourthAbilityData;

};
