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
	
	AActor* AvatarActor = GetAvatarActorFromActorInfo(); 
	if (AvatarActor && AvatarActor->HasAuthority())
	{
		/*UAbilityTask_WaitGameplayEvent* SpawnProjectileEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(
			this, SpawnProjectileTag,
			nullptr,
			false, 
			true
			); 
		
		SpawnProjectileEvent->EventReceived.AddDynamic(this, &UBaseFireGun::EventRecieved);
		SpawnProjectileEvent->ReadyForActivation(); */
		
		/*UAbilityTask_WaitTargetData* WaitTargetDataTask = UAbilityTask_WaitTargetData::WaitTargetData
		(this, // owning ability
			TEXT("WaitTargetData"),
			EGameplayTargetingConfirmation::Instant,
			AGameplayAbilityTargetActor::StaticClass()
			); 
		
		WaitTargetDataTask->ValidData.AddDynamic(this,&UBaseFireGun::EventRecieved); 
		
		AGameplayAbilityTargetActor* SpawnedActor = nullptr; 
		if (WaitTargetDataTask->BeginSpawningActor(this, TargetingClass, SpawnedActor))
		{
			if (SpawnedActor)
			{
				SpawnedActor->StartLocation = MakeTargetLocationInfoFromOwnerActor(); 
				SpawnedActor->bDebug = true; 
			}
			WaitTargetDataTask->FinishSpawningActor(this, SpawnedActor);
		}
		WaitTargetDataTask->ReadyForActivation();*/
	}
	
}

void UBaseFireGun::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UBaseFireGun::EventRecieved(const FGameplayAbilityTargetDataHandle& Payload)
{
	/*
	UAbilityTask_SpawnActor* SpawnActor = UAbilityTask_SpawnActor::SpawnActor
	(
		this,Payload,ProjectileClass
		);
	AActor* Actor; 
	
	
	if (SpawnActor->BeginSpawningActor(this, Payload,ProjectileClass, Actor))
	{
		if (ABaseProjectile* Projectile = Cast<ABaseProjectile>(Actor))
		{
			Projectile->SetActorLocation(GetOwningActorFromActorInfo()->GetActorLocation());
			Projectile->SetInstigator(Cast<APawn>(GetAvatarActorFromActorInfo())); 
			Projectile->SetTargetLocation(Payload.Data[0].Get()->GetEndPoint()); 
			
		}
		SpawnActor->FinishSpawningActor(this,FGameplayAbilityTargetDataHandle(), Actor);
		SpawnActor->ReadyForActivation(); 
	}
	*/

}

void UBaseFireGun::OnMontageCompleted()
{
	EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo, true, false);
}

void UBaseFireGun::OnMontageCancelled()
{
	EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo, true, true);
}
