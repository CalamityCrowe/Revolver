// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Spawn/WaveManager.h"

#include "Enemy/WaveData.h"
#include "Enemy/Spawn/BaseEnemySpawner.h"
#include "Characters/Enemies/EnemyCharacter.h"
#include "Kismet/GameplayStatics.h"


AWaveManager::AWaveManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AWaveManager::InitializeWaveManager()
{
	GetSpawners(); 
	NewWave(); 
}

void AWaveManager::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWaveManager::GetSpawners()
{
	TArray<AActor*> FoundSpawners; 
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseEnemySpawner::StaticClass(), FoundSpawners);
	
	for (AActor* Actor : FoundSpawners)
	{
		ABaseEnemySpawner* Spawner = CastChecked<ABaseEnemySpawner>(Actor); 
		Spawner->OnEnemyDefeatedDelegate.AddDynamic(this, &AWaveManager::OnEnemyDefeated);
		Spawners.Add(Spawner);
	}
}

void AWaveManager::StartWave()
{
	BuildEnemyPool(); 
	for (int32 i = 0; i < FMath::Min(GetPoolSize(), MaxEnemyCount); ++i)
	{
		int RandomSpawner = FMath::RandRange(0, Spawners.Num() - 1);
		Spawners[RandomSpawner]->AddEnemyToQueue(GetEnemyFromPool());
	}
}

void AWaveManager::NewWave()
{
	WaveNumber++; 
	StartWave(); 
}

void AWaveManager::EndWave()
{
	
}

void AWaveManager::EnterTransition()
{
	
	float Timer = FMath::RandRange(MinTimerRange,FMath::Max(MinTimerRange,MaxTimerRange));
	if (GetWorldTimerManager().IsTimerActive(TransitionTimerHandle))
	{
		GetWorldTimerManager().ClearTimer(TransitionTimerHandle);
	}
	GetWorldTimerManager().SetTimer(TransitionTimerHandle, this, &AWaveManager::NewWave, Timer, false); 
}

void AWaveManager::BuildEnemyPool()
{
	// the waves in the data table will be held as a number
	FName RowName = FName(*FString::FromInt(WaveNumber)); 
	
	if (WaveDataTable)
	{
		if (FWaveDataRow* WaveData = WaveDataTable->FindRow<FWaveDataRow>(RowName, TEXT("")))
		{
			EnemyPool = WaveData->WaveModifiers.EnemyPool; 
		}
		else
		{
						
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("The Data table for the wave manager isn't set")); 
	}
	
	EnemiesRemaining = GetPoolSize(); 
}

int32 AWaveManager::GetPoolSize() const
{
	int32 LocalSum = 0;
	TArray<int32> Values; 
	EnemyPool.GenerateValueArray(Values);
	for (int32 Value : Values)
	{
		LocalSum += Value;
	}
	return LocalSum;
}

TSubclassOf<AEnemyCharacter> AWaveManager::GetEnemyFromPool()
{
	TArray<TSubclassOf<AEnemyCharacter>>Keys; 
	EnemyPool.GetKeys(Keys);
	TSubclassOf<AEnemyCharacter> SelectedEnemy = Keys[FMath::RandRange(0, Keys.Num() - 1)];
	int32* Value = EnemyPool.Find(SelectedEnemy); 
	if (Value)
	{
		(*Value)--; 
		if (*Value> 0)
		{
			EnemyPool.Add(SelectedEnemy,*Value); 
		}
		else
		{
			EnemyPool.Remove(SelectedEnemy); 
		}
	}
	return SelectedEnemy; 
}

void AWaveManager::OnEnemyDefeated()
{
	EnemiesRemaining--; 
	if (EnemiesRemaining <= 0)
	{
		EnterTransition(); 
	}
	else
	{
		int RandomSpawner = FMath::RandRange(0, Spawners.Num() - 1);
		Spawners[RandomSpawner]->AddEnemyToQueue(GetEnemyFromPool()); 
	}
}
