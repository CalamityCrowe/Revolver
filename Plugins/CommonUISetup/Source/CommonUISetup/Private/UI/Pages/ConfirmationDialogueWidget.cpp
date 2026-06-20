// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PAges/ConfirmationDialogueWidget.h"

#include "CommonTextBlock.h"
#include "Animation/WidgetAnimation.h"
#include "UI/Components/BaseMenuButton.h"

UConfirmationDialogueWidget::UConfirmationDialogueWidget(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	
}

// we assign the message for the confirmation box along with what message it should have for this
void UConfirmationDialogueWidget::ShowDialogueMessage(const FText& Message)
{
	CT_Message->SetText(Message);
	AddToViewport(); 
}

// when the dialogue box is created we want to start by playing the fade in animation
void UConfirmationDialogueWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	if (CA_FadeIn)
	{
		PlayAnimationForward(CA_FadeIn);
	}
}

// we bind the buttons for the confrim and cancel here
void UConfirmationDialogueWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	WB_Confirm->OnClicked().AddUObject(this, &ThisClass::OnConfirmClicked);
	WB_Cancel->OnClicked().AddUObject(this, &ThisClass::OnCancelClicked);
}

// we then fire whatever delegates are bound to it if they are and unbind them
void UConfirmationDialogueWidget::OnConfirmClicked()
{
	if (ConfirmSelection.IsBound())
	{
		ConfirmSelection.Execute(true); 
		ConfirmSelection.Unbind();
		RemoveFromParent(); 
	}
}
// same idea but we reverse the fade in animation and then remove it when the fade out is finished
void UConfirmationDialogueWidget::OnCancelClicked()
{
	if (ConfirmSelection.IsBound())
	{
		ConfirmSelection.Execute(false); 
		ConfirmSelection.Unbind();
		PlayAnimationReverse(CA_FadeIn);
		
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle,[this]()
		{
			RemoveFromParent(); 
		},CA_FadeIn->GetEndTime(),false); 
	}
}
