// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OptionsPanel.h"
#include "AudioPanel.generated.h"

class UCustomAudioSlider;
/**
 * 
 */
UCLASS()
class COMMONUISETUP_API UAudioPanel : public UOptionsPanel
{
	GENERATED_UCLASS_BODY()
public: 
	
protected: 
	
	virtual void InitializeOptions() override;
	virtual void ApplyOptions() override;
	virtual void ResetOptions() override;
	
private:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category = "Options Panel|Widgets",  meta = (AllowPrivateAccess))
	TSubclassOf<UCustomAudioSlider> SliderWidgetClass;
	
	UPROPERTY()
	TMap<FName, UCustomAudioSlider*> VolumeSliders;
	
	float DefaultVolume; 

};
