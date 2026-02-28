// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/RevolverPlayerCharacter.h"

// engine 
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

//plugin
#include "Components/WeaponManagerComponent.h"
#include "EditorFiles/EnhancedGameplayTags.h"
#include "GAS/EnhancedAbilitySet.h"
#include "GAS/EnhancedAbilitySystemComponent.h"
#include "GAS/Attributes/EnhancedAttributeSet.h"
#include "Input/GASEnhancedInputComponent.h"
#include "Kismet/KismetMathLibrary.h"
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
	
}

void ARevolverPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (ARevolverPlayerController* PC = Cast<ARevolverPlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputContext, 0); 
		}
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
	
	
}

void ARevolverPlayerCharacter::InputAbilityInputTagPressed(FGameplayTag InputTag)
{
	ASC->AbilityInputTagPressed(InputTag); 
}

void ARevolverPlayerCharacter::InputAbilityInputTagReleased(FGameplayTag InputTag)
{
	ASC->AbilityInputTagReleased(InputTag);
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
	FVector2D Axis = Value.Get<FVector2D>();
	AddControllerYawInput(Axis.X);
	AddControllerPitchInput(Axis.Y);
}

void ARevolverPlayerCharacter::EquipRightHand(const FInputActionValue& Value)
{
	FGameplayEventData PayLoad;
	PayLoad.TargetTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Weapon.Melee"))); 
	ASC->HandleGameplayEvent(FGameplayTag::RequestGameplayTag(FName("Event.Abilities.EquipWeapon")),&PayLoad); 
}

