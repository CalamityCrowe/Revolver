// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RevolverPlayerController.generated.h"

class ABasePauseHUD;
class UInputAction;
class UInputMappingContext;
class UEnhancedAbilitySystemComponent;
class ARevolverPlayerState;
class URevolverPlayerHUD; 
/**
 * 
 */
UCLASS()
class REVOLVER_API ARevolverPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ARevolverPlayerController(); 
	
	virtual void BeginPlay() override;
	
	virtual void SetupInputComponent() override;
	
	UFUNCTION(BlueprintCallable, Category = "Input System|Player State")
	ARevolverPlayerState* GetRevolverPlayerState() const; 
	
	UFUNCTION(BlueprintCallable, Category = "Input System|Ability System")
	UEnhancedAbilitySystemComponent* GetEnhancedAbilitySystemComponent() const;
	
	void CreateHUD(); 
	
	void RemoveHUD();
	
	UFUNCTION()
	void ShowPauseHUD(const FInputActionValue& Value); 
	
protected:
	virtual void PostProcessInput(const float DeltaTime, const bool bGamePaused) override;
	
	virtual void OnRep_PlayerState() override;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<URevolverPlayerHUD> PlayerHudClass; 
	
	UPROPERTY()
	URevolverPlayerHUD* PlayerHUDRef;
	
	UPROPERTY(EditDefaultsOnly, Category = "Inputs")
	TObjectPtr<UInputMappingContext> PauseMappingContext; 
	UPROPERTY(EditDefaultsOnly, Category = "Inputs")
	TObjectPtr<UInputAction> IA_Pause; 
	
	ABasePauseHUD* PauseHUDRef; 
	
private: 	
};
