// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Components/BaseSlider.h"
#include "CustomAudioSlider.generated.h"

class USoundClass;
class USoundMix;

/**
 * 
 */
UCLASS(Abstract, HideDropdown)
class COMMONUISETUP_API UCustomAudioSlider : public UBaseSlider
{
	GENERATED_UCLASS_BODY()
public:

	void InitializeSoundSettings(USoundClass* soundClass, USoundMix* soundMix); 
	
	virtual void UpdateValue(float NewValue)override;

private: 
	UPROPERTY()
	USoundClass* SoundClass;
	UPROPERTY()
	USoundMix* SoundMix;
	
};
