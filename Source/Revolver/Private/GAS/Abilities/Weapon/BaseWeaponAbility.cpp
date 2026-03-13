// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Abilities/Weapon/BaseWeaponAbility.h"

// Engine/GAS
#include "GameplayEffectTypes.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"

// revolver
#include "Components/WeaponManagerComponent.h"
#include "Weapons/WeaponBase.h"

UBaseWeaponAbility::UBaseWeaponAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor; 
}

void UBaseWeaponAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	UWeaponManagerComponent* WeaponManager = GetAvatarActorFromActorInfo()->GetComponentByClass<UWeaponManagerComponent>(); 
	if (!WeaponManager)
	{
		EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,true,true);
		return; 
	}
	EquippedWeapon = WeaponManager->GetEquippedWeapon(); 
	if (!IsValid(EquippedWeapon) || !IsValid(AttackMontage))
	{
		EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,true,true);
		return; 
	}
	
	UAbilityTask_PlayMontageAndWait* AttackTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
		this, 
		TEXT("PlayAttackMontage"), 
		AttackMontage,
		1.0f,
		NAME_None
		); 
	
	AttackTask->OnCompleted.AddDynamic(this, &UBaseWeaponAbility::OnMontageCompleted);
	AttackTask->OnCancelled.AddDynamic(this, &UBaseWeaponAbility::OnMontageCancelled);
	AttackTask->OnInterrupted.AddDynamic(this, &UBaseWeaponAbility::OnMontageInterupted);
	AttackTask->ReadyForActivation();
	
	MontageStart(); // this function is left empty in this class so it can be extended else where
	

}

void UBaseWeaponAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

FVector UBaseWeaponAbility::GetSpawnLocation()
{
	if (EquippedWeapon){return EquippedWeapon->GetSpawnPoint(); }
	return GetAvatarActorFromActorInfo()->GetActorLocation(); 
}

void UBaseWeaponAbility::OnMontageCompleted()
{
	EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,true, false); 
}

void UBaseWeaponAbility::OnMontageCancelled()
{
	EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,true, true); 
}

void UBaseWeaponAbility::OnMontageInterupted()
{
	EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,true, true);
}

