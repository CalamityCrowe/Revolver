// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Pages/GraphicsPanel.h"
#include "Data/GraphicsSettingsTable.h"
#include "Components/ScrollBox.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Components/OptionsCycler.h"

UGraphicsPanel::UGraphicsPanel(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	SetIsFocusable(true);
}

void UGraphicsPanel::InitializeOptions()
{
	// calls the parent function to clear the selection box
	Super::InitializeOptions();
	
	// we invalidate these here so they are empty/null for using again
	OverallOptions = nullptr;
	OtherOptions.Empty();
	
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
				UOptionsCycler* OC = CreateWidget<UOptionsCycler>(GetWorld(),OptionsCycleClass);
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
				OC->SetPadding(FMargin(0,0,0,10));

				// we check if it is the overall setting and if so, we set the reference to the overall options
				if (RowData->GraphicsOptionType == EGraphicsOptions::Overall)
				{
					OverallOptions = OC;
				}
				else
				{
					OtherOptions.AddUnique(OC);
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

// this returns the current setting for the graphics option getting editted
int UGraphicsPanel::GetGraphicsOptionValue(EGraphicsOptions GraphicsOptions) const
{
	if (UGameUserSettings* CurrentGameSettings = UGameUserSettings::GetGameUserSettings())
	{
		switch (GraphicsOptions)
		{
		case EGraphicsOptions::Overall:
			return CurrentGameSettings->GetOverallScalabilityLevel();
			break;
		case EGraphicsOptions::GlobalIllumination:
			return CurrentGameSettings->GetGlobalIlluminationQuality();
			break;
		case EGraphicsOptions::Shadows:
			return CurrentGameSettings->GetShadowQuality();
			break;
		case EGraphicsOptions::AntiAliasing:
			return CurrentGameSettings->GetAntiAliasingQuality();
			break;
		case EGraphicsOptions::ViewDistance:
			return CurrentGameSettings->GetViewDistanceQuality();
			break;
		case EGraphicsOptions::TextureQuality:
			return CurrentGameSettings->GetTextureQuality();
			break;
		case EGraphicsOptions::Effects:
			return CurrentGameSettings->GetVisualEffectQuality();
			break;
		case EGraphicsOptions::Reflections:
			return CurrentGameSettings->GetReflectionQuality();
			break;
		case EGraphicsOptions::PostProcessing:
			return CurrentGameSettings->GetPostProcessingQuality();
			break;
		case EGraphicsOptions::COUNT:
			break;
		}
	}
	return 0;
}


void UGraphicsPanel::ChangeOverallValues(int SelectedIndex)
{
	for (UOptionsCycler* Option: OtherOptions) // loops through all the other options and makes them the index that has been passed in
	{
		Option->UpdateSelection(SelectedIndex);
	}
}

void UGraphicsPanel::OnNonOverallOptionChanged(int32 SelectedIndex)
{
	OverallOptions->MarkAsCustom(); 
}

