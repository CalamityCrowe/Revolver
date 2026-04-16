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

void UCustomAudioSlider::UpdateValue(float NewValue)
{
	Super::UpdateValue(NewValue);
	if (SoundClass && SoundMix)
	{
		UGameplayStatics::SetSoundMixClassOverride(GetWorld(), SoundMix, SoundClass, NewValue, 1, 0.1f);
		UGameplayStatics::PushSoundMixModifier(GetWorld(), SoundMix); 
	}
}
