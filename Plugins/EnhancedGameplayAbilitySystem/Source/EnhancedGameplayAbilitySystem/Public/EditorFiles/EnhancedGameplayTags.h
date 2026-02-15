#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

class UGameplayTagContainer;

struct ENHANCEDGAMEPLAYABILITYSYSTEM_API FEnhancedGameplayTags
{
public: 
	static const FEnhancedGameplayTags& Get(){return GameplayTags; }
	static void InitializeNativeTags(); 
	
public: 
	// Native inputs
	FGameplayTag Input_Move; 
	FGameplayTag Input_Aim;

	
	// Ability Inputs
	FGameplayTag Input_Dash; 
	
	// blocking movement tags
	
	FGameplayTag Gameplay_BlockMovement; 
	
protected:
	
	void AddAllTags(UGameplayTagsManager& Manager); 
	void AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagValue); 
	
private: 
	static FEnhancedGameplayTags GameplayTags; 
};
