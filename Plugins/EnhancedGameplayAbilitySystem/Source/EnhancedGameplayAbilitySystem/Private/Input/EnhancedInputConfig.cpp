// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/EnhancedInputConfig.h"

const UInputAction* UEnhancedInputConfig::FindNativeInputActionByTag(const FGameplayTag& InputTag) const
{
	for (const FEnhancedInputAction& Action: NativeInputActions)
	{
		if (Action.InputAction && Action.InputTag == InputTag)
		{
			return Action.InputAction;
		}
	}
	return nullptr; 
}

const UInputAction* UEnhancedInputConfig::FindAbilityInputActionByTag(const FGameplayTag& InputTag) const
{
	for (const FEnhancedInputAction& Action: AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag == InputTag)
		{
			return Action.InputAction;
		}
	}
	return nullptr; 
}
