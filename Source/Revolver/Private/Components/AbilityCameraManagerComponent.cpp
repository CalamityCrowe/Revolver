// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/AbilityCameraManagerComponent.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "Camera/CameraComponent.h"
#include "Characters/Player/RevolverPlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"

UAbilityCameraManagerComponent::UAbilityCameraManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAbilityCameraManagerComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UAbilityCameraManagerComponent::InitializeCameraSetup()
{
	PlayerRef = Cast<ARevolverPlayerCharacter>(GetOwner());
	if (PlayerRef)
	{
		CameraBoomRef = PlayerRef->GetCameraBoom();
		CameraRef = PlayerRef->GetCamera(); 
	}
	if (!IsValid(CameraBoomRef))
	{
		UE_LOG(LogTemp,Error,TEXT("CameraBoomRef is invalid"));
		return;
	}
	
	if (!CameraSetups.IsDataSet())
	{
		UE_LOG(LogTemp,Error,TEXT("Ability Camera Data has not been set"));
		return; 	
	}
	
	// we setup the camera transitions by binding an event on the addition or removal of tags to the ASC
	ASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(PlayerRef);
	if (ASC)
	{
		ASC->RegisterGameplayTagEvent(CameraSetups.FirstAbilityData->CameraTag, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &UAbilityCameraManagerComponent::OnTagChange); 
		ASC->RegisterGameplayTagEvent(CameraSetups.SecondAbilityData->CameraTag, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &UAbilityCameraManagerComponent::OnTagChange); 
		ASC->RegisterGameplayTagEvent(CameraSetups.ThirdAbilityData->CameraTag, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &UAbilityCameraManagerComponent::OnTagChange); 
		
	}
}

UAbilityCameraData* UAbilityCameraManagerComponent::FindDataForTag(const FGameplayTag& Tag)
{
	if (CameraSetups.FirstAbilityData->CameraTag == Tag)return CameraSetups.FirstAbilityData;
	if (CameraSetups.SecondAbilityData->CameraTag == Tag)return CameraSetups.SecondAbilityData;
	if (CameraSetups.ThirdAbilityData->CameraTag == Tag)return CameraSetups.ThirdAbilityData;
	if (CameraSetups.FourthAbilityData->CameraTag == Tag)return CameraSetups.FourthAbilityData;
	return nullptr; 
}

void UAbilityCameraManagerComponent::OnTagChange(FGameplayTag GameplayTag, int32 NewCount)
{
	if (NewCount > 0)
	{
		ActiveAbilityTag = GameplayTag;

		UAbilityCameraData* CameraData = FindDataForTag(GameplayTag);
		if (!CameraData)return; 
		
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green, "I ADD"); 
		
		SetStartingValues(); 
		TargetSocket = CameraData->AbilitySocketOffset;
		TargetArmLength = CameraData->AbilityTargetArm;
		TargetFOV = CameraData->AbilityFOV; 
		TransitionTime = CameraData->CameraTransition; 
		ResetCameraLerp(); 
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, "I REMOVE"); 
		if (ActiveAbilityTag == GameplayTag)
		{
			
			ActiveAbilityTag = FGameplayTag::EmptyTag; 
			AbilityFinished(); 
		}
	}
}

// we essentially want to go back to the previous camera state so it can return to normal 
void UAbilityCameraManagerComponent::AbilityFinished()
{
	SetStartingValues(); 
	TargetSocket = CameraSetups.DefaultCameraSetup->AbilitySocketOffset;
	TargetArmLength = CameraSetups.DefaultCameraSetup->AbilityTargetArm;
	TargetFOV = CameraSetups.DefaultCameraSetup->AbilityFOV; 
	TransitionTime = CameraSetups.DefaultCameraSetup->CameraTransition;
	ResetCameraLerp();
}

void UAbilityCameraManagerComponent::LerpCamera()
{
	ElapsedTime += TimerStep; // this is the value that will be assigned to lop the timer handle
	
	float Alpha = FMath::Clamp(ElapsedTime/TransitionTime, 0.0f , 1.0f); 
	if (BlendCurve)
	{
		Alpha = BlendCurve->GetFloatValue(Alpha); 
	}
	
	// we then lerp the camera properties to give the correct feel for the ability
	CameraBoomRef->SocketOffset = FMath::Lerp(StartSocket,TargetSocket,Alpha);
	CameraBoomRef->TargetArmLength = FMath::Lerp(StartArmLength,TargetArmLength,Alpha);
	CameraRef->FieldOfView = FMath::Lerp(StartFOV,TargetFOV,Alpha);
	
	if (ElapsedTime >=  TransitionTime)
	{
		GetWorld()->GetTimerManager().ClearTimer(CameraLerpTimer);
	}
}

void UAbilityCameraManagerComponent::SetStartingValues()
{
	ElapsedTime = 0;
	StartSocket = CameraBoomRef->SocketOffset; 
	StartArmLength = CameraBoomRef->TargetArmLength;
	StartFOV = CameraRef->FieldOfView;
}
void UAbilityCameraManagerComponent::ResetCameraLerp()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(CameraLerpTimer))
	{
		GetWorld()->GetTimerManager().ClearTimer(CameraLerpTimer);
	}
	GetWorld()->GetTimerManager().SetTimer(CameraLerpTimer,this,&UAbilityCameraManagerComponent::LerpCamera, TimerStep, true);
}

