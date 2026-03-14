// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Abilities/Character/RadialBurstAbility.h"

#include "AbilitySystemGlobals.h"
#include "GameplayCueManager.h"	
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Weapons/Projectiles/BaseProjectile.h"

URadialBurstAbility::URadialBurstAbility()
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
	float YawOffset = 360/NumberOfProjectiles;
	
	ACharacter* Character = GetCharacterFromActorInfo();
	FVector SpawnLocation =  Character->GetActorLocation() + (Character->GetActorUpVector() * 200); 
	FVector ForwardVector = Character->GetActorForwardVector();
	
	FGameplayCueParameters SpawnParams; 
	SpawnParams.Location = SpawnLocation;
	
	UAbilitySystemGlobals::Get().GetGameplayCueManager()->HandleGameplayCue(GetAvatarActorFromActorInfo(), SpawnCueTag, EGameplayCueEvent::Executed, SpawnParams); 
	
	FGameplayEffectSpecHandle DamageEffect = MakeOutgoingGameplayEffectSpec(EffectClass, 1);
	DamageEffect.Data.Get()->SetSetByCallerMagnitude(EffectMagnitudeTag,EffectMagnitude); 
	
	for (int i = 0; i < NumberOfProjectiles; ++i)
	{
		FRotator VectorRotation = FRotator(RadialPitch,YawOffset * i,0);
		FVector ForwardRotated = VectorRotation.RotateVector(ForwardVector) * 200;
		FVector TargetLocation = Character->GetActorLocation() + ForwardRotated;
		
		FTransform SpawnTransform; SpawnTransform.SetLocation(SpawnLocation);
		
		if (ABaseProjectile* Projectile = GetWorld()->SpawnActorDeferred<ABaseProjectile>(ProjectileClass,SpawnTransform, Character))
		{
			Projectile->SetProjectileDamage(DamageEffect); 
			Projectile->SetTargetLocation(TargetLocation);
			UGameplayStatics::FinishSpawningActor(Projectile,SpawnTransform); 
		}
	}
	
}
