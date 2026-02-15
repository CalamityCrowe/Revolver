// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/RevolverPlayerState.h"

// plugin
#include "GAS/EnhancedAbilitySystemComponent.h"
#include "GAS/Attributes/EnhancedAttributeSet.h"

ARevolverPlayerState::ARevolverPlayerState()
{
	ASC = CreateDefaultSubobject<UEnhancedAbilitySystemComponent>("Ability System Component");
	
	AttributeSet = CreateDefaultSubobject<UEnhancedAttributeSet>("Player Attributes"); 
}

UAbilitySystemComponent* ARevolverPlayerState::GetAbilitySystemComponent() const
{
	if (ASC.Get())
	{
		return ASC; 
	}
	return nullptr;
}

UEnhancedAttributeSet* ARevolverPlayerState::GetAttributeSet() const
{
	if (AttributeSet.Get())
	{
		return AttributeSet;
	}
	return nullptr;
}
