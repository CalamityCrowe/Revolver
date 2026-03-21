// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayEffectTypes.h"
#include "RevolverPlayerMana.generated.h"

class UTextBlock;
class UProgressBar;
/**
 * 
 */
UCLASS()
class REVOLVER_API URevolverPlayerMana : public UUserWidget
{
	GENERATED_UCLASS_BODY()
public: 
	
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

protected: 
	
	void UpdateMana(const FOnAttributeChangeData& Data);

	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess, BindWidgetOptional))
	TObjectPtr<UProgressBar> ManaBar; 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess, BindWidgetOptional))
	TObjectPtr<UTextBlock> ManaText; 	
	
	float Mana; 
	float MaxMana; 
};
