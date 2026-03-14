
#include "Enemy/Controllers/EnemyController.h"


AEnemyController::AEnemyController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemyController::BeginPlay()
{
	Super::BeginPlay();
	if (BehaviourTree)
	{
		RunBehaviorTree(BehaviourTree); 
	}
}


