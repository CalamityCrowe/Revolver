// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Characters/CharacterBase.h"
#include "GameplayTagContainer.h"
#include "GAS/EnhancedAbilitySet.h"
#include "RevolverPlayerCharacter.generated.h"

class UWeaponManagerComponent;
struct FAbilitySet_GrantedHandles;
class USpringArmComponent;
class UCameraComponent;

class UInputMappingContext;
class UEnhancedInputConfig; 
class UEnhancedAbilitySet;

UCLASS()
class REVOLVER_API ARevolverPlayerCharacter : public ACharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARevolverPlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual void PossessedBy(AController* NewController) override;
	
	void InputAbilityInputTagPressed(FGameplayTag InputTag);
	void InputAbilityInputTagReleased(FGameplayTag InputTag);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input System| Abilities")
	TObjectPtr<UEnhancedAbilitySet> AbilitySet; 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input System| Inputs")
	TObjectPtr<UEnhancedInputConfig>InputConfig; 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input System| Inputs")
	TObjectPtr<UInputMappingContext> InputContext;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components|Weapon Manager")
	TObjectPtr<UWeaponManagerComponent> WeaponManagerComponent; 
	
	
	FAbilitySet_GrantedHandles GrantedHandles; 
	
private: 
	UFUNCTION()
	void Move(const FInputActionValue& Value); 
	UFUNCTION()
	void Look(const FInputActionValue& Value);
	
	UFUNCTION() 
	void EquipRightHand(const FInputActionValue& Value); 
	
private: 
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess))
	TObjectPtr<UCameraComponent> Camera;
	UPROPERTY (EditDefaultsOnly, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess))
	TObjectPtr<USpringArmComponent> CameraBoom;
	
};
