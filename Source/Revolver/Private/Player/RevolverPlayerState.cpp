// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/RevolverPlayerState.h"

// plugin
#include "GAS/EnhancedAbilitySystemComponent.h"
#include "GAS/Attributes/RevolverAttributeSet.h"

ARevolverPlayerState::ARevolverPlayerState()
{
	ASC = CreateDefaultSubobject<UEnhancedAbilitySystemComponent>("Ability System Component");
	
	AttributeSet = CreateDefaultSubobject<URevolverAttributeSet>("Player Attributes"); 
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
