// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OptionsPanel.h"
#include "MenuFiles/GraphicsOptions.h"
#include "GraphicsPanel.generated.h"

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
	
};
