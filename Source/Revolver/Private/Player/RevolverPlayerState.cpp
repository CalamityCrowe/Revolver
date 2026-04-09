// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/RevolverPlayerState.h"

// plugin
#include "Characters/Player/RevolverPlayerCharacter.h"
#include "GAS/EnhancedAbilitySystemComponent.h"
#include "GAS/Attributes/RevolverAttributeSet.h"

ARevolverPlayerState::ARevolverPlayerState()
{
	ASC = CreateDefaultSubobject<UEnhancedAbilitySystemComponent>("Ability System Component");
	ASC->SetReplicationMode(EGameplayEffectReplicationMode::Full); 
	
	AttributeSet = CreateDefaultSubobject<URevolverAttributeSet>("Player Attributes"); 
	
	DeadTag = FGameplayTag::RequestGameplayTag("State.Dead"); 
}

UAbilitySystemComponent* ARevolverPlayerState::GetAbilitySystemComponent() const
{
	if (ASC.Get())
	{
		return ASC; 
	}
	return nullptr;
}

URevolverAttributeSet* ARevolverPlayerState::GetAttributeSet() const
{
	if (AttributeSet.Get())
	{
		return AttributeSet;
	}
	return nullptr;
}

void ARevolverPlayerState::BeginPlay()
{
	Super::BeginPlay();
	
	if (ASC)
	{
		HealthChangedDelegate = ASC->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthAttribute()).AddUObject(this, &ARevolverPlayerState::HealthChanged);
	}
}

float ARevolverPlayerState::GetHealth() const
{
	if (AttributeSet.Get())
	{
		return AttributeSet->GetHealth();
	}
	return 0.0f;
}

float ARevolverPlayerState::GetMaxHealth() const
{
	if (AttributeSet)
	{
		return AttributeSet->GetMaxHealth();
	}
	return 0.0f;
}

bool ARevolverPlayerState::IsAlive() const
{
	return GetHealth() > 0.0f;
}


void ARevolverPlayerState::HealthChanged(const FOnAttributeChangeData& Data)
{
	float NewHealth = Data.NewValue;
	if (!IsAlive() && !ASC->HasMatchingGameplayTag(DeadTag))
	{
		if (ARevolverPlayerCharacter* Player = Cast<ARevolverPlayerCharacter>(GetPawn()))
		{
			Player->Die(); 
		}
	}
}
