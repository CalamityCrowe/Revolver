// Fill out your copyright notice in the Description page of Project Settings.


#include "EditorFiles/RevolverGameplayTags.h"
#include "GameplayTagsManager.h"

FRevolverGameplayTags FRevolverGameplayTags::GameplayTags;


void FRevolverGameplayTags::InitializeNativeTags()
{
	UGameplayTagsManager& Manager = UGameplayTagsManager::Get(); 
	GameplayTags.AddAllTags(Manager); 
	Manager.DoneAddingNativeTags(); 
}

void FRevolverGameplayTags::AddAllTags(UGameplayTagsManager& Manager)
{
	FEnhancedGameplayTags::AddAllTags(Manager);
	
	AddTag(Input_EquipSword, "NativeInput.EquipSword", "Equip Sword");
	AddTag(Input_LockOn, "NativeInput.LockOn", "Lock On");
	
	// Ability Inputs
	AddTag(Input_Dash,"GameplayAbility.Movement.Dash","Interaction"); 
	AddTag(Input_MeleeAttack,"GameplayAbility.Attack.Sword","Melee Attack");
	AddTag(Input_CharacterAbility_1, "GameplayAbility.Character.First", "Character Ability");
	
}
