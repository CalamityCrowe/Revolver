// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Abilities/Weapon/Ranged/BaseFireGun.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Abilities/Tasks/AbilityTask_WaitTargetData.h"
#include "Abilities/Tasks/AbilityTask_SpawnActor.h"
#include "Kismet/GameplayStatics.h"
#include "Weapons/Projectiles/BaseProjectile.h"


UBaseFireGun::UBaseFireGun()
{
}

void UBaseFireGun::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	UAbilityTask_PlayMontageAndWait* PlayMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
		this, 
		TEXT("FireGunMontage"),
		FireMontage,
		1.0f,
		NAME_None); 
	
	
	PlayMontageTask->OnCancelled.AddDynamic(this, &UBaseFireGun::OnMontageCancelled);
	PlayMontageTask->OnInterrupted.AddDynamic(this, &UBaseFireGun::OnMontageCancelled); 
	PlayMontageTask->OnCompleted.AddDynamic(this, &UBaseFireGun::OnMontageCompleted); 
	PlayMontageTask->ReadyForActivation(); 
	
	UAbilityTask_WaitGameplayEvent* FireWeaponEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this,
		FireWeaponTag,nullptr , true, true); 
	
	FireWeaponEvent->EventReceived.AddDynamic(this, &UBaseFireGun::FireWeaponEvent); 
	FireWeaponEvent->ReadyForActivation(); 
}

void UBaseFireGun::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

// on the fire weapon event, we do a target trace to get where the impact point should be for the projectile to head to.
void UBaseFireGun::FireWeaponEvent(FGameplayEventData Payload)
{
	UAbilityTask_WaitTargetData* WaitData = UAbilityTask_WaitTargetData::WaitTargetData(
	this, 
	TEXT(""),EGameplayTargetingConfirmation::Instant,TargetingClass); 
	
	WaitData->ValidData.AddDynamic(this, &UBaseFireGun::ValidDataEvent); 
	
	AGameplayAbilityTargetActor* TargetActor = nullptr; 
	if (WaitData->BeginSpawningActor(this,TargetingClass, TargetActor)) // we defer the spawn using the built-in begin/finish functions
	{
		TargetActor->StartLocation = MakeTargetLocationInfoFromOwnerActor();
#if WITH_EDITOR
		TargetActor->bDebug = true; // we enaable debug here
#endif
		WaitData->FinishSpawningActor(this,TargetActor);
	}
	WaitData->ReadyForActivation(); 
}


// when the valid data event fires, we essentially do a defered spawn on the projectile to give the correct end point to calculate the direction it should move
void UBaseFireGun::ValidDataEvent(const FGameplayAbilityTargetDataHandle& PayLoad)
{
	// we check the owning pawn is still valid
	APawn* OwningPawn = Cast<APawn>(GetAvatarActorFromActorInfo());
	if (!OwningPawn)
	{
		return; 
	}
	// we get where the projectile should spawn from the pawn right now
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(OwningPawn->GetActorLocation()); 
	FVector TargetLocation = PayLoad.Data[0].Get()->GetEndPoint(); // grabs the target location from the end point
	
	// we defer the spawning of the spawning here and this is where the actual values are passed in
	if (ABaseProjectile* Projectile = GetWorld()->SpawnActorDeferred<ABaseProjectile>(ProjectileClass, SpawnTransform, nullptr, OwningPawn))
	{
		FGameplayEffectSpecHandle EffectSpec = MakeOutgoingGameplayEffectSpec(DamageEffect,1);
		EffectSpec.Data->SetSetByCallerMagnitude(DamageTag, Damage); 
		Projectile->SetTargetLocation(TargetLocation); 
		Projectile->SetProjectileDamage(EffectSpec); 
		UGameplayStatics::FinishSpawningActor(Projectile, SpawnTransform);
	}
}


void UBaseFireGun::OnMontageCompleted()
{
	EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo, true, false);
}

void UBaseFireGun::OnMontageCancelled()
{
	EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo, true, true);
}
