#pragma once 

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "AudioSettingsTable.generated.h"

USTRUCT()
struct FAudioConfig : public FTableRowBase 
{
    GENERATED_BODY()
    public: 
    UPROPERTY(EditAnywhere)
    TObjectPtr<USoundClass> SoundClass;
    UPROPERTY(EditAnywhere)
    TObjectPtr<USoundMix> SoundClassMix; 
    UPROPERTY(EditAnywhere)
    float DefaultVolume; 
    UPROPERTY(EditAnywhere)
    FText SoundClassName;
    
    FAudioConfig(): SoundClass(nullptr), SoundClassMix(nullptr), DefaultVolume(1.0f)
    {
        SoundClassName = FText::FromString("");
    }; 
}; 

