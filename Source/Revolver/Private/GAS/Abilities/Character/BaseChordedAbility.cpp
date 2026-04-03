// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Abilities/Character/BaseChordedAbility.h"

// engine
#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

// revolver 
#include "Characters/Player/RevolverPlayerCharacter.h"
#include "Components/WeaponManagerComponent.h"

UBaseChordedAbility::UBaseChordedAbility()
{
}

void UBaseChordedAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	if (bShouldCommitOnActivation)
	{
		if (CheckCooldown(Handle, ActorInfo) == false || CheckCost(Handle, ActorInfo) == false)
		{
			CancelAbility(Handle, ActorInfo, ActivationInfo, true);
			return; 
		}		
		else
		{
			CommitAbility(Handle, ActorInfo,ActivationInfo); 
		}
	}
	else
	{
		if (CheckCooldown(Handle, ActorInfo) == false || CheckCost(Handle, ActorInfo) == false)
		{	
			CancelAbility(Handle, ActorInfo, ActivationInfo, true);
			return; 
		}	
	}
	
	
	
	UAbilityTask_PlayMontageAndWait* PlayMontageAndWait = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy
	(this, 
		FName(""),
		AbilityMontage,
		1.0f,
		NAME_None
		); 
	
	PlayMontageAndWait->OnCompleted.AddDynamic(this, &UBaseChordedAbility::OnMontageCompleted); 
	PlayMontageAndWait->OnCancelled.AddDynamic(this, &UBaseChordedAbility::OnMontageCancelled);
	PlayMontageAndWait->OnInterrupted.AddDynamic(this, &UBaseChordedAbility::OnMontageInterupted); 
	PlayMontageAndWait->ReadyForActivation();
	
	MontageStarted(); // we add this call here so extending the functionality doesn't mean overriding the whole activate ability 

}

void UBaseChordedAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,bool bReplicateEndAbility, bool bWasCancelled)
{
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}


void UBaseChordedAbility::MontageStarted_Implementation()
{
	
}

void UBaseChordedAbility::OnMontageCompleted()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false); 
}

void UBaseChordedAbility::OnMontageCancelled()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
}

void UBaseChordedAbility::OnMontageInterupted()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
}

void UBaseChordedAbility::MontageTriggeredEvent(FGameplayEventData Payload)
{
	// we use this as a template to be overriden in another class
}

void UBaseChordedAbility::ApplyCameraEffect()
{
	if (UAbilitySystemComponent* ASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetAvatarActorFromActorInfo()))
	{
		ASC->AddLooseGameplayTag(CameraTag);
	}
}

void UBaseChordedAbility::RemoveCameraEffect()
{
	if (UAbilitySystemComponent* ASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetAvatarActorFromActorInfo()))
	{
		ASC->RemoveLooseGameplayTag(CameraTag);
	}
}

void UBaseChordedAbility::SetControlOrientMovement(bool NewControl, bool NewOrient)
{
	if (UCharacterMovementComponent* MovementComponent = GetCharacterFromActorInfo()->GetCharacterMovement())
	{
		MovementComponent->bUseControllerDesiredRotation = NewControl; 
		MovementComponent->bOrientRotationToMovement = NewOrient; 
	}
}

void UBaseChordedAbility::EnableAbilityOrientation()
{
	SetControlOrientMovement(true, false); 
}

void UBaseChordedAbility::DisableAbilityOrientation()
{
	if (ARevolverPlayerCharacter* PlayerCharacter = Cast<ARevolverPlayerCharacter>(GetAvatarActorFromActorInfo()))
	{
		if (PlayerCharacter->GetWeaponManager()->GetEquippedWeapon() == nullptr)
		{
			SetControlOrientMovement(false, true); 
		} 
	}
}

void UBaseChordedAbility::AbilityHitScan(const TArray<FHitResult> HitResults)
{
	if (HitResults.Num() > 0)
	{
		for (FHitResult Hit : HitResults)
		{
			UAbilitySystemComponent* HitASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Hit.GetActor()); 
			if (!HitActors.Contains(Hit.GetActor()) && HitASC)
			{
				HitActors.AddUnique(Hit.GetActor());
				FGameplayEffectSpecHandle EffectSpecHandle =  MakeOutgoingGameplayEffectSpec(EffectClass, 1); 
				EffectSpecHandle.Data->SetSetByCallerMagnitude(EffectMagnitudeTag,EffectMagnitude); 
				
				EffectSpecHandle.Data->GetContext().AddHitResult(Hit,true); 
				HitASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get()); 
			}
		}
	}
}
