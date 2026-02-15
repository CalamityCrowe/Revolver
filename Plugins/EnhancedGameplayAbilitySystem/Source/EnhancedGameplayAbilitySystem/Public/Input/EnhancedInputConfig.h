// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "EnhancedInputConfig.generated.h"

/**
 * 
 */

class UInputAction;

USTRUCT(Blueprintable)
struct FEnhancedInputAction
{
	GENERATED_BODY()
public: 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> InputAction; 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	FGameplayTag InputTag;
};

UCLASS()
class ENHANCEDGAMEPLAYABILITYSYSTEM_API UEnhancedInputConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditDefaultsOnly, BLueprintReadOnly, Category = "Input")
	TArray<FEnhancedInputAction> NativeInputActions;
	
	UPROPERTY(EditDefaultsOnly, BLueprintReadOnly, Category = "Input")
	TArray<FEnhancedInputAction> AbilityInputActions; 
	
	const UInputAction* FindNativeInputActionByTag(const FGameplayTag& InputTag) const; 
	const UInputAction* FindAbilityInputActionByTag(const FGameplayTag& InputTag) const;
	
};
