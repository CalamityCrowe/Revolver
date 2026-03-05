// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "InstrumentWeapon.generated.h"

UCLASS()
class REVOLVER_API AInstrumentWeapon : public AWeaponBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInstrumentWeapon();
	
	virtual void HitScanStart(const FGameplayEffectSpecHandle& InEffectSpecHandle) override;	

	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	FGameplayEffectSpecHandle UserSpecHandle;
	
	virtual void HitScan() override;
};
