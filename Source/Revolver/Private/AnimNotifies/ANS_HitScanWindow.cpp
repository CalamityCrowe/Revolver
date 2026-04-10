// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/ANS_HitScanWindow.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GAS/EnhancedAbilitySystemComponent.h"

void UANS_HitScanWindow::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	
	FGameplayEventData Payload;
	if (bUseSkeletonForCollisions)
	{
		USocketCollisionParamsObject* ParamsObj = NewObject<USocketCollisionParamsObject>();
		ParamsObj->Params.SocketName = SocketName;
		ParamsObj->Params.CollisionRadius = CollisionRadius;
		
		Payload.OptionalObject = ParamsObj;
	}
	
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(MeshComp->GetOwner(),HitStartTag,Payload); 
}

void UANS_HitScanWindow::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(MeshComp->GetOwner(),HitEndTag,FGameplayEventData()); 
}

FString UANS_HitScanWindow::GetNotifyName_Implementation() const
{
	return FString::Printf(TEXT("Hit Scan Window"));
}
