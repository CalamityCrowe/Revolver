// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Pages/GraphicsPanel.h"
#include "Data/GraphicsSettingsTable.h"
#include "Components/ScrollBox.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Components/OptionsCycler.h"

UGraphicsPanel::UGraphicsPanel(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	
}

void UGraphicsPanel::InitializeOptions()
{
	Super::InitializeOptions();
	if (OptionsTable && OptionsCycleClass)
	{
		TArray<FName> RowNames = OptionsTable->GetRowNames();
		for (FName RowName : RowNames)
		{
			FGraphicsConfig* RowData = OptionsTable->FindRow<FGraphicsConfig>(RowName, TEXT(""));
			if (RowData)
			{
				UOptionsCycler* OC = CreateWidget<UOptionsCycler>(GetWorld(),OptionsCycleClass);
				FText EnumToText = StaticEnum<EGraphicsOptions>()->GetDisplayNameTextByValue(static_cast<int64>(RowData->GraphicsOptionType));
				
				
				TArray<FText> OptionValues;
				RowData->Options.GenerateValueArray(OptionValues);

				TArray<int> OptionsKeys;
				RowData->Options.GenerateKeyArray(OptionsKeys);
				int DefaultGraphicsOption = OptionsKeys.Find(GetGraphicsOptionValue(RowData->GraphicsOptionType));
				
				
				OC->InitializeOption(EnumToText,OptionValues,DefaultGraphicsOption);
				OC->SetPadding(FMargin(0,0,0,10));

				SB_OptionsScroll->AddChild(OC);
			}
		}
	}
}

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
