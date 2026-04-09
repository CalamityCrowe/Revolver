// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Ability/EnhancedGameplayAbility.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/Character.h"

UEnhancedGameplayAbility::UEnhancedGameplayAbility():ActivationPolicy(EEnhancedActivationPolicy::OnInputTriggered),bActivateOnGranted(false)
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	FGameplayTagContainer AbilityContainer;
	AbilityContainer.AddTag(FGameplayTag::RequestGameplayTag(TEXT("GameplayAbility"))); 
	SetAssetTags(AbilityContainer); 
	
	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag("State.Dead")); 
	
}

ACharacter* UEnhancedGameplayAbility::GetCharacterFromActorInfo() const
{
	return(CurrentActorInfo ? Cast<ACharacter>(CurrentActorInfo->AvatarActor.Get()) : nullptr); 
}

FGameplayTagContainer UEnhancedGameplayAbility::GetActivationOwnedTags() const
{
	return ActivationOwnedTags; 
}

void UEnhancedGameplayAbility::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);
	if (bActivateOnGranted)
	{
		ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle, false); 
	}
}

void UEnhancedGameplayAbility::OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilitySpec& Spec)
{
	Super::OnRemoveAbility(ActorInfo, Spec);
	
	// I dont implement anything here as this is more a reference of what I should call if I need to remove passive abilities
}
