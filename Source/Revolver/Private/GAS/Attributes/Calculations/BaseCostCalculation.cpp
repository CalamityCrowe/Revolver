// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Attributes/Calculations/BaseCostCalculation.h"

#include "GAS/Abilities/Character/BaseChordedAbility.h"


// todo: look at attributes specifically for abilities (Strength, duration, etc)
float UBaseCostCalculation::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	if (const UBaseChordedAbility* Ability = Cast<UBaseChordedAbility>(Spec.GetContext().GetAbility()))
	{
		return Ability->GetAbilityCost(); 
	}
	return Super::CalculateBaseMagnitude_Implementation(Spec); 
}
