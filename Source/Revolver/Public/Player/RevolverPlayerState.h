// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "RevolverPlayerState.generated.h"

class UEnhancedAbilitySystemComponent;
class UEnhancedAttributeSet;
/**
 * 
 */
UCLASS()
class REVOLVER_API ARevolverPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
public: 
	ARevolverPlayerState(); 
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	virtual UEnhancedAttributeSet* GetAttributeSet() const; 
	
protected:
	
	UPROPERTY()
	TObjectPtr<UEnhancedAbilitySystemComponent> ASC;

	UPROPERTY()
	TObjectPtr<UEnhancedAttributeSet> AttributeSet;
	
};
