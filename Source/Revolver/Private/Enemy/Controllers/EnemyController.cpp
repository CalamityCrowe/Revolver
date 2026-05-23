
#include "Enemy/Controllers/EnemyController.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"


AEnemyController::AEnemyController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemyController::StopBehaviourTree()
{
	if (UBehaviorTreeComponent* BTComp = Cast<UBehaviorTreeComponent>(BrainComponent))
	{
#if WITH_EDITOR
		GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Green,"WE ARE STOPPING THE TREE"); 
#endif
		BTComp->StopTree();
		
	} 
}


void AEnemyController::OnPossess(APawn* PossessPawn)
{
	Super::OnPossess(PossessPawn);
	// we check if the behaviour tree is valid when possessing
	if (BehaviourTree)
	{
		// we add a slight delay here to make sure the player is actually ready for them to have as a target
		// we do this by creating a lambda as this will be a one time call and we dont need to reset this
		FTimerHandle InitializeTreeHandle; 
		GetWorldTimerManager().SetTimer(InitializeTreeHandle,[this]()
		{
			// we tell it to run the behaviour tree to have the enemies be alive
			RunBehaviorTree(BehaviourTree);
			// we assign the value of a blackboard key "TargetKeyName" to be the player. We could use a location if we wanted to do a 
			// general idea for where they should be moving to, I.E 
			Blackboard->SetValueAsObject(TargetKeyName,UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));  
		},0.2f,false); 
	}
}




