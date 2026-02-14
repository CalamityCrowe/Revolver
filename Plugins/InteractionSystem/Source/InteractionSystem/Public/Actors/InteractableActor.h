// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractableInterface.h"
#include "InteractableActor.generated.h"

UCLASS()
class INTERACTIONSYSTEM_API AInteractableActor : public AActor, public IInteractableInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInteractableActor();
	
	virtual void Interact_Implementation(AActor* InteractingActor);
	
	virtual EInteractionType GetInteractionType() const{return InteractionType;};

	virtual float GetHoldDuration_Implementation() const {return HoldDuration;};

	FString GetInteractionTypeName() const {return InteractionMessage; };

	virtual UAnimMontage* GetInteractionAnimMontage_Implementation() const override {return InteractionMontage;};
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private: 
	
	UPROPERTY(EditDefaultsOnly, Category="Interact", meta=(AllowPrivateAccess, ToolTip = "This is how we will define the type of interaction for the button pressing"))
	EInteractionType InteractionType;

	UPROPERTY(EditAnywhere, Category="Interact", meta=(AllowPrivateAccess,EditCondition= "InteractionType == EInteractionType::Hold",ClampMin = 0.01f, UIMin = 0.01f, ClampMax = 3.0f, UIMax = 3.0f, ToolTip = "This will be what we use to determine how long a button has to be held for the interaction to happen"))
	float HoldDuration;
	
	UPROPERTY(EditDefaultsOnly,Category = "Interact", meta = (AllowPrivateAcess, ToolTip = "The Message to be displayed on the UI when they are within range to onteract with the object") )
	FString InteractionMessage; 
	
	UPROPERTY(EditDefaultsOnly, Category = "Interact", meta = (AllowPrivateAccess = true, ToolTip = "This is the animation montage to be played if there is one for interacting with the object"))
	TObjectPtr<UAnimMontage> InteractionMontage;
};
