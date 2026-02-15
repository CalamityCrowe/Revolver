// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RevolverPlayerController.generated.h"

class UEnhancedAbilitySystemComponent;
class ARevolverPlayerState;
/**
 * 
 */
UCLASS()
class REVOLVER_API ARevolverPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ARevolverPlayerController(); 
	
	UFUNCTION(BlueprintCallable, Category = "Input System|Player State")
	ARevolverPlayerState* GetRevolverPlayerState() const; 
	
	UFUNCTION(BlueprintCallable, Category = "Input System|Ability System")
	UEnhancedAbilitySystemComponent* GetEnhancedAbilitySystemComponent() const;
	
	
protected:
	virtual void PostProcessInput(const float DeltaTime, const bool bGamePaused) override;
	
	virtual void OnRep_PlayerState() override;
	
	
private: 	
};
