// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/InteractableInterface.h"
#include "InteractableWidget.generated.h"


class UOverlay;
class UTextBlock; 
class UProgressBar; 
class UBorder; 
class UBackgroundBlur;
/**
 * 
 */
UCLASS(abstract, HideDropdown)
class INTERACTIONSYSTEM_API UInteractableWidget : public UUserWidget
{
	GENERATED_UCLASS_BODY()
public: 
	
	virtual void NativeConstruct()override;
	virtual void NativeDestruct()override;
	
	void InitializeWidget(EInteractionType InInteractType, FString InteractMessage); 
	
	void SetHoldTime(float InPercent);
	
protected: 
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UOverlay> OV_InteractOverlay; 
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TB_InteractableText;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> PB_InteractHoldBar;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBackgroundBlur> BB_BackBlur;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBorder> B_InteractColor;


private: 
	
	void UpdateInteractionMessage(FString InteractMessage); 
	
	EInteractionType InteractionType;
};
