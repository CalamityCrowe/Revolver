// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Spawn/BaseEnemySpawner.h"

#include "Components/BoxComponent.h"


ABaseEnemySpawner::ABaseEnemySpawner()
{
	PrimaryActorTick.bCanEverTick = false;
	
	BoxSpawner = CreateDefaultSubobject<UBoxComponent>("Spawn Area"); 
	RootComponent = BoxSpawner;
	
	BoxSpawner->SetBoxExtent(FVector(100.f,100.f,50.f),true); 
	
}

bool ABaseEnemySpawner::SpawnEnemy()
{
	if (EnemyQueue.IsValidIndex(0))
	{
			
	}
	else
	{
		return false;
	}
	
}

void ABaseEnemySpawner::AddEnemyToQueue(TSubclassOf<AEnemyCharacter> EnemyRef)
{
	
}

void ABaseEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(SpawnTimerHandle,this, &ABaseEnemySpawner::AttemptToSpawn, SpawnTimer, true, 2.f); 
}

void ABaseEnemySpawner::AttemptToSpawn()
{
	SpawnEnemy(); 
}

void ABaseEnemySpawner::OnEnemyDefeated()
{
	// need a degate for this
	if (OnEnemyDefeatedDelegate.IsBound())
	{
		OnEnemyDefeatedDelegate.Broadcast(); 
	}
}



