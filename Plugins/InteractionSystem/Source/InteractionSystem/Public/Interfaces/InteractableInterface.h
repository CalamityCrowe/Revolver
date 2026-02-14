// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractableInterface.generated.h"
UENUM()
enum class EInteractionType:uint8
{
	Press UMETA(DisplayName = "Press"), 
	Hold UMETA(DisplayName = "Hold"), 
	None UMETA (Hidden)
};

// This class does not need to be modified.
UINTERFACE()
class UInteractableInterface : public UInterface
{
	GENERATED_BODY()
};


class INTERACTIONSYSTEM_API IInteractableInterface
{
	GENERATED_BODY()
public: 
	UFUNCTION(BlueprintNativeEvent)
	void Interact(AActor* InteractingActor);
	
	UFUNCTION(BlueprintNativeEvent)
	EInteractionType GetInteractionType()const ;
	
	UFUNCTION(BlueprintNativeEvent)
	float GetHoldDuration() const; 
	
	UFUNCTION(BlueprintNativeEvent)
	FString GetInteractionMessage() const; 
	
	UFUNCTION(BlueprintNativeEvent)
	UAnimMontage* GetInteractionAnimMontage()const ;
};
