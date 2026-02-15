// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/RevolverPlayerController.h"

#include "GAS/EnhancedAbilitySystemComponent.h"
#include "Player/RevolverPlayerState.h"

ARevolverPlayerController::ARevolverPlayerController()
{
}

ARevolverPlayerState* ARevolverPlayerController::GetRevolverPlayerState() const
{
	return CastChecked<ARevolverPlayerState>(PlayerState, ECastCheckedType::NullAllowed); 
}

UEnhancedAbilitySystemComponent* ARevolverPlayerController::GetEnhancedAbilitySystemComponent() const
{
	if (ARevolverPlayerState* PS = GetRevolverPlayerState())
	{
		return CastChecked<UEnhancedAbilitySystemComponent>(PS->GetAbilitySystemComponent()); 
	}
	return nullptr;
}

void ARevolverPlayerController::PostProcessInput(const float DeltaTime, const bool bGamePaused)
{
	if (UEnhancedAbilitySystemComponent* ASC = GetEnhancedAbilitySystemComponent())
	{
		ASC->PrccessAbilityInput(DeltaTime, bGamePaused);
	}
	Super::PostProcessInput(DeltaTime, bGamePaused);
}

void ARevolverPlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	
	// create hud
}
