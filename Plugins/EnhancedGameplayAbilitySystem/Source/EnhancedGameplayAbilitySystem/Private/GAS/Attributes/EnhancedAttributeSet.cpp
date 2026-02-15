// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Attributes/EnhancedAttributeSet.h"

UEnhancedAttributeSet::UEnhancedAttributeSet():MaxHealth(100.f), Health(100.0f), Damage(0.0f)
{
}

void UEnhancedAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
	}
	else if (Attribute == GetMaxHealthAttribute())
	{
		if (NewValue >= GetMaxHealth())
		{
			
		}
	}
}

void UEnhancedAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	// will do something later with this
	
}
