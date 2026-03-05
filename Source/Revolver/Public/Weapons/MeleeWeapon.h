// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "MeleeWeapon.generated.h"

UCLASS()
class REVOLVER_API AMeleeWeapon : public AWeaponBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMeleeWeapon();
	
	virtual void HitScanStart(const FGameplayEffectSpecHandle& InEffectSpecHandle)override;
	
	virtual void HitScanEnd() override; 
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void HitScan() override; 
	
private: 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<USceneComponent> TraceStart; 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<USceneComponent> TraceEnd;

	UPROPERTY(EditDefaultsOnly, BLueprintReadOnly, Category = "Hit Scan", meta = (AllowPrivateAccess = true))
	float TraceTimer; 
	
	FTimerHandle HitScanTimer;
};
