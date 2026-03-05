// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/CharacterBase.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class REVOLVER_API AEnemyCharacter : public ACharacterBase
{
	GENERATED_BODY()

public:
	AEnemyCharacter();

	virtual void BeginPlay() override;
	
	virtual void PossessedBy(AController* inController) override;
protected:
	
	virtual void HealthUpdated(const FOnAttributeChangeData& Data); 

	virtual void Die() override;
	
	virtual void FinishDying() override;
private: 
	UPROPERTY()
	UEnhancedAttributeSet* HardRefAttributeSet; 
	
	UPROPERTY()
	UEnhancedAbilitySystemComponent* HardRefASC; 
};
