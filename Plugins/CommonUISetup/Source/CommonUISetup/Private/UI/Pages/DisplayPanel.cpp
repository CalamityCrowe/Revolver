// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Pages/DisplayPanel.h"

#include "Components/ScrollBox.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Components/OptionsCycler.h"
#include "GameFramework/GameUserSettings.h"
#include "Subsystem/ExtendedUserSettingsSubsystem.h"

UDisplayPanel::UDisplayPanel(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	const UEnum* EnumPtr = StaticEnum<EWindowMode::Type>();
	for (int32 i = 0; i < EnumPtr->NumEnums() -1; i++)
	{
		AllWindowModes.Add(static_cast<EWindowMode::Type>(EnumPtr->GetValueByIndex(i)));
	}
	
}


void UDisplayPanel::NativePreConstruct()
{
	UGameInstance* GI = GetGameInstance();
	if (GI)
	{
		ExtendedUserSettingsSubsystem = GI->GetSubsystem<UExtendedUserSettingsSubsystem>();
	}
	Super::NativePreConstruct();
	
}

void UDisplayPanel::InitializeOptions()
{
	Super::InitializeOptions();
	
	if (OptionsCycleClass)
	{
		
		InitializeMonitorSetting();
		InitializeWindowModeSetting(); 
		InitializeResolutionSetting();
		InitializeFPSLimitSettings(); 
	}
}

void UDisplayPanel::InitializeMonitorSetting()
{
	DisplayNames.Empty();
	AllDisplays.Empty();
	
	if (ExtendedUserSettingsSubsystem)
	{
		AllDisplays = ExtendedUserSettingsSubsystem->GetAllMonitorInfo();
		for (FMonitorInfo Monitor : AllDisplays)
		{
			DisplayNames.Add(FText::FromString(Monitor.Name));
		}
	}
	
	if (UOptionsCycler* OC = CreateWidget<UOptionsCycler>(this, OptionsCycleClass))
	{
		MonitorCycler = OC;

		MonitorCycler->InitializeOption(MonitorOptionText,DisplayNames, 0); 
		MonitorCycler->SetPadding(OptionsPadding); 
		SB_OptionsScroll->AddChild(OC); 
	}
}

void UDisplayPanel::InitializeWindowModeSetting()
{
	WindowModesArray.Empty(); 
	
	for (EWindowMode::Type WindowMode : AllWindowModes)
	{
		FText ModeText = StaticEnum<EWindowMode::Type>()->GetDisplayNameTextByValue(WindowMode); 
		WindowModesArray.Add(ModeText);
	}
	
	if (UOptionsCycler* OC = CreateWidget<UOptionsCycler>(this, OptionsCycleClass))
	{
		int DefaultWindowMode = AllWindowModes.Find( UGameUserSettings::GetGameUserSettings()->GetDefaultWindowMode()); 
		
		WindowModeCycler = OC;
		WindowModeCycler->InitializeOption(WindowModesText,WindowModesArray, DefaultWindowMode);
		WindowModeCycler->SetPadding(OptionsPadding);
		SB_OptionsScroll->AddChild(OC);
	}
}

void UDisplayPanel::InitializeResolutionSetting()
{
	if (UOptionsCycler* OC = CreateWidget<UOptionsCycler>(this, OptionsCycleClass))
	{
		ResolutionCycler = OC;
		TArray<FText> Resolutions = TArray<FText>
		{
			FText(FText::FromString("1920x1080")),
			FText(FText::FromString("1280x720"))
		}; 
		ResolutionCycler->InitializeOption(ResolutionText,Resolutions, 0);
		ResolutionCycler->SetPadding(OptionsPadding);
		SB_OptionsScroll->AddChild(OC);
	}
}

void UDisplayPanel::InitializeFPSLimitSettings()
{
	if (UOptionsCycler* OC = CreateWidget<UOptionsCycler>(this, OptionsCycleClass))
	{
		FPSLimitCycler = OC;
		TArray<FText> FPSLimits = TArray<FText>
		{
			FText(FText::FromString("144")),
			FText(FText::FromString("60"))
		}; 
		FPSLimitCycler->InitializeOption(FPSLimitText,FPSLimits, 0);
		FPSLimitCycler->SetPadding(OptionsPadding);
		SB_OptionsScroll->AddChild(OC);
	}
}

void UDisplayPanel::ApplyActiveDisplay()
{
	FMonitorInfo MonitorInfo = AllDisplays[MonitorCycler->GetCurrentSetting()];
	if (ExtendedUserSettingsSubsystem)
	{
		ExtendedUserSettingsSubsystem->SetActiveDisplay(MonitorInfo.ID); 
	}
}
void UDisplayPanel::ApplyWindowModeSettings()
{
	if (UGameUserSettings* US = UGameUserSettings::GetGameUserSettings())
	{
		US->SetFullscreenMode(AllWindowModes[WindowModeCycler->GetCurrentSetting()]);
		US->ApplyResolutionSettings(false); 
	}
}

void UDisplayPanel::ApplyOptions()
{
	Super::ApplyOptions();
	ApplyWindowModeSettings(); 
	ApplyActiveDisplay();
}

void UDisplayPanel::ResetOptions()
{
	Super::ResetOptions();
}
