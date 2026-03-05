// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Attributes/EnhancedAttributeSet.h"
#include "GameplayEffectExtension.h"


UEnhancedAttributeSet::UEnhancedAttributeSet():Health(100.0f), MaxHealth(100.f), Damage(0.0f)
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
		
	}
}

void UEnhancedAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(GetHealth()); 
	}
	// will do something later with this
	
}
