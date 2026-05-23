// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTask_ActivateASCAbility.generated.h"

class AEnemyCharacter;
class UGameplayAbility;
/**
 * 
 */
UCLASS()
class REVOLVER_API UBTask_ActivateASCAbility : public UBTTaskNode
{
	GENERATED_BODY()
public: 
	UBTask_ActivateASCAbility(); 
	
protected: 
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	UFUNCTION()
	virtual void OnAttackEnded(); 
	
	
private: 
	
	UPROPERTY()
	UBehaviorTreeComponent* OwnerCompRef; 	
	UPROPERTY()
	AEnemyCharacter* EnemyRef; 
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess), Category = "Ability")
	TSubclassOf<UGameplayAbility> AbilityToActivate; 
	
};
