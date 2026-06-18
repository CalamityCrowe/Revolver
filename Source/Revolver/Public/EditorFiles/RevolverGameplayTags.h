// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorFiles/EnhancedGameplayTags.h"

/**
 * 
 */
struct REVOLVER_API FRevolverGameplayTags: public FEnhancedGameplayTags
{
	
	
public: 
	
	static const FRevolverGameplayTags& Get() {return GameplayTags;};
	static void InitializeNativeTags(); 
	
public: 
	// Native Inputs
	FGameplayTag Input_EquipSword;
	FGameplayTag Input_LockOn; 
	
		
	// Ability Inputs
	FGameplayTag Input_Dash; 
	FGameplayTag Input_MeleeAttack; 
	FGameplayTag Input_CharacterAbility_1;
	
	// blocking movement tags
	FGameplayTag Gameplay_BlockMovement; 

	
protected:
	
	virtual void AddAllTags(UGameplayTagsManager& Manager) override;
	
private: 
	static FRevolverGameplayTags GameplayTags; 
};
