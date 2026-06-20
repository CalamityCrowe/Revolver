// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Pages/Settings/DisplayPanel.h"

#include "Components/ScrollBox.h"
#include "Kismet/KismetSystemLibrary.h"
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
	
	if (UGameInstance* GI = GetGameInstance())
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
	Resolutions.Empty();
	
	TArray<FIntPoint> TempResolutions; 
	if (UKismetSystemLibrary::GetSupportedFullscreenResolutions(TempResolutions))
	{
		for (const FIntPoint& Resolution : TempResolutions)
		{
			FFormatNamedArguments Args; 
			Args.Add(TEXT("X"), Resolution.X);
			Args.Add(TEXT("Y"), Resolution.Y);
			Resolutions.Add(FText::Format(NSLOCTEXT("Display","ResolutionFormat", "{X}x{Y}"), Args)); 
		}
	} 
		
	if (UOptionsCycler* OC = CreateWidget<UOptionsCycler>(this, OptionsCycleClass))
	{
		ResolutionCycler = OC;
		
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
		TArray<FText> FPSLimitsText; 
		for (int FPS: FPSLimits)
		{
			FPSLimitsText.Add(FText::FromString(FString::FromInt(FPS))); 
		}
		FPSLimitCycler->InitializeOption(FPSLimitText,FPSLimitsText, 0);
		FPSLimitCycler->SetPadding(OptionsPadding);
		SB_OptionsScroll->AddChild(OC);
	}
}

void UDisplayPanel::ApplyFPS(UGameUserSettings* US)
{
	US->SetFrameRateLimit(FPSLimits[FPSLimitCycler->GetCurrentSetting()]);
}

void UDisplayPanel::ApplyActiveDisplay()
{
	FMonitorInfo MonitorInfo = AllDisplays[MonitorCycler->GetCurrentSetting()];
	if (ExtendedUserSettingsSubsystem)
	{
		ExtendedUserSettingsSubsystem->SetActiveDisplay(MonitorInfo.ID); 
	}
}
void UDisplayPanel::ApplyWindowModeSettings(UGameUserSettings* US)
{
	US->SetFullscreenMode(AllWindowModes[WindowModeCycler->GetCurrentSetting()]);
}

void UDisplayPanel::ApplyResolution(UGameUserSettings* US)
{
	TArray<FIntPoint> TempResolutions;
	if (UKismetSystemLibrary::GetSupportedFullscreenResolutions(TempResolutions))
	{
		FIntPoint SelectedResolution = TempResolutions[ResolutionCycler->GetCurrentSetting()];
		UE_LOG(LogTemp, Warning, TEXT("Setting resolution: %dx%d"), SelectedResolution.X, SelectedResolution.Y);
		US->SetScreenResolution(SelectedResolution);
	}
}

void UDisplayPanel::ApplyOptions()
{
	Super::ApplyOptions();
	if (UGameUserSettings* US = UGameUserSettings::GetGameUserSettings())
	{
		ApplyFPS(US); 
		ApplyActiveDisplay();
		ApplyResolution(US);
		ApplyWindowModeSettings(US); 
		US->ApplySettings(false); 

	} 
}

void UDisplayPanel::ResetOptions()
{
	Super::ResetOptions();
}
