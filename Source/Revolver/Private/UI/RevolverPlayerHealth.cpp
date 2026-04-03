// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RevolverPlayerHealth.h"

#include "AbilitySystemComponent.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "GAS/Attributes/EnhancedAttributeSet.h"
#include "Player/RevolverPlayerState.h"

URevolverPlayerHealth::URevolverPlayerHealth(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	
}

void URevolverPlayerHealth::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (ARevolverPlayerState* PS = GetOwningPlayerState<ARevolverPlayerState>())
	{
		UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
		if (!ASC)
		{
			return; 
		}
		Health = ASC->GetNumericAttribute(UEnhancedAttributeSet::GetHealthAttribute()); 
		MaxHealth = ASC->GetNumericAttribute(UEnhancedAttributeSet::GetMaxHealthAttribute());
		HealthBar->SetPercent(Health/MaxHealth); 
		 
		DisplayHealth = Health;
		
		FString HealthString = FString::Printf(TEXT("%.0f"), Health); 
		CurrentHealthText->SetText(FText::FromString(HealthString)); 
		
		FString MaxHealthString = FString::Printf(TEXT("%.0f"), MaxHealth);
		MaxHealthText->SetText(FText::FromString(MaxHealthString));
		
		ASC->GetGameplayAttributeValueChangeDelegate(UEnhancedAttributeSet::GetHealthAttribute()).AddUObject(this, &URevolverPlayerHealth::UpdateHealth);
	}
}

void URevolverPlayerHealth::NativeDestruct()
{
	Super::NativeDestruct();
}

void URevolverPlayerHealth::UpdateHealth(const FOnAttributeChangeData& Data)
{
	OldHealth = DisplayHealth; 
	Health = Data.NewValue; 
	Alpha = 0; 

	if (GetWorld()->GetTimerManager().IsTimerActive(HealthChangeTimer))
	{
		GetWorld()->GetTimerManager().ClearTimer(HealthChangeTimer);
	}
	GetWorld()->GetTimerManager().SetTimer(HealthChangeTimer,this,&URevolverPlayerHealth::AnimateChange, TimerInterval, true); 
}

void URevolverPlayerHealth::AnimateChange()
{
	Alpha =  FMath::Clamp(Alpha += (TimerInterval/AnimDuration),0.0f,1.0f);
	DisplayHealth = FMath::Lerp(OldHealth,Health,Alpha);
	HealthBar->SetPercent(DisplayHealth/MaxHealth);
	
	if (CurrentHealthText)
	{
		FString HealthString = FString::Printf(TEXT("%.0f"), DisplayHealth);
		CurrentHealthText->SetText(FText::FromString(HealthString));
	}
	if (Alpha >= 1.0f)
	{
		GetWorld()->GetTimerManager().ClearTimer(HealthChangeTimer);
	}
}
