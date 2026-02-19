// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Ability/EnhancedGameplayAbility.h"

#include "GameFramework/Character.h"

UEnhancedGameplayAbility::UEnhancedGameplayAbility():ActivationPolicy(EEnhancedActivationPolicy::OnInputTriggered)
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

ACharacter* UEnhancedGameplayAbility::GetCharacterFromActorInfo() const
{
	return(CurrentActorInfo ? Cast<ACharacter>(CurrentActorInfo->AvatarActor.Get()) : nullptr); 
}
