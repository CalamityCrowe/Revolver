// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/RevolverPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GAS/EnhancedAbilitySystemComponent.h"
#include "Player/RevolverPlayerState.h"
#include "UI/HUD/RevolverPlayerHUD.h"

// CommonUISetup
#include "MenuFiles/HUDS/BasePauseHUD.h"


ARevolverPlayerController::ARevolverPlayerController()
{
}

void ARevolverPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (ABasePauseHUD* PauseHUD = Cast<ABasePauseHUD>(GetHUD()))
	{
		PauseHUDRef = PauseHUD;
	}
}

void ARevolverPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
		{
			Subsystem->AddMappingContext(PauseMappingContext,0 ); 
		}
	}
	
	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EIC->BindAction(IA_Pause, ETriggerEvent::Started, this, &ARevolverPlayerController::ShowPauseHUD); 
	}
	
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

void ARevolverPlayerController::ShowPauseHUD(const FInputActionValue& Value)
{
	if (PauseHUDRef)
	{
		PauseHUDRef->ShowPauseMenu(); 
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
