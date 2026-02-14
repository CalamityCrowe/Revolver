// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/CharacterBase.h"

#include "Components/CapsuleComponent.h"


ACharacterBase::ACharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
	
	GetCapsuleComponent()->InitCapsuleSize(35.0f, 90.0f); 
}

UAbilitySystemComponent* ACharacterBase::GetAbilitySystemComponent() const
{
	/*if (ASC.Get())
	{
		return ASC.Get(); 
	}*/
	return nullptr; 
}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	/*if (ASC.Get())
	{
		ASC->InitAbilityActorInfo(this, this); 
	}*/
}

void ACharacterBase::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	/*if (ASC.Get())
	{
		ASC->InitAbilityActorInfo(this, this); 
	}*/
}


