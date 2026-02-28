// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Abilities/EquipWeaponAbility.h"

#include "Components/WeaponManagerComponent.h"
#include "GAS/Abilities/BaseMeleeAbility.h"
#include "Weapons/WeaponBase.h"

UEquipWeaponAbility::UEquipWeaponAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor; 
	FAbilityTriggerData TriggerData;
	TriggerData.TriggerTag = FGameplayTag::RequestGameplayTag("Event.Abilities.EquipWeapon");
	TriggerData.TriggerSource = EGameplayAbilityTriggerSource::GameplayEvent; 
	AbilityTriggers.Add(TriggerData); 
}

void UEquipWeaponAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	CommitAbility(Handle,ActorInfo,ActivationInfo);
	
	FGameplayTagContainer TargetTags = TriggerEventData->TargetTags;
	
	if (UWeaponManagerComponent* WeaponManager = GetAvatarActorFromActorInfo()->GetComponentByClass<UWeaponManagerComponent>())
	{
		FGameplayTag EquipTag = TargetTags.GetByIndex(0); 
		if (EquipTag == FGameplayTag::RequestGameplayTag("Weapon.Melee"))
		{
			WeaponManager->EquipWeapon(MeleeWeaponClass); 
			if (UAnimInstance* AnimInstance = WeaponManager->GetAnimInstance())
			{
				if (AnimInstance->OnMontageEnded.IsBound())
				{
					AnimInstance->OnMontageEnded.RemoveDynamic(this, &UEquipWeaponAbility::OnMontageCompleted);
				}	
				AnimInstance->OnMontageEnded.AddDynamic(this, &UEquipWeaponAbility::OnMontageCompleted); 
			}
			
		}
	}
	//EndAbility(Handle,ActorInfo,ActivationInfo,true,false);
}

void UEquipWeaponAbility::OnMontageCompleted(UAnimMontage* Montage, bool bWasCancelled)
{
	EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,true, bWasCancelled); 
}
