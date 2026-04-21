// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Pages/Settings/GraphicsPanel.h"

#include "IMediaControls.h"
#include "Data/GraphicsSettingsTable.h"
#include "Components/ScrollBox.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Components/OptionsCycler.h"

UGraphicsPanel::UGraphicsPanel(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer), DefaultSelectedIndex(2)
{
	SetIsFocusable(true);
}

void UGraphicsPanel::InitializeOptions()
{
	// calls the parent function to clear the selection box
	Super::InitializeOptions();
	
	// we invalidate these here so they are empty/null for using again
	OverallOptions = nullptr;
	AllOptions.Empty();
	
	if (OptionsTable && OptionsCycleClass) // we check if the data table and the cycler class are valid
	{
		// we then grab all the rows and loop through them
		TArray<FName> RowNames = OptionsTable->GetRowNames(); 
		for (FName RowName : RowNames)
		{
			FGraphicsConfig* RowData = OptionsTable->FindRow<FGraphicsConfig>(RowName, TEXT("")); // we get the current graphics setting and check it is valid
			if (RowData)
			{
				// we then create the widget to display the current setting and grab the setting it is representing
				UOptionsCycler* OC = CreateWidget<UOptionsCycler>(this,OptionsCycleClass);
				FText EnumToText = StaticEnum<EGraphicsOptions>()->GetDisplayNameTextByValue(static_cast<int64>(RowData->GraphicsOptionType));
				
				// we grab all the text values for the setting (medium, high , cinematic, etc)
				TArray<FText> OptionValues;
				RowData->Options.GenerateValueArray(OptionValues);

				// we get all the values for the settings repressented by a string and set the default value
				TArray<int> OptionsKeys;
				RowData->Options.GenerateKeyArray(OptionsKeys);
				int DefaultGraphicsOption = OptionsKeys.Find(GetGraphicsOptionValue(RowData->GraphicsOptionType));
				
				// calls the initiallizer to do the final setup and set some padding
				OC->InitializeOption(EnumToText,OptionValues,DefaultGraphicsOption);
				OC->SetPadding(OptionsPadding);

				AllOptions.Add(RowData->GraphicsOptionType, OC); 
				
				// we check if it is the overall setting and if so, we set the reference to the overall options
				if (RowData->GraphicsOptionType == EGraphicsOptions::Overall)
				{
					OverallOptions = OC;
				}
				else
				{
					OC->OnOptionsChanged.AddDynamic(this, &UGraphicsPanel::OnNonOverallOptionChanged);
				}
				// lastly we add it to the scroll box
				SB_OptionsScroll->AddChild(OC);
			}
		}
		
		if (OverallOptions) // last we check if the overall options is valid and if so we bind the delegate to apply the settings correctly
		OverallOptions->OnOptionsChanged.AddDynamic(this,&UGraphicsPanel::ChangeOverallValues); 
	}
}

void UGraphicsPanel::ApplyOptions()
{
	Super::ApplyOptions();
	if (UGameUserSettings* CurrentGameSettings = UGameUserSettings::GetGameUserSettings())
	{
		for (TPair<EGraphicsOptions, UOptionsCycler*>& Option :AllOptions)
		{
			if (int32 SettingValue = Option.Value->GetCurrentSetting(); SettingValue >= 0)
			{
				switch (Option.Key)
				{
				case EGraphicsOptions::Overall:
					CurrentGameSettings->SetOverallScalabilityLevel(SettingValue); 
					break;
				case EGraphicsOptions::GlobalIllumination:
					CurrentGameSettings->SetGlobalIlluminationQuality(SettingValue);
					break;
				case EGraphicsOptions::Shadows:
					CurrentGameSettings->SetShadowQuality(SettingValue);
					break;
				case EGraphicsOptions::AntiAliasing:
					CurrentGameSettings->SetAntiAliasingQuality(SettingValue);
					break;
				case EGraphicsOptions::ViewDistance:
					CurrentGameSettings->SetViewDistanceQuality(SettingValue);
					break;
				case EGraphicsOptions::TextureQuality:
					CurrentGameSettings->SetTextureQuality(SettingValue);
					break;
				case EGraphicsOptions::Effects:
					CurrentGameSettings->SetVisualEffectQuality(SettingValue);
					break;
				case EGraphicsOptions::Reflections:
					CurrentGameSettings->SetReflectionQuality(SettingValue);
					break;
				case EGraphicsOptions::PostProcessing:
					CurrentGameSettings->SetPostProcessingQuality(SettingValue);
					break;
				case EGraphicsOptions::Foliage:
					CurrentGameSettings->SetFoliageQuality(SettingValue);
					break;
				case EGraphicsOptions::Shading: 
					CurrentGameSettings->SetShadingQuality(SettingValue);
					break;
				case EGraphicsOptions::COUNT:
					// we do nothing
					break;
				}
			}
		}
		CurrentGameSettings->ApplySettings(false); 
	}
}

void UGraphicsPanel::ResetOptions()
{
	Super::ResetOptions();
	for (TPair<EGraphicsOptions, UOptionsCycler*>& Option :AllOptions)
	{
		Option.Value->UpdateSelection(DefaultSelectedIndex); 
	}
	ApplyOptions(); 
}

// this returns the current setting for the graphics option getting editted
int UGraphicsPanel::GetGraphicsOptionValue(EGraphicsOptions GraphicsOptions) const
{
	if (UGameUserSettings* CurrentGameSettings = UGameUserSettings::GetGameUserSettings())
	{
		switch (GraphicsOptions)
		{
		case EGraphicsOptions::Overall:
			return CurrentGameSettings->GetOverallScalabilityLevel();
		case EGraphicsOptions::GlobalIllumination:
			return CurrentGameSettings->GetGlobalIlluminationQuality();
		case EGraphicsOptions::Shadows:
			return CurrentGameSettings->GetShadowQuality();
		case EGraphicsOptions::AntiAliasing:
			return CurrentGameSettings->GetAntiAliasingQuality();
		case EGraphicsOptions::ViewDistance:
			return CurrentGameSettings->GetViewDistanceQuality();
		case EGraphicsOptions::TextureQuality:
			return CurrentGameSettings->GetTextureQuality();
		case EGraphicsOptions::Effects:
			return CurrentGameSettings->GetVisualEffectQuality();
		case EGraphicsOptions::Reflections:
			return CurrentGameSettings->GetReflectionQuality();
		case EGraphicsOptions::PostProcessing:
			return CurrentGameSettings->GetPostProcessingQuality();
		case EGraphicsOptions::Foliage: 
			return CurrentGameSettings->GetFoliageQuality();
		case EGraphicsOptions::Shading: 
			return CurrentGameSettings->GetShadingQuality();
		case EGraphicsOptions::COUNT:
			break;
		}
	}
	return 0;
}

// we loop all the settings and apply the same setting to all of them
void UGraphicsPanel::ChangeOverallValues(int SelectedIndex)
{
	for (TPair<EGraphicsOptions, UOptionsCycler*>& Pair :AllOptions)
	{
		if (Pair.Key != EGraphicsOptions::Overall)
		{
			Pair.Value->UpdateSelection(SelectedIndex);
		}
	}
}

void UGraphicsPanel::OnNonOverallOptionChanged(int32 SelectedIndex)
{
	OverallOptions->MarkAsCustom(); 
}

