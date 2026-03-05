// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "WeaponBase.generated.h"

class UEnhancedAbilitySet;

USTRUCT(Blueprintable)
struct REVOLVER_API FWeaponConfig
{
	GENERATED_BODY()
public: 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UEnhancedAbilitySet> AbilitiesToGrant; 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	FName EquipSocketName; 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	FName UnEquipSocketName; 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UAnimMontage> EquipMontage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UAnimMontage> UnEquipMontage;
};


UCLASS()
class REVOLVER_API AWeaponBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeaponBase();
	
	FWeaponConfig GetWeaponConfig() const {return WeaponConfig; }

	UStaticMeshComponent* GetMesh() const {return WeaponMesh; }
	
	UFUNCTION()
	virtual void HitScanStart(const FGameplayEffectSpecHandle& InEffectSpecHandle){};
	
	UFUNCTION()
	virtual void HitScanEnd(){}; 
	
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
private: 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> WeaponMesh; 

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon Config",meta = (AllowPrivateAccess = true))
	FWeaponConfig WeaponConfig; 
	


	


	
};
