// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayAbilitySpec.h"
#include "GAS/EnhancedAbilitySet.h"
#include "Revolver/Revolver.h"
#include "CharacterBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharacterHitReactDelegate, EHitReactDirection,Direction); 


class UEnhancedAbilitySystemComponent;
class UEnhancedAttributeSet;

UCLASS()
class REVOLVER_API ACharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();
	
	UPROPERTY(BlueprintAssignable, Category = "GAS|Character")
	FCharacterHitReactDelegate ShowHitReactDelegate; 
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	EHitReactDirection GetHitReactDirection(const FVector& ImpactPoint) const;
	
	
	void RemoveAbilities(TArray<FGameplayAbilitySpecHandle> AbilityHandlesToRemove); 
	
	float GetHealth() const;
	
	bool IsAlive() const;
	
	virtual void Die(); 
	
	UFUNCTION(BlueprintCallable)
	virtual void FinishDying(); 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void PossessedBy(AController* NewController) override;
	
	virtual void OnRep_PlayerState() override;

	UFUNCTION(BlueprintCallable, Category = "GAS|Event Functions")
	void SendGameplayEventToSelf(const FGameplayEventData& EventData);
	
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GAS", meta = (AllowPrivateAccess))
	TWeakObjectPtr<UEnhancedAbilitySystemComponent> ASC;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS", meta = (AllowPrivateAccess))
	TWeakObjectPtr<UEnhancedAttributeSet> AttributeSet; 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input System| Abilities")
	TObjectPtr<UEnhancedAbilitySet> AbilitySet; 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input System| Abilities")
	TObjectPtr<UAnimMontage> DeathMontage;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input System| Abilities")
	FGameplayTag DeadTag; 
	
	FAbilitySet_GrantedHandles GrantedHandles; 

	
};
