// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Abilities/Weapon/Ranged/BaseFireGun.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Abilities/Tasks/AbilityTask_WaitTargetData.h"
#include "Abilities/Tasks/AbilityTask_SpawnActor.h"
#include "Weapons/Projectiles/BaseProjectile.h"


UBaseFireGun::UBaseFireGun()
{
}

void UBaseFireGun::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	UAbilityTask_PlayMontageAndWait* FireGunTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
		this, 
		TEXT("FireGunMontage"),
		FireMontage,
		1.0f,
		NAME_None); 
	
	
	FireGunTask->OnCancelled.AddDynamic(this, &UBaseFireGun::OnMontageCancelled);
	FireGunTask->OnInterrupted.AddDynamic(this, &UBaseFireGun::OnMontageCancelled); 
	FireGunTask->OnCompleted.AddDynamic(this, &UBaseFireGun::OnMontageCompleted); 
	FireGunTask->ReadyForActivation(); 
	
}

void UBaseFireGun::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UBaseFireGun::OnMontageCompleted()
{
	EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo, true, false);
}

void UBaseFireGun::OnMontageCancelled()
{
	EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo, true, true);
}
