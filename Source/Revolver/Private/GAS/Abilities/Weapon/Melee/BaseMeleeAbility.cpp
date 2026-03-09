// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Abilities/Weapon/Melee/BaseMeleeAbility.h"

// Engine/GAS
#include "GameplayEffectTypes.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"

// revolver
#include "Components/WeaponManagerComponent.h"
#include "Weapons/WeaponBase.h"

UBaseMeleeAbility::UBaseMeleeAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor; 
}

void UBaseMeleeAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	UWeaponManagerComponent* WeaponManager = GetAvatarActorFromActorInfo()->GetComponentByClass<UWeaponManagerComponent>(); 
	if (!WeaponManager)
	{
		EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,true,true);
	}
	EquippedWeapon = WeaponManager->GetEquippedWeapon(); 
	if (!IsValid(EquippedWeapon) || !IsValid(AttackMontage))
	{
		EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,true,true);
	}
	
	UAbilityTask_PlayMontageAndWait* AttackTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
		this, 
		TEXT("PlayAttackMontage"), 
		AttackMontage,
		1.0f,
		NAME_None
		); 
	
	AttackTask->OnCompleted.AddDynamic(this, &UBaseMeleeAbility::OnMontageCompleted);
	AttackTask->OnCancelled.AddDynamic(this, &UBaseMeleeAbility::OnMontageCancelled);
	AttackTask->OnInterrupted.AddDynamic(this, &UBaseMeleeAbility::OnMontageInterupted);
	AttackTask->ReadyForActivation();
	
	MontageStart(); // this function is left empty in this class so it can be extended else where
	
	AActor* AvatarActor = GetAvatarActorFromActorInfo();
	if (AvatarActor && AvatarActor->HasAuthority())
	{
		UAbilityTask_WaitGameplayEvent* HitScanStartEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(
			this,
			HitStartTag,
			nullptr,
			false,
			true
			); 
	
		HitScanStartEvent->EventReceived.AddDynamic(this, &UBaseMeleeAbility::HandleHitScanStart); 
		HitScanStartEvent->ReadyForActivation();

		UAbilityTask_WaitGameplayEvent* HitScanEndEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(
			this,
			HitEndTag,
			nullptr,
			false,
			true
			);
		
		HitScanEndEvent->EventReceived.AddDynamic(this, &UBaseMeleeAbility::HandleHitScanEnd);
		HitScanEndEvent->ReadyForActivation();
	}
}

void UBaseMeleeAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	HandleHitScanEnd(FGameplayEventData());
}


// if this function gets overridden to handle "Combos" the magnitude should be set to handle the damage increase/decrease then the parent call just after it
// we also only have a payload getting used here due to the UAbilityTask_WaitGameplayEvent
void UBaseMeleeAbility::HandleHitScanStart(FGameplayEventData Payload)
{
	if (IsValid(EquippedWeapon))
	{
		FGameplayEffectSpecHandle EffectSpec = MakeOutgoingGameplayEffectSpec(EffectClass,1);
		EffectSpec.Data->SetSetByCallerMagnitude(EffectCallerTag, EffectMagnitude); // this is how we apply the effect
		EquippedWeapon->HitScanStart(EffectSpec);
	}
}

void UBaseMeleeAbility::HandleHitScanEnd(FGameplayEventData Payload)
{
	if (IsValid(EquippedWeapon))
	{
		EquippedWeapon->HitScanEnd(); 
	}
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

