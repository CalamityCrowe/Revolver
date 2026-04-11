// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WaveManager.generated.h"

class ABaseEnemySpawner;
class AEnemyCharacter;

UCLASS()
class REVOLVER_API AWaveManager : public AActor
{
	GENERATED_BODY()

public:

	AWaveManager();
	
	virtual void InitializeWaveManager(); 

protected:

	virtual void BeginPlay() override;
	
	virtual void GetSpawners(); 
	void StartWave(); 
	void NewWave(); 
	void EndWave(); 
	void EnterTransition(); 
	void BuildEnemyPool(); 
	int32 GetPoolSize() const;
	TSubclassOf<AEnemyCharacter> GetEnemyFromPool(); 
	
	UFUNCTION()
	virtual void OnEnemyDefeated(); 
	
private: 
	UPROPERTY()
	TArray<ABaseEnemySpawner*> Spawners; 
	int32 WaveNumber; 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	int32 MaxEnemyCount; 
	int32 EnemiesRemaining; 
	
	TMap<TSubclassOf<AEnemyCharacter>, int32> EnemyPool; 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UDataTable> WaveDataTable;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true, UIMin = 0.0f,ClampMin = 0.0f))
	float MinTimerRange; 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true, UIMin = 0.0f, ClampMin = 0.0f))
	float MaxTimerRange;
	
	FTimerHandle TransitionTimerHandle; 

};
