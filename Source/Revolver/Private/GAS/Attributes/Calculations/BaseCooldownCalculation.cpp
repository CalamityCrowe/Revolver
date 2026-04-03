// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Attributes/Calculations/BaseCooldownCalculation.h"

#include "GAS/Abilities/Character/BaseChordedAbility.h"

float UBaseCooldownCalculation::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	
	if (const UBaseChordedAbility* Ability = Cast<UBaseChordedAbility>(Spec.GetContext().GetAbility()))
	{
		return Ability->GetAbilityCooldown(); 
	}
	
	return Super::CalculateBaseMagnitude_Implementation(Spec);
}
