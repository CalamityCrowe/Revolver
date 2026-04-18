// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/ExtendedUserSettingsSubsystem.h"

TArray<FMonitorInfo> UExtendedUserSettingsSubsystem::GetAllMonitorInfo() const
{
	FDisplayMetrics DisplayMetrics;
	FDisplayMetrics::RebuildDisplayMetrics(DisplayMetrics); 
	return DisplayMetrics.MonitorInfo; 
}
