// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/RevolverPlayerController.h"

#include "GAS/EnhancedAbilitySystemComponent.h"
#include "Player/RevolverPlayerState.h"
#include "UI/HUD/RevolverPlayerHUD.h"

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

void ARevolverPlayerController::CreateHUD()
{
	if (!PlayerHudClass)
	{
		UE_LOG(LogTemp,Warning,TEXT("HUD class is not set")); 
		return;
	}
	if (PlayerHUDRef)
	{
		UE_LOG(LogTemp, Warning, TEXT("HUD widget already set"))
		return;		
	}
	if (!GetRevolverPlayerState())
	{
		UE_LOG(LogTemp, Error, TEXT("Player State is not a revolver player state"))
		return;
	}
	
	PlayerHUDRef = CreateWidget<URevolverPlayerHUD>(GetWorld(), PlayerHudClass); 
	PlayerHUDRef->AddToViewport(); 
}

void ARevolverPlayerController::RemoveHUD()
{
	if (PlayerHUDRef)
	{
		PlayerHUDRef->RemoveFromParent();
	}
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
	

	
}
