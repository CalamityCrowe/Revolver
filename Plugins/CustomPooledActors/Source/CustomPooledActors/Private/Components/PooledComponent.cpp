// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PooledComponent.h"

#include "Actors/PooledActor.h"

UPooledComponent::UPooledComponent()
{
}


void UPooledComponent::BeginPlay()
{
	Super::BeginPlay();
	InitializePool();
}

APooledActor* UPooledComponent::SpawnFromPool(const FTransform& SpawnTransform)
{
	if (APooledActor* AvailableActor = FindFirstAvailableActor())
	{
		AvailableActor->SetActorTransform(SpawnTransform);
		AvailableActor->SetInUse(true);
		return AvailableActor;
	}
	return nullptr;
}
APooledActor* UPooledComponent::FindFirstAvailableActor()
{
	for (APooledActor* Actor : PooledActors)
	{
		if (!Actor->IsInUse())
		{
			return Actor;
		}
	}
	return nullptr;
}

void UPooledComponent::InitializePool()
{
	if (PooledActorClass)
	{
		for (int i = 0; i < PoolSize; ++i)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = GetOwner(); 
			if (APooledActor* NewActor = GetWorld()->SpawnActor<APooledActor>(PooledActorClass,FVector::ZeroVector,FRotator::ZeroRotator , SpawnParams))
			{
				NewActor->SetInUse(false); 
				PooledActors.AddUnique(NewActor);
			}
		}
	}
}


