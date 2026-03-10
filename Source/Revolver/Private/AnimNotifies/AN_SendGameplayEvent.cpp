// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/AN_SendGameplayEvent.h"

#include "AbilitySystemBlueprintLibrary.h"

void UAN_SendGameplayEvent::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(MeshComp->GetOwner(), EventTag,FGameplayEventData()); 
}

FString UAN_SendGameplayEvent::GetNotifyName_Implementation() const
{
	if (EventTag.IsValid())
		return FString::Printf(TEXT("Send Gameplay Event: %s"), *EventTag.ToString());
	
	return FString("Send Gameplay Event: no tag set");
}
