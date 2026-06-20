// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GenericPlatform/GenericApplication.h"
#include "ExtendedUserSettingsSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class COMMONUISETUP_API UExtendedUserSettingsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public: 
	TArray<FMonitorInfo> GetAllMonitorInfo() const; 
	
	void SetActiveDisplay(const FString& DisplayID); 
	
};
