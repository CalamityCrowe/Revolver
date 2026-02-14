// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "CharacterBase.generated.h"

UCLASS()
class REVOLVER_API ACharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void PossessedBy(AController* NewController) override;
	
	virtual void OnRep_PlayerState() override;
private: 
	/*UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GAS", meta = (AllowPrivateAccess))
	TWeakObjectPtr<UEnhancedAbilitySystemComponent> ASC;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS", meta = (AllowPrivateAccess))
	TWeakObjectPtr<UEnhancedAttributeSet> AttributeSet; */
	
};
