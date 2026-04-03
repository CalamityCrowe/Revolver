// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RevolverPlayerMana.h"
#include "AbilitySystemComponent.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "GAS/Attributes/RevolverAttributeSet.h"
#include "Player/RevolverPlayerState.h"

URevolverPlayerMana::URevolverPlayerMana(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)  
{
}

void URevolverPlayerMana::NativeConstruct()
{
	Super::NativeConstruct();
	if (ARevolverPlayerState* PS = GetOwningPlayerState<ARevolverPlayerState>())
	{
		if (UAbilitySystemComponent* ASC=  PS->GetAbilitySystemComponent())
		{
			GEngine->AddOnScreenDebugMessage(-1,5,FColor::Yellow,"MANA"); 
			Mana = ASC->GetNumericAttribute(URevolverAttributeSet::GetManaAttribute()); 
			MaxMana = ASC->GetNumericAttribute(URevolverAttributeSet::GetMaxManaAttribute());
			if (ManaBar && ManaText)
			{
				ManaBar->SetPercent(Mana/MaxMana); 
				ManaText->SetText(FText::AsNumber(FMath::TruncToInt(Mana))); 
			}
		
			DisplayMana = Mana; 
			FString ManaString = FString::Printf(TEXT("%.0f"), DisplayMana);
			ManaText->SetText(FText::FromString(ManaString));
			
			ASC->GetGameplayAttributeValueChangeDelegate(URevolverAttributeSet::GetManaAttribute()).AddUObject(this, & URevolverPlayerMana::UpdateMana); 
		}		
	}
	
}

void URevolverPlayerMana::NativeDestruct()
{
	Super::NativeDestruct();
}

void URevolverPlayerMana::UpdateMana(const FOnAttributeChangeData& Data)
{
	OldMana = DisplayMana;
	Mana = Data.NewValue;
	Alpha = 0; 
	
	if (GetWorld()->GetTimerManager().IsTimerActive(ManaChangeTimer))
	{
		GetWorld()->GetTimerManager().ClearTimer(ManaChangeTimer);
	}
	GetWorld()->GetTimerManager().SetTimer(ManaChangeTimer, this, &URevolverPlayerMana::AnimateChange, TimerInterval, true); 
}

void URevolverPlayerMana::AnimateChange()
{
	Alpha = FMath::Clamp(Alpha+= (TimerInterval/AnimDuration), 0.0f , 1.0f); 
	DisplayMana = FMath::Lerp(OldMana, Mana, Alpha); 
	if (ManaBar && ManaText)
	{
		ManaBar->SetPercent(DisplayMana);
		FString ManaString = FString::Printf(TEXT("%.0f"), DisplayMana); 
		ManaText->SetText(FText::FromString(ManaString)); 
	}
	
	if (Alpha >= 1.0f)
	{
		GetWorld()->GetTimerManager().ClearTimer(ManaChangeTimer);
	}
}
