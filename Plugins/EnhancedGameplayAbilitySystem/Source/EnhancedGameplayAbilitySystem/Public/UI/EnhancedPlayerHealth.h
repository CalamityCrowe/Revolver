// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayEffectTypes.h"
#include "EnhancedPlayerHealth.generated.h"

class UProgressBar;
class UTextBlock;
class UHorizontalBox; 
/**
 * 
 */
UCLASS(Abstract,HideDropdown)
class ENHANCEDGAMEPLAYABILITYSYSTEM_API UEnhancedPlayerHealth : public UUserWidget
{
	GENERATED_UCLASS_BODY()
	
protected: 
	
	virtual void UpdateHealth(const FOnAttributeChangeData& Data); 
	
	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetOptional))
	TObjectPtr<UProgressBar> HealthBar; 
	
	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetOptional))
	TObjectPtr<UHorizontalBox> TextFormatBox; 
	
	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> CurrentHealthText; 
	
	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> MaxHealthText;
	
	
	
	float Health; 
	float MaxHealth;
};
