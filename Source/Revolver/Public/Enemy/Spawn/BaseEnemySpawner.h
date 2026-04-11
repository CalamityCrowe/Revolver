
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseEnemySpawner.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEnemyDefeated);

class UBoxComponent; 
class AEnemyCharacter; 

UCLASS()
class REVOLVER_API ABaseEnemySpawner : public AActor
{
	GENERATED_BODY()

public:
	ABaseEnemySpawner();
	
	UFUNCTION()
	bool SpawnEnemy(); 
	
	void AddEnemyToQueue(TSubclassOf<AEnemyCharacter> EnemyRef);
	
	UPROPERTY(BlueprintAssignable)
	FOnEnemyDefeated OnEnemyDefeatedDelegate;  // we will bind this in the wave manager
	
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UBoxComponent> BoxSpawner;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Spawner logic")
	float SpawnTimer;
	
	UPROPERTY()
	TArray<TSubclassOf<AEnemyCharacter>> EnemyQueue; 
	
	FTimerHandle SpawnTimerHandle; 
	
	void AttemptToSpawn();
	UFUNCTION()
	void OnEnemyDefeated(); 
	
	FVector GetSpawnLocation() const;
	
};
