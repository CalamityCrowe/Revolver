// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "WeaponBase.generated.h"

UCLASS()
class REVOLVER_API AWeaponBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeaponBase();

	UFUNCTION()
	void HitScanStart(const FGameplayEffectSpecHandle& InEffectSpecHandle);
	
	UFUNCTION()
	void HitScanEnd();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void HitScan(); 
private: 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<USkeletalMeshComponent> WeaponMesh; 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<USceneComponent> TraceStart; 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<USceneComponent> TraceEnd;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Hit Scan", meta = (AllowPrivateAccess = true))
	float TraceRadius;
	UPROPERTY(EditDefaultsOnly, BLueprintReadOnly, Category = "Hit Scan", meta = (AllowPrivateAccess = true))
	float TraceTimer; 
	
	FGameplayEffectSpecHandle EffectSpecHandle; 
	
	FTimerHandle HitScanTimer;
	
	UPROPERTY()
	TArray<AActor*> HitActors;
	
};
