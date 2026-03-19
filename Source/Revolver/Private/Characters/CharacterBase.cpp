// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/CharacterBase.h"

//engine
#include "Components/CapsuleComponent.h"

// enhanced ability plugin
#include "AbilitySystemBlueprintLibrary.h"
#include "GAS/EnhancedAbilitySystemComponent.h"
#include "GAS/Attributes/RevolverAttributeSet.h"


ACharacterBase::ACharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
	
	GetCapsuleComponent()->InitCapsuleSize(35.0f, 90.0f);
	
	DeadTag = FGameplayTag::RequestGameplayTag(FName("State.Dead"),false); 
	
	HitDirectionFront = FGameplayTag::RequestGameplayTag(FName("Effect.HitReact.Front"),false); 
	HitDirectionBack = FGameplayTag::RequestGameplayTag(FName("Effect.HitReact.Back"),false); 
	HitDirectionLeft = FGameplayTag::RequestGameplayTag(FName("Effect.HitReact.Left"),false); 
	HitDirectionRight = FGameplayTag::RequestGameplayTag(FName("Effect.HitReact.Right"),false); 
	
	// we do this so the stencil doesn't overlap from AOE targetting 
	GetMesh()->bRenderCustomDepth = true; 
	GetMesh()->CustomDepthStencilValue = 1; 
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
	
	// positivie in the front negative in the back
	float ForwardDist = FVector::PointPlaneDist(ImpactPoint,ActorLocation,GetActorForwardVector()); 
	
	// positive to the right, negative to the back
	float RightDist = FVector::PointPlaneDist(ImpactPoint,ActorLocation,GetActorRightVector());
	
	if (FMath::Abs(ForwardDist) >= FMath::Abs(RightDist))
	{
		return ForwardDist >= 0? EHitReactDirection::Front :EHitReactDirection::Back;
	}
	else
	{
		return RightDist >= 0 ? EHitReactDirection::Right :EHitReactDirection::Left;
	}
}

void ACharacterBase::PlayHitReact(FGameplayTag HitDirection)
{
	if (IsAlive())
	{
		if (HitDirection == HitDirectionFront)
		{
			ShowHitReactDelegate.Broadcast(EHitReactDirection::Front); 
		}
		else if (HitDirection == HitDirectionBack)
		{
			ShowHitReactDelegate.Broadcast(EHitReactDirection::Back);
		}
		else if (HitDirection == HitDirectionLeft)
		{
			ShowHitReactDelegate.Broadcast(EHitReactDirection::Left);
		}
		else if (HitDirection == HitDirectionRight)
		{
			ShowHitReactDelegate.Broadcast(EHitReactDirection::Right);
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

