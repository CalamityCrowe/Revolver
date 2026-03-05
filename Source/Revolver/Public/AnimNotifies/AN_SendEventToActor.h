// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "GameplayTagContainer.h"
#include "AN_SendEventToActor.generated.h"

/**
 * 
 */
UCLASS()
class REVOLVER_API UAN_SendEventToActor : public UAnimNotify
{
	GENERATED_BODY()
public: 
	UAN_SendEventToActor(); 
	
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	
	virtual FString GetNotifyName_Implementation() const override;
protected: 
	
	UPROPERTY(EditAnywhere, Category = "GAS")
	FGameplayTag EventToSend; 
	
};
