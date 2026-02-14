// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/InteractableActor.h"

AInteractableActor::AInteractableActor()
{
	PrimaryActorTick.bCanEverTick = false;
}


void AInteractableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AInteractableActor::Interact_Implementation(AActor* InteractingActor)
{
	IInteractableInterface::Interact_Implementation(InteractingActor);
#if WITH_EDITOR
	// print a message saying what actor is getting interacted with 
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, FString::Printf(TEXT("Interacting with: %s (%s)"), *GetName(), *GetClass()->GetName()));
#endif
}



