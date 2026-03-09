// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Abilities/Passive/BasePassiveAbility.h"

#include "AbilitySystemComponent.h"

UBasePassiveAbility::UBasePassiveAbility()
{
	
}

void UBasePassiveAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
}

void UBasePassiveAbility::OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnRemoveAbility(ActorInfo, Spec);
	
	if (UAbilitySystemComponent* ASC = ActorInfo->AbilitySystemComponent.Get())
	{
		
	} 
	
}
