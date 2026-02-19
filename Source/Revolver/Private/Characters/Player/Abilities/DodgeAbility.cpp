// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/Abilities/DodgeAbility.h"

#include "GameFramework/Character.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"


UDodgeAbility::UDodgeAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor; 
}

void UDodgeAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                    const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	UAnimMontage* SelectedAnim = ForwardDodgeAnim; 
			
	FVector MovementVector;
	
	GetDirection(MovementVector); 
	
	if (MovementVector.IsNearlyZero())
	{
		CancelAbility(Handle,ActorInfo,ActivationInfo,false); 
	}
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		
	}
	
	UAbilityTask_PlayMontageAndWait* Task = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
		this,
		TEXT("PlayDodgeMontage"),
		SelectedAnim,  // Your UAnimMontage* variable
		1.0f,          // PlayRate
		NAME_None      // StartSection
	);
	
	Task->OnCompleted.AddDynamic(this, &UDodgeAbility::OnMontageCompleted);
	Task->OnInterrupted.AddDynamic(this, &UDodgeAbility::OnMontageInterrupted);
	Task->OnCancelled.AddDynamic(this, &UDodgeAbility::OnMontageCancelled);
	Task->ReadyForActivation();
}

void UDodgeAbility::GetDirection(FVector& OutLastMovement) const
{
	if (ACharacter* OwningCharacter = GetCharacterFromActorInfo())
	{
		OutLastMovement = OwningCharacter->GetLastMovementInputVector();
	}
}

/*UAnimMontage* UDodgeAbility::SelectDodgeMontage(FVector Movement)
{
	
}*/

void UDodgeAbility::OnMontageCompleted()
{
	EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,true, false); 
}

void UDodgeAbility::OnMontageInterrupted()
{
	EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,true, true); 
}

void UDodgeAbility::OnMontageCancelled()
{
	EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,true, true); 
}
