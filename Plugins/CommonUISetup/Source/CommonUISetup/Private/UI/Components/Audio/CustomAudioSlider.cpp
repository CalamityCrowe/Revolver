// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Components/Audio/CustomAudioSlider.h"

#include "Kismet/GameplayStatics.h"

UCustomAudioSlider::UCustomAudioSlider(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
	
}

void UCustomAudioSlider::InitializeSoundSettings(USoundClass* soundClass, USoundMix* soundMix)
{
	SoundClass = soundClass;
	SoundMix = soundMix;
}

// we just add a final step to make sure that the volume is set correctly in relation to the slider 
void UCustomAudioSlider::UpdateValue(float NewValue)
{
	Super::UpdateValue(NewValue);
	if (SoundClass && SoundMix)
	{
		UGameplayStatics::SetSoundMixClassOverride(GetWorld(), SoundMix, SoundClass, NewValue, 1, 0.1f);
		UGameplayStatics::PushSoundMixModifier(GetWorld(), SoundMix); 
	}
}
