// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Abilities/Character/Chorded/BaseToggleAbility.h"

UBaseToggleAbility::UBaseToggleAbility()
{
}

void UBaseToggleAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UBaseToggleAbility::OnMontageCompleted()
{
	
}

void UBaseToggleAbility::OnMontageCancelled()
{
	
}

void UBaseToggleAbility::OnMontageInterupted()
{
	
}
