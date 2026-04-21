// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OptionsPanel.h"
#include "DisplayPanel.generated.h"

class UExtendedUserSettingsSubsystem;
/**
 * 
 */
UCLASS(Abstract, HideDropdown)
class COMMONUISETUP_API UDisplayPanel : public UOptionsPanel
{
	GENERATED_UCLASS_BODY()
protected:
	
	virtual void NativePreConstruct() override;
	
	virtual void InitializeOptions() override;
	virtual void ApplyOptions() override;
	virtual void ResetOptions() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Options Panel|Display Options")
	FText MonitorOptionText; 
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Options Panel|Display Options" )
	FText WindowModesText;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Options Panel|Display Options")
	FText ResolutionText; 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Options Panel|Display Options")
	FText FPSLimitText;
	
	UPROPERTY()
	TObjectPtr<UOptionsCycler> MonitorCycler; 
	UPROPERTY()
	TObjectPtr<UOptionsCycler> WindowModeCycler;
	UPROPERTY()
	TObjectPtr<UOptionsCycler> ResolutionCycler;
	UPROPERTY()
	TObjectPtr<UOptionsCycler> FPSLimitCycler;
	
	
	TArray<EWindowMode::Type> AllWindowModes;
	
	TArray<FText> WindowModesArray;
	TArray<FText> DisplayNames; 
	TArray<FText> Resolutions; 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Options Panel|Display Options")
	TArray<int> FPSLimits;
	
	TArray<FMonitorInfo> AllDisplays; 
	
	UPROPERTY()
	UExtendedUserSettingsSubsystem* ExtendedUserSettingsSubsystem;
private: 
	void InitializeMonitorSetting();
	void InitializeWindowModeSetting();
	void InitializeResolutionSetting();
	void InitializeFPSLimitSettings();
	
	void ApplyFPS(UGameUserSettings* US);
	void ApplyActiveDisplay(); 
	void ApplyWindowModeSettings(UGameUserSettings* US);
	void ApplyResolution(UGameUserSettings* US);

};
