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
	FGameplayTag Input_EquipSword;
	
	
	// Ability Inputs
	FGameplayTag Input_Dash; 
	FGameplayTag Input_MeleeAttack; 
	
	
	// blocking movement tags
	
	FGameplayTag Gameplay_BlockMovement; 
	FGameplayTag Gameplay_Death; 
	
protected:
	
	void AddAllTags(UGameplayTagsManager& Manager); 
	void AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagValue); 
	
private: 
	static FEnhancedGameplayTags GameplayTags; 
};
