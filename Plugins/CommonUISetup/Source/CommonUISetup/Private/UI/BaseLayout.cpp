// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BaseLayout.h"
#include "CommonActivatableWidget.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

UBaseLayout::UBaseLayout(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	
}

void UBaseLayout::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UBaseLayout::PushWidget(TSubclassOf<UCommonActivatableWidget> ActivatableWidgetClass)
{
	CAWS_WidgetStack->AddWidget(ActivatableWidgetClass); 
}
