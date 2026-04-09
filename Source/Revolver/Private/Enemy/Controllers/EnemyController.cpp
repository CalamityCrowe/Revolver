
#include "Enemy/Controllers/EnemyController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"


AEnemyController::AEnemyController()
{
	PrimaryActorTick.bCanEverTick = true;
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
			UObject* Target = Cast<UObject>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)); 
			Blackboard->SetValueAsObject(TargetKeyName, Target); 
		},0.2f,false); 
	}
}


