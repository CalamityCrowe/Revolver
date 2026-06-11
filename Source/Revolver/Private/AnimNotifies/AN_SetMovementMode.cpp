// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/AN_SetMovementMode.h"

#include "Characters/CharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"

UAN_SetMovementMode::UAN_SetMovementMode()
{
}

void UAN_SetMovementMode::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	if (ACharacterBase* Character = Cast<ACharacterBase>(MeshComp->GetOwner()))
	{
		if (UCharacterMovementComponent* MovementComponent = Character->GetCharacterMovement())
		{
			MovementComponent->SetMovementMode(MovementMode); 
		}
	}
}

FString UAN_SetMovementMode::GetNotifyName_Implementation() const
{
	return Super::GetNotifyName_Implementation();
}
