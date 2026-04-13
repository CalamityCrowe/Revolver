// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OptionsPanel.h"
#include "MenuFiles/GraphicsOptions.h"
#include "GraphicsPanel.generated.h"


class UOptionsCycler; 
/**
 * 
 */
UCLASS()
class COMMONUISETUP_API UGraphicsPanel : public UOptionsPanel
{
	GENERATED_UCLASS_BODY()
	
protected: 
	
	virtual void InitializeOptions() override;
	
private:
	int GetGraphicsOptionValue(EGraphicsOptions GraphicsOptions)const ; 
	
	UFUNCTION()
	virtual void ChangeOverallValues(int SelectedIndex); 
	UFUNCTION()
	virtual void OnNonOverallOptionChanged(int32 SelectedIndex); 
	
	UPROPERTY()
	TObjectPtr<UOptionsCycler> OverallOptions; 
	
	UPROPERTY()
	TArray<TObjectPtr<UOptionsCycler>> OtherOptions;
	
};
