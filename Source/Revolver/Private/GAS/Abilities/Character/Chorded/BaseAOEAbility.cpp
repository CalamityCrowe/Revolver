// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Abilities/Character/Chorded/BaseAOEAbility.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitTargetData.h"
#include "GAS/Targeting/TargetActor_GroundDecal.h"

UBaseAOEAbility::UBaseAOEAbility()
{
	
}

void UBaseAOEAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UBaseAOEAbility::MontageStarted()
{
	Super::MontageStarted();
	
	bIsWaitingTargetDetails = true;
	
}

void UBaseAOEAbility::OnMontageCompleted()
{
	LoopTargetingAnimation(); 
	
	bIsWaitingTargetDetails = true; 
	
	UAbilityTask_WaitTargetData* WaitTargetData = UAbilityTask_WaitTargetData::WaitTargetData(
		this, FName(""), TargetingConfirmation, TargetingClass); 
	
	
	AGameplayAbilityTargetActor* TargetActor = nullptr; 
	if (WaitTargetData->BeginSpawningActor(this, TargetingClass, TargetActor))
	{
		if (ATargetActor_GroundDecal* GroundDecalTarget = Cast<ATargetActor_GroundDecal>(TargetActor))
		{
			GroundDecalTarget->StartLocation = MakeTargetLocationInfoFromOwnerActor(); 
			GroundDecalTarget->MaxRange = MaxRange;			
			GroundDecalTarget->DecalSize = (AOERadius * 2);
		}
		
	}
}

void UBaseAOEAbility::LoopTargetingAnimation()
{
	UAbilityTask_PlayMontageAndWait* LoopingTargetTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
		this, 
		FName("LoopTargetingAnimation"),
		TargetingAnimation,
		1.0f
		); 
	LoopingTargetTask->OnCompleted.AddDynamic(this, &UBaseAOEAbility::TargetingMontageCompleted); 
	LoopingTargetTask->OnBlendOut.AddDynamic(this, &UBaseAOEAbility::TargetingMontageCompleted);
	LoopingTargetTask->OnInterrupted.AddDynamic(this, &UBaseAOEAbility::TargetingInterrupted); 
	
	LoopingTargetTask->ReadyForActivation(); 
}

void UBaseAOEAbility::TargetingMontageCompleted()
{
	if (bIsWaitingTargetDetails)
	{
		LoopTargetingAnimation(); 
	}
}

void UBaseAOEAbility::TargetingInterrupted()
{
	if (bIsWaitingTargetDetails)
	{
		EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,true,true); 
	}
}
