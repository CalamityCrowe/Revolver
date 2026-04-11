// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Spawn/BaseEnemySpawner.h"

#include "Characters/Enemies/EnemyCharacter.h"
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
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn; 
		FTransform SpawnTransform = FTransform(GetActorRotation(),GetSpawnLocation(),FVector::OneVector);
		if (AEnemyCharacter* Enemy = GetWorld()->SpawnActor<AEnemyCharacter>(EnemyQueue[0], SpawnTransform, SpawnParams))
		{
			Enemy->OnDeathDelegate.AddDynamic(this, &ABaseEnemySpawner::OnEnemyDefeated); 
			EnemyQueue.RemoveAt(0); 
			return true; 
		}
	}
	return false;
}

void ABaseEnemySpawner::AddEnemyToQueue(TSubclassOf<AEnemyCharacter> EnemyRef)
{
	EnemyQueue.Add(EnemyRef); 
	SpawnEnemy(); 
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
	if (OnEnemyDefeatedDelegate.IsBound())
	{
		OnEnemyDefeatedDelegate.Broadcast(); 
	}
}

FVector ABaseEnemySpawner::GetSpawnLocation() const
{
	if (BoxSpawner)
	{
		FVector Origin = GetActorLocation(); 
		FVector Extent = BoxSpawner->GetScaledBoxExtent(); 
		
		return FVector(FMath::RandRange(Origin.X - Extent.X, Origin.X + Extent.Y), 
			FMath::RandRange(Origin.Y - Extent.Y, Origin.Y + Extent.Y),
			Origin.Z); 
		
	}
	return GetActorLocation();
}



