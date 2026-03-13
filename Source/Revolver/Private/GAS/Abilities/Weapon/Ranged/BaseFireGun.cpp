// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Abilities/Weapon/Ranged/BaseFireGun.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Abilities/Tasks/AbilityTask_WaitTargetData.h"
#include "Abilities/Tasks/AbilityTask_SpawnActor.h"
#include "Kismet/GameplayStatics.h"
#include "Weapons/WeaponBase.h"
#include "Weapons/Projectiles/BaseProjectile.h"


// this is called in the base weapon ability class, this essentially just overrides the function and adds the relevant events to it
void UBaseFireGun::MontageStart()
{
	Super::MontageStart();
	
	// we create a gameplay event for the ASC to listen for and when the tag is sent it will do the fire weapon event
	UAbilityTask_WaitGameplayEvent* FireWeaponEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this,
	FireWeaponTag,nullptr , true, true); 
	
	FireWeaponEvent->EventReceived.AddDynamic(this, &UBaseFireGun::FireWeaponEvent); 
	FireWeaponEvent->ReadyForActivation(); 
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
	// we get where the projectile spawn from the weapon
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(GetSpawnLocation()); 
	FVector TargetLocation = PayLoad.Data[0].Get()->GetEndPoint(); // grabs the target location from the end point
	
	// we defer the spawning of the spawning here and this is where the actual values are passed in
	if (ABaseProjectile* Projectile = GetWorld()->SpawnActorDeferred<ABaseProjectile>(ProjectileClass, SpawnTransform, nullptr, OwningPawn))
	{
		FGameplayEffectSpecHandle EffectSpec = MakeOutgoingGameplayEffectSpec(EffectClass,1);
		EffectSpec.Data->SetSetByCallerMagnitude(EffectCallerTag, EffectMagnitude); 
		Projectile->SetTargetLocation(TargetLocation); 
		Projectile->SetProjectileDamage(EffectSpec); 
		Projectile->SetSpeed(ProjectileSpeed); 
		UGameplayStatics::FinishSpawningActor(Projectile, SpawnTransform);
	}
}
