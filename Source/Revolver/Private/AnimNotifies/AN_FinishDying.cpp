// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/AN_FinishDying.h"
#include "Characters/CharacterBase.h"

UAN_FinishDying::UAN_FinishDying()
{
	bShouldFireInEditor = false;
}

void UAN_FinishDying::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	if (ACharacterBase* Character = Cast<ACharacterBase>(MeshComp->GetOwner()))
	{
		Character->FinishDying(); 
	}
}

FString UAN_FinishDying::GetNotifyName_Implementation() const
{
	return FString::Printf(TEXT("Finish Dying"));
}
