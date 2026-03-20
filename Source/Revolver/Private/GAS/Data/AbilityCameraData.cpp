// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Data/AbilityCameraData.h"

UAbilityCameraData::UAbilityCameraData():AbilitySocketOffset(FVector()), AbilityTargetArm(300), AbilityFOV(90), CameraTransition(0.0f)
{
	CameraTag = FGameplayTag::RequestGameplayTag(TEXT("GameplayEffect.Camera"));  // we just set the defualt value to this so there is a tag already assigned
}
