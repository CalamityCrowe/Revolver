// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/RevolverPlayerCharacter.h"

// engine 
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"

//plugin

#include "EditorFiles/EnhancedGameplayTags.h"
#include "GAS/EnhancedAbilitySet.h"
#include "GAS/EnhancedAbilitySystemComponent.h"
#include "GAS/Attributes/RevolverAttributeSet.h"
#include "Input/GASEnhancedInputComponent.h"

// revolver
#include "Components/AbilityCameraManagerComponent.h"
#include "Components/TargetLockOnComponent.h"
#include "Components/WeaponManagerComponent.h"
#include "Player/RevolverPlayerController.h"
#include "Player/RevolverPlayerState.h"



ARevolverPlayerCharacter::ARevolverPlayerCharacter()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->SetWorldLocation(FVector(0.0f,0.0f,8.492f));
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true; 
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom,CameraBoom->SocketName); 
	
	bUseControllerRotationYaw = false; 
	
	WeaponManagerComponent = CreateDefaultSubobject<UWeaponManagerComponent>(TEXT("AC_WeaponManager")); 
	AbilityCameraManagerComponent = CreateDefaultSubobject<UAbilityCameraManagerComponent>(TEXT("Ability Camera Manager")); 
	TargetLockOnComponent = CreateDefaultSubobject<UTargetLockOnComponent>(TEXT("AC_TargetLockOnComponent")); 
}




void ARevolverPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (const ARevolverPlayerController* PC = Cast<ARevolverPlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputContext, 0); 
		}
	}
	
	if (AbilityCameraManagerComponent)
	{
		AbilityCameraManagerComponent->InitializeCameraSetup(); 
	}
	
}


void ARevolverPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	UGASEnhancedInputComponent* GASInputComponent = Cast<UGASEnhancedInputComponent>(PlayerInputComponent); 
	check(GASInputComponent);
	
	const FEnhancedGameplayTags& GameplayTags = FEnhancedGameplayTags::Get(); 
	TArray<uint32> BindHandles; 
	GASInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::InputAbilityInputTagPressed, & ThisClass::InputAbilityInputTagReleased, BindHandles); 
	
	GASInputComponent->BindNativeAction(InputConfig, GameplayTags.Input_Move, ETriggerEvent::Triggered,this,  &ThisClass::Move);
	GASInputComponent->BindNativeAction(InputConfig, GameplayTags.Input_Aim, ETriggerEvent::Triggered, this, &ThisClass::Look); 

	GASInputComponent->BindNativeAction(InputConfig, GameplayTags.Input_Aim, ETriggerEvent::Started, this, &ThisClass::SwitchTarget); 
	GASInputComponent->BindNativeAction(InputConfig, GameplayTags.Input_LockOn, ETriggerEvent::Started, this, &ThisClass::TriggerLockOn); 
	// for the likes of needing to send specific event data, I.E equipping weapons via input, then this is how we handle that 
	GASInputComponent->BindNativeAction(InputConfig, GameplayTags.Input_EquipSword, ETriggerEvent::Started, this, &ThisClass::EquipRightHand); 
	
}

void ARevolverPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	ARevolverPlayerState* PS = Cast<ARevolverPlayerState>(GetPlayerState()); 
	check (PS);
	
	ASC = Cast<UEnhancedAbilitySystemComponent>(PS->GetAbilitySystemComponent()); 
	ASC->InitAbilityActorInfo(PS,this); 
	
	AttributeSet = PS->GetAttributeSet(); 
	
	
	if (AbilitySet)
	{
		AbilitySet->GiveToAbilitySystem(ASC.Get(), &GrantedHandles,this); 
	}
	
	// we would create the player HUD here if we have one
	if (ARevolverPlayerController* PC = Cast<ARevolverPlayerController>(GetController()))
	{
		PC->CreateHUD(); 
	}
	
	SendAbilitiesChangedEvent(); 
}

void ARevolverPlayerCharacter::SendAbilitiesChangedEvent()
{
	FGameplayEventData EventData;
	EventData.EventTag = FGameplayTag::RequestGameplayTag(FName("Event.Abilities.Changed")); 
	EventData.Instigator = this; 
	EventData.Target = this; 
	
	SendGameplayEventToSelf(EventData);
}

void ARevolverPlayerCharacter::InputAbilityInputTagPressed(FGameplayTag InputTag)
{
	ASC->AbilityInputTagPressed(InputTag); 
}

void ARevolverPlayerCharacter::InputAbilityInputTagReleased(FGameplayTag InputTag)
{
	ASC->AbilityInputTagReleased(InputTag);
}

void ARevolverPlayerCharacter::Die()
{
	Super::Die();
	if (ARevolverPlayerController* PC = Cast<ARevolverPlayerController>(GetController()))
	DisableInput(PC); 
}

void ARevolverPlayerCharacter::FinishDying()
{
	Super::FinishDying();
}

void ARevolverPlayerCharacter::Move(const FInputActionValue& Value)
{ 
	// we might need to block this with an if condition for when an ability is active
	FVector2D MovementAxis = Value.Get<FVector2D>(); 
	FRotator ControlRotation = GetControlRotation(); 
	FVector XWorldVector = UKismetMathLibrary::GetRightVector(FRotator(0,ControlRotation.Yaw, ControlRotation.Roll)); 
	FVector YWorldVector = UKismetMathLibrary::GetForwardVector(FRotator(0,ControlRotation.Yaw, 0));
	AddMovementInput(XWorldVector, MovementAxis.X, false);
	AddMovementInput(YWorldVector, MovementAxis.Y, false);
}

void ARevolverPlayerCharacter::Look(const FInputActionValue& Value)
{
	// we might need to block this with an if condition 
	const FVector2D Axis = Value.Get<FVector2D>();
	
	AddControllerYawInput(Axis.X);
	AddControllerPitchInput(Axis.Y);
}

void ARevolverPlayerCharacter::EquipRightHand(const FInputActionValue& Value)
{
	FGameplayEventData PayLoad;
	PayLoad.TargetTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Weapon.Melee"))); 
	ASC->HandleGameplayEvent(FGameplayTag::RequestGameplayTag(FName("Event.Abilities.EquipWeapon")),&PayLoad); 
}

void ARevolverPlayerCharacter::TriggerLockOn(const FInputActionValue& Value)
{
	if(TargetLockOnComponent)
	{
		GEngine->AddOnScreenDebugMessage(-1,1,FColor::Red,"TOGGLED LOCK ON"); 
		TargetLockOnComponent->ToggleLockOn(); // this will basically flip-flop between the locked on states depending on if the character is locked on or not
	}
}

void ARevolverPlayerCharacter::SwitchTarget(const FInputActionValue& Value)
{
	const FVector2D Axis = Value.Get<FVector2D>();
	// we only really want to run this if the player is locked onto something at this point
	if (TargetLockOnComponent->IsLockedOn())
	{
		TargetLockOnComponent->SwitchTarget(Axis.X); 
	}
	
}


