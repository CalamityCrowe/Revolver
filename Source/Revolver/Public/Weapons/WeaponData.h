
#pragma once

#include "WeaponData.Generated.h"

class UEnhancedAbilitySet; 


USTRUCT(BlueprintType)
struct REVOLVER_API FWeaponMovementProperties
{
	GENERATED_BODY()
public: 
	FWeaponMovementProperties()
	:bUseControlRotation(false),
	bShouldOrientMovement(false)
	{} 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bUseControlRotation; 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bShouldOrientMovement; 
};

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

