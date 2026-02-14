// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"

class UInteractableWidget;
class UWidgetComponent;
DECLARE_DELEGATE_OneParam(FOnInteractionPressOngoing, float); 


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class INTERACTIONSYSTEM_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInteractionComponent();

	void Interact(); 
	
	void ResetInteractionProgress(); 
	
	FOnInteractionPressOngoing InteractionPressOngoing;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	void InteractBegin(); 
	
	void RenderInteractionWidget(); 
	
	void ActivateInteractAction(); 
	
	void InteractionOngoing(float ElapsedTime); 
	
private: 
	
	TArray<TWeakObjectPtr<AActor>> InteractableActors; 
	
	UPROPERTY()
	TObjectPtr<ACharacter> CharacterRef;
	
	UFUNCTION()
	void OnInteractableOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnInteractableEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	AActor* GetActiveInteractable() const; 
};
