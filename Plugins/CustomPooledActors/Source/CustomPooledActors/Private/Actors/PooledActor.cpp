// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/PooledActor.h"


// Sets default values
APooledActor::APooledActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APooledActor::SetInUse(const bool InUse)
{
	bInUse = InUse;
	SetActorEnableCollision(InUse); 
	SetActorTickEnabled(InUse); 
	GetWorldTimerManager().ClearTimer(ReturnTimer); 
	if (InUse)
	{
		GetWorldTimerManager().SetTimer(ReturnTimer, this, &APooledActor::ReturnToPool, TimeToLive,false); 
	}
}

// Called when the game starts or when spawned
void APooledActor::BeginPlay()
{
	Super::BeginPlay();
	SetInUse(false);
}

void APooledActor::ReturnToPool()
{
	SetInUse(false);
}

