// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/EnhancedPlayerHealth.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

UEnhancedPlayerHealth::UEnhancedPlayerHealth(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), Health(50),MaxHealth(100)
{
	
}

void UEnhancedPlayerHealth::UpdateHealth(const FOnAttributeChangeData& Data)
{
	Health = Data.NewValue; 
	HealthBar->SetPercent(Health/MaxHealth); 
	
	if (CurrentHealthText)
	{
		const FString HealthText = FString::Printf(TEXT("%.0f"), Health); 
		CurrentHealthText->SetText(FText::FromString(HealthText));
	}
	
}
