// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AN_FinishDying.generated.h"

/**
 * 
 */
UCLASS(meta = (DisplayName = "Finish Dying"))
class REVOLVER_API UAN_FinishDying : public UAnimNotify
{
	GENERATED_BODY()
public: 
	UAN_FinishDying();
	
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	
	virtual FString GetNotifyName_Implementation() const override;
};
