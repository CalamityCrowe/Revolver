// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Abilities/Character/Chorded/ChargeAbility.h"
// engine 
#include "Abilities/Tasks/AbilityTask_ApplyRootMotionConstantForce.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetSystemLibrary.h"

// revolver
#include "Characters/Player/RevolverPlayerCharacter.h"
#include "Components/WeaponManagerComponent.h"
#include "Player/RevolverPlayerController.h"


UChargeAbility::UChargeAbility()
{
}

void UChargeAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                     const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                     const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	if (ACharacter* Character = GetCharacterFromActorInfo())
	{
		if (ARevolverPlayerController* PC = Cast<ARevolverPlayerController>(Character->GetController()))
		{
			Character->DisableInput(PC); 
		}
		EnableAbilityOrientation(); 
	}
}

// we dont call this directly, this will be called in the base chorded ability so any previously bound 
void UChargeAbility::MontageStarted()
{
	Super::MontageStarted();
	
	UAbilityTask_WaitGameplayEvent*  MontageTriggeredEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent
	(this,MontageTriggeredTag,
		nullptr, false,
		true
		); 
	MontageTriggeredEvent->EventReceived.AddDynamic(this, &UChargeAbility::MontageTriggerEvent); 
	MontageTriggeredEvent->ReadyForActivation();
	
	UAbilityTask_WaitGameplayEvent* HitScanStartEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent
	(
		this,HitScanStartTag, 
		nullptr,false,
		true
		);
	HitScanStartEvent->EventReceived.AddDynamic(this, &UChargeAbility::HitScanStartEvent);
	HitScanStartEvent->ReadyForActivation();
	
	UAbilityTask_WaitGameplayEvent* HitScanEndedEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent
	(
		this, HitScanEndTag,
		nullptr, false,
		true
		); 
	HitScanEndedEvent->EventReceived.AddDynamic(this, &UChargeAbility::HitScanEndEvent);
	HitScanEndedEvent->ReadyForActivation();
	
	
}

void UChargeAbility::OnMontageCancelled()
{
	if (ARevolverPlayerController* PC = Cast<ARevolverPlayerController>(GetCharacterFromActorInfo()->GetController()))
	{
		GetCharacterFromActorInfo()->EnableInput(PC);	
	}
	EndAbility(CurrentSpecHandle, CurrentActorInfo,CurrentActivationInfo,true, true); 
	Super::OnMontageCancelled(); 
}

void UChargeAbility::OnMontageCompleted()
{
	if (ARevolverPlayerController* PC = Cast<ARevolverPlayerController>(GetCharacterFromActorInfo()->GetController()))
	{
		GetCharacterFromActorInfo()->EnableInput(PC);	
	}
	EndAbility(CurrentSpecHandle, CurrentActorInfo,CurrentActivationInfo,true, false); 
	Super::OnMontageCompleted();
}

void UChargeAbility::OnMontageInterupted()
{
	if (ARevolverPlayerController* PC = Cast<ARevolverPlayerController>(GetCharacterFromActorInfo()->GetController()))
	{
		GetCharacterFromActorInfo()->EnableInput(PC);	
	}
	EndAbility(CurrentSpecHandle, CurrentActorInfo,CurrentActivationInfo,true, true); 
	Super::OnMontageInterupted(); 
}

void UChargeAbility::MontageTriggerEvent(FGameplayEventData Payload)
{
	ChargeForce(); 
}

void UChargeAbility::HitScanStartEvent(FGameplayEventData Payload)
{
	HitActors.Empty();
	
	if (GetWorld()->GetTimerManager().IsTimerActive(HitScanTimer))
	{
		GetWorld()->GetTimerManager().ClearTimer(HitScanTimer);
	}
	GetWorld()->GetTimerManager().SetTimer(HitScanTimer, this, &UChargeAbility::HitScan, HitRate, true);
	
}

void UChargeAbility::HitScanEndEvent(FGameplayEventData Payload)
{
	GetWorld()->GetTimerManager().ClearTimer(HitScanTimer);
}

void UChargeAbility::HitScan()
{
	FVector StartLocation = GetAvatarActorFromActorInfo()->GetActorLocation(); 
	FVector EndLocation = StartLocation + ChargeDirection;
	
	TArray<AActor*> ActorsToIgnore; ActorsToIgnore.Add(GetAvatarActorFromActorInfo()); 
	
	
	TArray<FHitResult> HitResults;
	
	UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(), StartLocation, EndLocation,HitRadius,ObjectTypes,false,ActorsToIgnore,EDrawDebugTrace::ForDuration,HitResults,true); 
	
	AbilityHitScan(HitResults); 
}

void UChargeAbility::ChargeForce()
{
	ApplyCameraEffect(); 
	
	if (UCapsuleComponent* Collision = GetCharacterFromActorInfo()->GetCapsuleComponent())
	{
		Collision->SetCollisionObjectType(ECC_Visibility); 
	}
	
	ChargeDirection = GetAvatarActorFromActorInfo()->GetActorForwardVector().GetSafeNormal()* DirectionMagnitude; 
	
	CommitAbilityCost(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo); 
	
	
	UAbilityTask_ApplyRootMotionConstantForce* RootMotionTask = UAbilityTask_ApplyRootMotionConstantForce::ApplyRootMotionConstantForce(
		this, FName(""),
		ChargeDirection, ChargeStrength,
		ChargeDuration, false,
		nullptr, ERootMotionFinishVelocityMode::SetVelocity,
		FVector(), 0.0f,
		false);
	
	RootMotionTask->OnFinish.AddDynamic(this, &UChargeAbility::OnChargeFinish); 
	RootMotionTask->ReadyForActivation(); 
}

void UChargeAbility::OnChargeFinish()
{
	RemoveCameraEffect();
	if (UCapsuleComponent* Collision = GetCharacterFromActorInfo()->GetCapsuleComponent())
	{
		Collision->SetCollisionObjectType(ECC_Pawn); 
	}
	// will fix this part to include the fixing of the movement
	
	DisableAbilityOrientation(); 
	
	CommitAbilityCooldown(CurrentSpecHandle, CurrentActorInfo,CurrentActivationInfo, true); 
	
}

