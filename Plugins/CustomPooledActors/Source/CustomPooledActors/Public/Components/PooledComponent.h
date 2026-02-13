// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PooledComponent.generated.h"

class APooledActor;

UCLASS

(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CUSTOMPOOLEDACTORS_API UPooledComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPooledComponent();

	APooledActor* SpawnFromPool(const FTransform& SpawnTransform); 
	
protected:
	virtual void BeginPlay() override;

	APooledActor* FindFirstAvailableActor(); 
	
private: 
	
	void InitializePool(); 
	
	UPROPERTY(EditDefaultsOnly, Category = "Object Pool", meta = (BlueprintProtected = true))
	TSubclassOf<APooledActor> PooledActorClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Object Pool", meta = (BlueprintProtected = true))
	int PoolSize;
	
	TArray<TObjectPtr<APooledActor>> PooledActors;
};
