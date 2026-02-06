// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PAges/ConfirmationDialogueWidget.h"

#include "CommonTextBlock.h"
#include "Animation/WidgetAnimation.h"
#include "UI/Components/BaseMenuButton.h"

UConfirmationDialogueWidget::UConfirmationDialogueWidget(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	
}

void UConfirmationDialogueWidget::ShowDialogueMessage(const FText& Message)
{
	CT_Message->SetText(Message);
	AddToViewport(); 
}

void UConfirmationDialogueWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	if (CA_FadeIn)
	{
		PlayAnimationForward(CA_FadeIn);
	}
}

void UConfirmationDialogueWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	WB_Confirm->OnClicked().AddUObject(this, &ThisClass::OnConfirmClicked);
	WB_Cancel->OnClicked().AddUObject(this, &ThisClass::OnCancelClicked);
}

void UConfirmationDialogueWidget::OnConfirmClicked()
{
	if (ConfirmSelection.IsBound())
	{
		ConfirmSelection.Execute(true); 
		ConfirmSelection.Unbind();
		RemoveFromParent(); 
	}
}

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
