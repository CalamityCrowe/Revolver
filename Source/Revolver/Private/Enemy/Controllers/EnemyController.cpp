
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
	
	
	if (BehaviourTree)
	{
		FTimerHandle InitializeTreeHandle; 
		GetWorldTimerManager().SetTimer(InitializeTreeHandle,[this]()
		{
			RunBehaviorTree(BehaviourTree);
			Blackboard->SetValueAsObject(TargetKeyName,UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)); 
		},0.2f,false); 
	}
}




