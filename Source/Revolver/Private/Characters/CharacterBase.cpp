// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/CharacterBase.h"

//engine
#include "Components/CapsuleComponent.h"

// enhanced ability plugin
#include "AbilitySystemBlueprintLibrary.h"
#include "GAS/EnhancedAbilitySystemComponent.h"
#include "GAS/Attributes/EnhancedAttributeSet.h"


ACharacterBase::ACharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
	
	GetCapsuleComponent()->InitCapsuleSize(35.0f, 90.0f);
	
	DeadTag = FGameplayTag::RequestGameplayTag(FName("State.Dead"),false); 
}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (ASC.Get())
	{
		ASC->InitAbilityActorInfo(this, this); 
		
	}
}

void ACharacterBase::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	if (ASC.Get())
	{
		ASC->InitAbilityActorInfo(this, this); 
	}
}

void ACharacterBase::SendGameplayEventToSelf(const FGameplayEventData& EventData)
{
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, EventData.EventTag,EventData); 
}

UAbilitySystemComponent* ACharacterBase::GetAbilitySystemComponent() const
{
	if (ASC.Get())
	{
		return ASC.Get();
	}
	return nullptr; 
}

EHitReactDirection ACharacterBase::GetHitReactDirection(const FVector& ImpactPoint) const
{
	FVector ActorLocation = GetActorLocation();
	
	float FrontBackPlaneDist = FVector::PointPlaneDist(ImpactPoint,ActorLocation,GetActorRightVector()); 
	float LeftRightPlaneDist = FVector::PointPlaneDist(ImpactPoint,ActorLocation,GetActorForwardVector());
	
	if (FMath::Abs(FrontBackPlaneDist) <= FMath::Abs(LeftRightPlaneDist))
	{
		if (LeftRightPlaneDist >= 0)
		{
			return EHitReactDirection::Front; 
		}
		else
		{
			return EHitReactDirection::Back;
		}
	}
	else
	{
		if (FrontBackPlaneDist >= 0)
		{
			return EHitReactDirection::Right;
		} 
		else
		{
			return EHitReactDirection::Left;
		}
	}
}

void ACharacterBase::RemoveAbilities(TArray<FGameplayAbilitySpecHandle> AbilityHandlesToRemove)
{
	if (!ASC.Get()|| !HasAuthority())
	{
		return; 
	}
	
	for (FGameplayAbilitySpecHandle& AbilityHandle : AbilityHandlesToRemove)
	{
		ASC.Get()->ClearAbility(AbilityHandle);	
	}
}



void ACharacterBase::Die()
{
	if (ASC.IsValid())
	{
		ASC->CancelAllAbilities(); 
		
		ASC->AddLooseGameplayTag(DeadTag); 
	}
	if (DeathMontage)
	{
		if (!GetMesh()->GetAnimInstance()->Montage_IsPlaying(DeathMontage))
		GetMesh()->PlayAnimation(DeathMontage,false);
	}
	else
	{
		FinishDying(); 
	}
	
}

void ACharacterBase::FinishDying()
{
	Destroy();
}

float ACharacterBase::GetHealth() const
{
	if (AttributeSet.Get())
	{
		return AttributeSet->GetHealth(); 
	}
	return 0; 
}

bool ACharacterBase::IsAlive() const
{
	return GetHealth() > 0.0f;
}

