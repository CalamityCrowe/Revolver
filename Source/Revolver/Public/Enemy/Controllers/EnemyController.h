// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "EnemyController.generated.h"


UCLASS()
class REVOLVER_API AEnemyController : public AAIController
{
	GENERATED_BODY()

public:
	AEnemyController();

protected:
	virtual void OnPossess(APawn* PossessPawn) override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Blackboard|Trees")
	TObjectPtr<UBehaviorTree> BehaviourTree;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Blackboard|Keys")
	FName TargetKeyName; 
	
};
