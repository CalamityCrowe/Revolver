// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseChordedAbility.h"
#include "RadialBurstAbility.generated.h"

class ABaseProjectile;
/**
 * 
 */
UCLASS()
class REVOLVER_API URadialBurstAbility : public UBaseChordedAbility
{
	GENERATED_BODY()
public: 
	URadialBurstAbility();
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
protected: 
	virtual void MontageStarted() override;
	
	
	UPROPERTY(EditDefaultsOnly, Category = "Abilities|Tags")
	FGameplayTag SpawnCueTag;
	
	UPROPERTY(EditDefaultsOnly, Category = "Abilities|Properties|Projectile")
	int NumberOfProjectiles; 
	
	UPROPERTY(EditDefaultsOnly, Category = "Abilities|Properties|Projectile")
	float RadialPitch; 
	
	UPROPERTY(EditDefaultsOnly, Category = "Abilities|Properties|Projectile")
	float ProjectileSpeed; 
	
	UPROPERTY(EditDefaultsOnly, Category = "Abilities|Properties|Projectile")
	TSubclassOf<ABaseProjectile> ProjectileClass; 
	
	UPROPERTY(EditDefaultsOnly, Category = "Abilities|Properties|Projectile")
	bool bStaggeredProjectiles; 
	
	UPROPERTY(EditDefaultsOnly, Category = "Abilities|Properties|Projectile", meta = (EditCondition = "bStaggeredProjectiles", EditConditionHides))
	float StaggeredSpawnTime; 
	
	UFUNCTION()
	virtual void EventRecieved(FGameplayEventData EventData);
	void SpawnProjectile(float YawOffset, ACharacter* OwningCharacter, const FVector& ActorLocation,
	                     const FVector& SpawnLocation, const FVector& ForwardVector,
	                     const FGameplayEffectSpecHandle& DamageEffect, int i);

private: 
	void BurstSpawn(float YawOffset, ACharacter* OwningCharacter, const FVector& ActorLocation, const FVector& SpawnLocation,
				const FVector& ForwardVector, const FGameplayEffectSpecHandle& DamageEffect);
	
	void StaggerSpawn(float YawOffset, ACharacter* OwningCharacter, const FVector& ActorLocation, const FVector& SpawnLocation,
			const FVector& ForwardVector, const FGameplayEffectSpecHandle& DamageEffect);
	
	int CurrentProjectile; 
	
	FTimerHandle TimerHandle;

	
	
};
