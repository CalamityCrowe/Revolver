// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Abilities/Character/BaseChordedAbility.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"

UBaseChordedAbility::UBaseChordedAbility()
{
}

void UBaseChordedAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	if (bShouldCommitOnActivation)
	{
		if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
		{
			CancelAbility(Handle, ActorInfo, ActivationInfo, true);
			return; 
		}		
	}
	
	if (CheckCooldown(Handle, ActorInfo) == false || CheckCost(Handle, ActorInfo) == false)
	{
		return; 
	}
	
	
	UAbilityTask_PlayMontageAndWait* PlayMontageAndWait = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy
	(this, 
		FName(""),
		AbilityMontage,
		1.0f,
		NAME_None
		); 
	
	PlayMontageAndWait->OnCompleted.AddDynamic(this, &UBaseChordedAbility::OnMontageCompleted); 
	PlayMontageAndWait->OnCancelled.AddDynamic(this, &UBaseChordedAbility::OnMontageCancelled);
	PlayMontageAndWait->OnInterrupted.AddDynamic(this, &UBaseChordedAbility::OnMontageInterupted); 
	PlayMontageAndWait->ReadyForActivation();
	
	MontageStarted(); // we add this call here so extending the functionality doesn't mean overriding the whole activate ability 

}

void UBaseChordedAbility::MontageStarted()
{
	// we do nothing in here, but if we are doing something like spawning projectiles or something like that, then we can create an event here for it
}

void UBaseChordedAbility::OnMontageCompleted()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false); 
}

void UBaseChordedAbility::OnMontageCancelled()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
}

void UBaseChordedAbility::OnMontageInterupted()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
}
