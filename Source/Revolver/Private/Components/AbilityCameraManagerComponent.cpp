// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/AbilityCameraManagerComponent.h"

#include "Abilities/Async/AbilityAsync_WaitGameplayTag.h"
#include "Characters/Player/RevolverPlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"

UAbilityCameraManagerComponent::UAbilityCameraManagerComponent()
{

	PrimaryComponentTick.bCanEverTick = false;

}

void UAbilityCameraManagerComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UAbilityCameraManagerComponent::IntializeCameraSetup()
{
	PlayerRef = Cast<ARevolverPlayerCharacter>(GetOwner());
	if (PlayerRef)
	{
		CameraBoomRef = PlayerRef->GetCameraBoom();
	}
	if (!IsValid(CameraBoomRef))
	{
		UE_LOG(LogTemp,Error,TEXT("CameraBoomRef is invalid"));
		return;
	}
	
UAbilityAsync_WaitGameplayTagAdded* Ability1TagAdded = UAbilityAsync_WaitGameplayTagAdded::WaitGameplayTagAddToActor
	(PlayerRef,FGameplayTag::RequestGameplayTag("GameplayEffect.Character.Ability1"),false);
	Ability1TagAdded->Added.AddDynamic(this,&UAbilityCameraManagerComponent::OnAbility1CameraLerp); 
	
	UAbilityAsync_WaitGameplayTagRemoved* Ability1TagRemoved = UAbilityAsync_WaitGameplayTagRemoved::WaitGameplayTagRemoveFromActor
	(PlayerRef, FGameplayTag::RequestGameplayTag("GameplayEffect.Character.Ability1"),false); 
	Ability1TagRemoved->Removed.AddDynamic(this,&UAbilityCameraManagerComponent::AbilityFinished);
}

void UAbilityCameraManagerComponent::OnAbility1CameraLerp()
{
	
}

void UAbilityCameraManagerComponent::AbilityFinished()
{
	StartArmLength = CameraBoomRef->TargetArmLength; 
	StartSocket = CameraBoomRef->SocketOffset; 
	
	TargetArmLength = DefaultArmLength;
	TargetSocket = DefaultSocket;
	
	if (GetWorld()->GetTimerManager().IsTimerActive(CameraLerpTimer))
	{
		GetWorld()->GetTimerManager().ClearTimer(CameraLerpTimer);
	}
	GetWorld()->GetTimerManager().SetTimer(CameraLerpTimer,this,&UAbilityCameraManagerComponent::LerpCamera, 0.1f, true);
}

void UAbilityCameraManagerComponent::LerpCamera()
{
	// I am needing to set this up
}



