// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Components/BaseOptionsRotator.h"

#include "CommonTextBlock.h"
#include "Components/Image.h"

UBaseOptionsRotator::UBaseOptionsRotator(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
}

void UBaseOptionsRotator::MarkAsCustom()
{
	MyText->SetText(FText::FromString("Custom")); 
	
	HandleOptionSelected(6); 
}

void UBaseOptionsRotator::HandleOptionsPopulated(int32 Count)
{
	if (!Highlighted_Option)return; 
	
	if (UMaterialInstanceDynamic* DynMat = Highlighted_Option->GetDynamicMaterial())
	{
		DynMat->SetScalarParameterValue(TEXT("Pip Count"),Count); 
	}
}

void UBaseOptionsRotator::HandleOptionSelected(int32 Index)
{
	if (!Highlighted_Option)return; 
	
	if (UMaterialInstanceDynamic* DynMat = Highlighted_Option->GetDynamicMaterial())
	{
		DynMat->SetScalarParameterValue(TEXT("Active Pip"),Index); 
	}
}
