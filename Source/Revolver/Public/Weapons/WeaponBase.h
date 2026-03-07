// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "Weapons/WeaponData.h"
#include "WeaponBase.generated.h"

class UEnhancedAbilitySet;
class UNiagaraSystem;

UCLASS()
class REVOLVER_API AWeaponBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeaponBase();
	
	FWeaponConfig GetWeaponConfig() const {return WeaponConfig; }
	
	FWeaponMovementProperties GetMovementProperties() const {return MovementProperties; }
	
	UStaticMeshComponent* GetMesh() const {return WeaponMesh; }
	
	UFUNCTION()
	virtual void HitScanStart(const FGameplayEffectSpecHandle& InEffectSpecHandle){HitActors.Empty(); };
	
	UFUNCTION()
	virtual void HitScanEnd(){}; 
	
	virtual void SpawnWeaponParticle(); 
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY()
	TArray<AActor*> HitActors;
	
	UFUNCTION()
	virtual void HitScan(){}
	
	FGameplayEffectSpecHandle EffectSpecHandle; 
		
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Hit Scan", meta = (AllowPrivateAccess = true))
	float TraceRadius;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawn Effect")
	TObjectPtr<UNiagaraSystem> SpawnParticle; 
	
private: 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> WeaponMesh; 

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon Config",meta = (AllowPrivateAccess = true))
	FWeaponConfig WeaponConfig; 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon Config",meta = (AllowPrivateAccess = true))
	FWeaponMovementProperties MovementProperties;
};
