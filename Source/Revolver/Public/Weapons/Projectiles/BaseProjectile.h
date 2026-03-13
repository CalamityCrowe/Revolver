// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "BaseProjectile.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class REVOLVER_API ABaseProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseProjectile();
	UFUNCTION(BlueprintCallable)
	void SetTargetLocation(const FVector& NewLocation) {TargetLocation = NewLocation;};
	
	void SetProjectileDamage(const FGameplayEffectSpecHandle& InDamageEffect); 
	
	void SetSpeed(const float NewSpeed) {Speed = NewSpeed;};
	
	virtual void Destroyed() override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category = "Components")
	TObjectPtr<UStaticMeshComponent> Mesh; 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category = "Components")
	TObjectPtr<USphereComponent> Collider; 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category = "Components")
	TObjectPtr<UProjectileMovementComponent> MovementComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category = "Abilities|GameplayCues")
	FGameplayTag SpawnCueTag; 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category = "Abilities|GameplayCues")
	FGameplayTag ImpactCueTag; 
	
	float Speed; 
	
	UPROPERTY()
	FGameplayEffectSpecHandle EffectSpecHandle;
	
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	FVector TargetLocation; 
private: 
	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
