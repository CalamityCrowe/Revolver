// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/ExtendedUserSettingsSubsystem.h"
#include "Widgets/SWindow.h"

TArray<FMonitorInfo> UExtendedUserSettingsSubsystem::GetAllMonitorInfo() const
{
	FDisplayMetrics DisplayMetrics;
	FDisplayMetrics::RebuildDisplayMetrics(DisplayMetrics); 
	return DisplayMetrics.MonitorInfo; 
}

void UExtendedUserSettingsSubsystem::SetActiveDisplay(const FString& DisplayID)
{
	for (const FMonitorInfo& MonitorInfo : GetAllMonitorInfo())
	{
		if (MonitorInfo.ID == DisplayID)
		{
			UE_LOG(LogTemp,Log, TEXT("Setting active Display to ID: %s"), *DisplayID)
			
			FVector2D NewWindowPosition(MonitorInfo.WorkArea.Left, MonitorInfo.WorkArea.Top);
			if (GEngine && GEngine->GameViewport)
			{
				if (TSharedPtr<SWindow> GWindow = GEngine->GameViewport->GetWindow())
				{
					GWindow->MoveWindowTo(NewWindowPosition);
				}
			}
			
		}
	}
}
