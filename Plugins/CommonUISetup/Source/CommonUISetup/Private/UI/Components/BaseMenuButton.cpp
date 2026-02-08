// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Components/BaseMenuButton.h"
#include "CommonTextBlock.h"
#include "Components/OverlaySlot.h"

UBaseMenuButton::UBaseMenuButton(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer), ButtonText(FText::FromString("Main Menu Button"))
{

}

void UBaseMenuButton::NativePreConstruct()
{
	Super::NativePreConstruct();
	if (Text_ActionName)
	{
		Text_ActionName->SetText(ButtonText); 
		if (UOverlaySlot* OverlaySlot = Cast<UOverlaySlot>(Text_ActionName->Slot))
		{
			OverlaySlot->SetHorizontalAlignment(OverrideHorizontalAllignment); 
		}
	}
}

