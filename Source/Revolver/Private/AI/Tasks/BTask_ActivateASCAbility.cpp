// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTask_ActivateASCAbility.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "AIController.h"
#include "Characters/Enemies/EnemyCharacter.h"

UBTask_ActivateASCAbility::UBTask_ActivateASCAbility()
{
}

EBTNodeResult::Type UBTask_ActivateASCAbility::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) // might look at node memory specifically as that seems to be the way to pass data around in the task instead
{
	EnemyRef = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn()); // we grab a copy of the owning enemy here to store as a reference
	if (EnemyRef && AbilityToActivate) // we first check if the enemy ref was valid and there is a valid ability to activate
	{
		if (UAbilitySystemComponent* ASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(EnemyRef)) // we check if there is a valid ASC as well so we can activate the ability on it
		{
			if (ASC->TryActivateAbilityByClass(AbilityToActivate,true)) // next we try to activate the ability and make sure none of the blocking conditions are going to stop it(blocking tags on the ability itself)
			{
				EnemyRef->OnAttackEnded.AddDynamic(this,&UBTask_ActivateASCAbility::OnAttackEnded);  // we bind the attack on finished delegate here
				OwnerCompRef = &OwnerComp; // store a copy of the owner component, to be passed into the latent ability
				return EBTNodeResult::InProgress;  // lastly we return in progress, so it doesn't move onto the next task
			} 
		} 
	}
	// if any of the casting results return as a fail or the ability can't activate, we just tell it to return failed
	return EBTNodeResult::Failed;
}

EBTNodeResult::Type UBTask_ActivateASCAbility::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (EnemyRef)
	{
		EnemyRef->OnAttackEnded.RemoveDynamic(this, &UBTask_ActivateASCAbility::OnAttackEnded); 
	}
	return Super::AbortTask(OwnerComp, NodeMemory);
}

void UBTask_ActivateASCAbility::OnAttackEnded()
{
	if (EnemyRef)
	{
		EnemyRef->OnAttackEnded.RemoveDynamic(this,&UBTask_ActivateASCAbility::OnAttackEnded); 
	}
	FinishLatentTask(*OwnerCompRef, EBTNodeResult::Succeeded); 
}


