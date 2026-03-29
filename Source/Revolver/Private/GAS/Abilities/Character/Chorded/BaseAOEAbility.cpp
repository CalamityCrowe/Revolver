// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Abilities/Character/Chorded/BaseAOEAbility.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "GameplayCueManager.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Abilities/Tasks/AbilityTask_WaitTargetData.h"
#include "GAS/Targeting/TargetActor_GroundDecal.h"
#include "Kismet/KismetSystemLibrary.h"

UBaseAOEAbility::UBaseAOEAbility()
{
	
}

void UBaseAOEAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	ApplyCameraEffect(); 
	EnableAbilityOrientation(); 	
}


void UBaseAOEAbility::MontageStarted()
{
	Super::MontageStarted();
	
	bIsWaitingTargetDetails = true;
	
}

void UBaseAOEAbility::LoopTargetingAnimation()
{
	UAbilityTask_PlayMontageAndWait* LoopingTargetTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
		this, 
		NAME_None,
		TargetingAnimation,
		1.0f
		); 
	LoopingTargetTask->OnCompleted.AddDynamic(this, &UBaseAOEAbility::TargetingMontageCompleted); 
	LoopingTargetTask->OnBlendOut.AddDynamic(this, &UBaseAOEAbility::TargetingMontageCompleted);
	LoopingTargetTask->OnInterrupted.AddDynamic(this, &UBaseAOEAbility::TargetingInterrupted); 
	
	LoopingTargetTask->ReadyForActivation(); 
}


void UBaseAOEAbility::ValidTargeting(const FGameplayAbilityTargetDataHandle& Payload)
{
	bIsWaitingTargetDetails = false;
	if (!Payload.Data.IsEmpty())
	{
		ConfirmedAOE =  Payload.Data[0]->GetHitResult()->Location;
		ConfirmStrike(); 
	}
}

void UBaseAOEAbility::ConfirmStrike()
{
	if (!CommitAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo))
	{
		EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,true,true);
		return;
	}
	
	RemoveCameraEffect(); 
	
	UAbilityTask_PlayMontageAndWait* CastingTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy
	(this, NAME_None,
		CastingMontage,1.0f); 
	
	CastingTask->OnCompleted.AddDynamic(this, &UBaseAOEAbility::CastingCompleted);
	CastingTask->OnInterrupted.AddDynamic(this, &UBaseAOEAbility::CastingInterrupted);
	CastingTask->ReadyForActivation();
	
	UAbilityTask_WaitGameplayEvent* MontageTriggerTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(
		this, MontageTriggeredTag, nullptr, false, true
		); 
	
	MontageTriggerTask->EventReceived.AddDynamic(this, &UBaseAOEAbility::MontageTriggeredEvent);
	MontageTriggerTask->ReadyForActivation();
	
}


void UBaseAOEAbility::MontageTriggeredEvent(FGameplayEventData Payload)
{
	Super::MontageTriggeredEvent(Payload); 
	AOEDamage(); 
	
	// we could remove the aoe on the ground if it is on the ground here still
	FGameplayCueParameters CueParameters; 
	CueParameters.Location = ConfirmedAOE; 
	UAbilitySystemGlobals::Get().GetGameplayCueManager()->ExecuteGameplayCue_NonReplicated(GetAvatarActorFromActorInfo(),AOEDamageEffectTag,CueParameters);
	
}

void UBaseAOEAbility::AOEDamage()
{
	// we could do a has authority chekc here if we are doing networked based code
	
	// we empty this to ensure that no previous hits are still in here for the hit scan
	HitActors.Empty(); 
	
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetAvatarActorFromActorInfo()); 
	
	TArray<FHitResult> HitResults;
	
	UKismetSystemLibrary::SphereTraceMultiForObjects(
		GetWorld(),ConfirmedAOE,ConfirmedAOE,AOERadius, 
		ObjectTypes,false,ActorsToIgnore,EDrawDebugTrace::ForDuration,
		HitResults,true); 
	
	AbilityHitScan(HitResults); 
	
}

void UBaseAOEAbility::OnMontageCompleted()
{
	bIsReloopingMontage = true;
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
			GroundDecalTarget->DecalMaterial = TargetingMaterial;
		}
		WaitTargetData->FinishSpawningActor(this, TargetActor); 
	}
	
	WaitTargetData->ValidData.AddDynamic(this, &UBaseAOEAbility::ValidTargeting);
	
}

void UBaseAOEAbility::TargetingMontageCompleted()
{
	if (bIsWaitingTargetDetails)
	{
		bIsReloopingMontage = true;
		LoopTargetingAnimation(); 
	}
}

void UBaseAOEAbility::TargetingInterrupted()
{
	if (bIsReloopingMontage)
	{
		bIsReloopingMontage = false;
		return; 
	}
	
	if (bIsWaitingTargetDetails)
	{
		EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,true,true); 
	}
}

void UBaseAOEAbility::CastingInterrupted()
{
	DisableAbilityOrientation(); 
	EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,true,true);
}

void UBaseAOEAbility::CastingCompleted()
{
	DisableAbilityOrientation(); 
	EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,true,false);
}