// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/EnemyCharacter.h"

#include "GAS/EnhancedAbilitySet.h"
#include "GAS/EnhancedAbilitySystemComponent.h"
#include "GAS/Attributes/RevolverAttributeSet.h"

AEnemyCharacter::AEnemyCharacter()
{
	HardRefASC = CreateDefaultSubobject<UEnhancedAbilitySystemComponent>(TEXT("ASC"));
	ASC = HardRefASC; 
	ASC->SetReplicationMode(EGameplayEffectReplicationMode::Full);
	
	HardRefAttributeSet = CreateDefaultSubobject<URevolverAttributeSet>(TEXT("AttributeSet"));
	AttributeSet = HardRefAttributeSet;
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (ASC.IsValid())
	{
		ASC->InitAbilityActorInfo(this, this); 
		
		if (AbilitySet)
		{
			AbilitySet->GiveToAbilitySystem(ASC.Get(),&GrantedHandles,this); 
		}
		
		ASC->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthAttribute()).AddUObject(this, &AEnemyCharacter::HealthUpdated); 
	}
}

void AEnemyCharacter::PossessedBy(AController* inController)
{
	Super::PossessedBy(inController);
	
	if (AbilitySet)
	{
		AbilitySet->GiveToAbilitySystem(ASC.Get(),&GrantedHandles,this);
	}
}

void AEnemyCharacter::HealthUpdated(const FOnAttributeChangeData& Data)
{
	float Health = Data.NewValue; 
	
	// we could do UI stuff here 
	
	if (!IsAlive() && !ASC->HasMatchingGameplayTag(DeadTag))
	{
		Die(); 
	}
}

void AEnemyCharacter::Die()
{
	Super::Die();
}

void AEnemyCharacter::FinishDying()
{
	Super::FinishDying();
}


