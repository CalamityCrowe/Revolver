// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Abilities/BaseMeleeAbility.h"
#include "GameplayEffectTypes.h"

UBaseMeleeAbility::UBaseMeleeAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor; 
}

void UBaseMeleeAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	if (!IsValid(AttackMontage))
	{
		EndAbility(Handle,ActorInfo,ActivationInfo,true, true); 
	}
	
}

void UBaseMeleeAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	HandleHitScanEnd();
}


// if this function gets overridden to handle "Combos" the magnitude should be set to handle the damage increase/decrease then the parent call just after it
void UBaseMeleeAbility::HandleHitScanStart()
{
	// we need a validation check to get the melee weapon when that is made
	FGameplayEffectSpecHandle EffectSpec = MakeOutgoingGameplayEffectSpec(EffectClass,1);
	EffectSpec.Data->SetSetByCallerMagnitude(EffectCallerTag, EffectMagnitude); // this is how we apply the effect
	// lastly we will pass this to the weapon to use when we do the hit scans
}

void UBaseMeleeAbility::HandleHitScanEnd()
{
	/*if (EquppedWeapon)
	{
		EquppedWeapon->HitScanEnd()
	}*/
}

void UBaseMeleeAbility::OnMontageCompleted()
{
	EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,true, false); 
}

void UBaseMeleeAbility::OnMontageCancelled()
{
	EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,true, true); 
}

void UBaseMeleeAbility::OnMontageInterupted()
{
	EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,true, true);
}

