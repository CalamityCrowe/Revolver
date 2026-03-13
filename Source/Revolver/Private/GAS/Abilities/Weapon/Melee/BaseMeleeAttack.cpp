// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Abilities/Weapon/Melee/BaseMeleeAttack.h"

//engine
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Weapons/WeaponBase.h"


void UBaseMeleeAttack::MontageStart()
{
	Super::MontageStart();
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

	HitScanStartEvent->EventReceived.AddDynamic(this, &UBaseMeleeAttack::HandleHitScanStart); 
	HitScanStartEvent->ReadyForActivation();

	UAbilityTask_WaitGameplayEvent* HitScanEndEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(
		this,
		HitEndTag,
		nullptr,
		false,
		true
		);
	
	HitScanEndEvent->EventReceived.AddDynamic(this, &UBaseMeleeAttack::HandleHitScanEnd);
	HitScanEndEvent->ReadyForActivation();
}
}

void UBaseMeleeAttack::HandleHitScanStart(FGameplayEventData Payload)
{
	if (IsValid(EquippedWeapon))
	{
		FGameplayEffectSpecHandle EffectSpec = MakeOutgoingGameplayEffectSpec(EffectClass,1);
		EffectSpec.Data->SetSetByCallerMagnitude(EffectCallerTag, EffectMagnitude); // this is how we apply the effect
		EquippedWeapon->HitScanStart(EffectSpec);
	}
}

void UBaseMeleeAttack::HandleHitScanEnd(FGameplayEventData Payload)
{
	if (IsValid(EquippedWeapon))
	{
		EquippedWeapon->HitScanEnd(); 
	}
}
