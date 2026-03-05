// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/Abilities/DodgeAbility.h"

#include <string>

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
	
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		CancelAbility(Handle,ActorInfo,ActivationInfo,true);
		return; 
	}
	
	FVector MovementVector;
	
	GetDirection(MovementVector); 
	
	UAnimMontage* SelectedAnim = SelectDodgeMontage(MovementVector); 
	
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

UAnimMontage* UDodgeAbility::SelectDodgeMontage(FVector Movement)
{
	UAnimMontage* SelectedAnim = ForwardDodgeAnim;

	Movement = Movement.GetSafeNormal();
	FVector ActorFowardVector = GetCharacterFromActorInfo()->GetActorForwardVector();
	FVector ActorRightVector = GetCharacterFromActorInfo()->GetActorRightVector();

	float ForwardDot = FVector::DotProduct(ActorFowardVector, Movement);
	float RightDot = FVector::DotProduct(ActorRightVector, Movement);
	
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString::Printf(TEXT("Forward: %.f,  Right: %.f"), ForwardDot, RightDot));

	if (FMath::Abs(ForwardDot) >= FMath::Abs(RightDot))
	{
		SelectedAnim = (ForwardDot >= 0.0f)? ForwardDodgeAnim : BackwardDodgeAnim;
	}
	else
	{
		SelectedAnim = (RightDot >= 0.0f)? RightDodgeAnim : LeftDodgeAnim;
	}
	return SelectedAnim;
	
}

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
