// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InteractableWidget.h"

// engine
#include "Components/ProgressBar.h"

UInteractableWidget::UInteractableWidget(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	
}

void UInteractableWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UInteractableWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UInteractableWidget::InitializeWidget(EInteractionType InInteractType, FString InteractMessage)
{
	PB_InteractHoldBar->SetPercent(0);
	InteractionType = InInteractType;
	
	UpdateInteractionMessage(InteractMessage);
}

void UInteractableWidget::SetHoldTime(float InTime)
{
	PB_InteractHoldBar->SetPercent(InTime);
}

void UInteractableWidget::UpdateInteractionMessage(FString InteractMessage)
{
	
	
}
