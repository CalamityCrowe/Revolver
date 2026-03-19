// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Abilities/Character/RadialBurstAbility.h"


#include "AbilitySystemGlobals.h"
#include "GameplayCueManager.h"	
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Characters/CharacterBase.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Weapons/Projectiles/BaseProjectile.h"

URadialBurstAbility::URadialBurstAbility(): NumberOfProjectiles(8),RadialPitch(-30), ProjectileSpeed(1000), ProjectileClass(nullptr)
{
	
}

void URadialBurstAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	GetCharacterFromActorInfo()->GetCharacterMovement()->SetMovementMode(MOVE_Walking); 
}

void URadialBurstAbility::MontageStarted()
{
	Super::MontageStarted();
	GetCharacterFromActorInfo()->GetCharacterMovement()->SetMovementMode(MOVE_Flying); 
	
	UAbilityTask_WaitGameplayEvent* SpawnProjectileTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, 
		SpawnEventTag, 
		nullptr, 
		true,
		true
		);
	
	SpawnProjectileTask->EventReceived.AddDynamic(this, &URadialBurstAbility::EventRecieved);
	SpawnProjectileTask->ReadyForActivation();
}



void URadialBurstAbility::EventRecieved(FGameplayEventData EventData)
{
	float YawOffset = 360.f/NumberOfProjectiles;
	
	ACharacter* OwningCharacter = GetCharacterFromActorInfo(); 
	
	FVector ActorLocation = OwningCharacter->GetActorLocation();
	FVector UpVector = OwningCharacter->GetActorUpVector();
	FVector SpawnLocation =  ActorLocation + (UpVector * 200); 
	
	FVector ForwardVector = FVector(1, 0, 0) * 200;
	
	FGameplayCueParameters SpawnParams; 
	SpawnParams.Location = SpawnLocation;
	
	UAbilitySystemGlobals::Get().GetGameplayCueManager()->HandleGameplayCue(GetAvatarActorFromActorInfo(), SpawnCueTag, EGameplayCueEvent::Executed, SpawnParams); 
	
	FGameplayEffectSpecHandle DamageEffect = MakeOutgoingGameplayEffectSpec(EffectClass, 1);
	DamageEffect.Data.Get()->SetSetByCallerMagnitude(EffectMagnitudeTag,EffectMagnitude); 
	
	if (bStaggeredProjectiles)
	{
		StaggerSpawn(YawOffset, OwningCharacter, ActorLocation, SpawnLocation, ForwardVector, DamageEffect);
	}
	else
	{
		BurstSpawn(YawOffset, OwningCharacter, ActorLocation, SpawnLocation, ForwardVector, DamageEffect);
	}
	
	
}

void URadialBurstAbility::SpawnProjectile(const float YawOffset, ACharacter* OwningCharacter, const FVector& ActorLocation, const FVector& SpawnLocation, const FVector& ForwardVector, const FGameplayEffectSpecHandle& DamageEffect, int i)
{
	FRotator VectorRotation = FRotator(RadialPitch,YawOffset * i,0);
	FVector ForwardRotated = VectorRotation.RotateVector(ForwardVector) * 200;
	FVector TargetLocation = ActorLocation + ForwardRotated;
		
	DrawDebugLine(GetWorld(),SpawnLocation,TargetLocation,FColor::Green,false, 20); 
		
	FTransform SpawnTransform; SpawnTransform.SetLocation(SpawnLocation);
		
	if (ABaseProjectile* Projectile = GetWorld()->SpawnActorDeferred<ABaseProjectile>(ProjectileClass,SpawnTransform, OwningCharacter))
	{
		Projectile->SetProjectileDamage(DamageEffect); 
		Projectile->SetTargetLocation(TargetLocation);
		Projectile->SetSpeed(ProjectileSpeed);
		Projectile->SetInstigator(GetCharacterFromActorInfo()); 
		UGameplayStatics::FinishSpawningActor(Projectile,SpawnTransform); 
	}
}

void URadialBurstAbility::BurstSpawn(const float YawOffset, ACharacter* OwningCharacter, const FVector& ActorLocation, const FVector& SpawnLocation,
                                     const FVector& ForwardVector, const FGameplayEffectSpecHandle& DamageEffect)
{
	for (int i = 0; i < NumberOfProjectiles; ++i)
	{
		SpawnProjectile(YawOffset, OwningCharacter, ActorLocation, SpawnLocation, ForwardVector, DamageEffect, i);
	}
}

void URadialBurstAbility::StaggerSpawn(float YawOffset, ACharacter* OwningCharacter, const FVector& ActorLocation,
	const FVector& SpawnLocation, const FVector& ForwardVector, const FGameplayEffectSpecHandle& DamageEffect)
{
	CurrentProjectile = 0; 
	
	FTimerDelegate TimerDelegate;
	
	TimerDelegate.BindLambda([this, YawOffset, OwningCharacter, ActorLocation, SpawnLocation, ForwardVector, DamageEffect]
	{
		SpawnProjectile(YawOffset, OwningCharacter, ActorLocation, SpawnLocation, ForwardVector, DamageEffect, CurrentProjectile);
		CurrentProjectile++;
		if (CurrentProjectile >= NumberOfProjectiles)
		{
			GetWorld()->GetTimerManager().ClearTimer(TimerHandle); 
		}
	}); 
	// we clear the timer so there isn't multiple delegates bound 
	if (GetWorld()->GetTimerManager().IsTimerActive(TimerHandle))
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	}
	GetWorld()->GetTimerManager().SetTimer(TimerHandle,TimerDelegate,StaggeredSpawnTime,true); 
}
