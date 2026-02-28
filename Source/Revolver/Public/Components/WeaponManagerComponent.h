// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GAS/EnhancedAbilitySet.h"
#include "WeaponManagerComponent.generated.h"


class AWeaponBase;
class ACharacterBase;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class REVOLVER_API UWeaponManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UWeaponManagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public: 
	
	void EquipWeapon(TSubclassOf<AWeaponBase> WeaponToEquip); 
	
	void UnEquipWeapon(); 
	
	AWeaponBase* GetEquippedWeapon() const {return EquippedWeapon; }
	
	UAnimInstance* GetAnimInstance() const;
	
private:
	UPROPERTY()
	ACharacterBase* OwningCharacter; 
	
	UPROPERTY()
	AWeaponBase* EquippedWeapon; 
	
	FAbilitySet_GrantedHandles AbilitiesGrantedByWeapon; 
	
	UFUNCTION()
	void OnEquipNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& Payload); 
	UFUNCTION()
	void OnUnEquipNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& Payload); 
	
	void SpawnWeapon(TSubclassOf<AWeaponBase> WeaponToEquip);

	
};
