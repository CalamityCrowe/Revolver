// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Ability/EnhancedGameplayAbility.h"

UEnhancedGameplayAbility::UEnhancedGameplayAbility():ActivationPolicy(EEnhancedActivationPolicy::OnInputTriggered)
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}
