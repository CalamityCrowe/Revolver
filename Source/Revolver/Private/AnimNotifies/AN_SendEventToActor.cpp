// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/AN_SendEventToActor.h"

#include "AbilitySystemBlueprintLibrary.h"

UAN_SendEventToActor::UAN_SendEventToActor()
{
	bShouldFireInEditor = false;
}

void UAN_SendEventToActor::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(MeshComp->GetOwner(),EventToSend, FGameplayEventData()); 
}

FString UAN_SendEventToActor::GetNotifyName_Implementation() const
{
	return FString("Sent Event Notify"); 
}
