#include "EditorFiles/EnhancedGameplayTags.h"
#include "GameplayTagsManager.h"

FEnhancedGameplayTags FEnhancedGameplayTags::GameplayTags;

void FEnhancedGameplayTags::InitializeNativeTags()
{
	UGameplayTagsManager& Manager = UGameplayTagsManager::Get(); 
	GameplayTags.AddAllTags(Manager); 
	Manager.DoneAddingNativeTags(); 
}

void FEnhancedGameplayTags::AddAllTags(UGameplayTagsManager& Manager)
{
	// Native Inputs
	AddTag(Input_Move, "NativeInput.Move", "Movement Inputs"); 
	AddTag(Input_Aim, "NativeInput.Aim", "Aim Inputs");
	AddTag(Input_EquipSword, "NativeInput.EquipSword", "Equip Sword");
	AddTag(Input_LockOn, "NativeInput.LockOn", "Lock On");
	
	// Ability Inputs
	AddTag(Input_Dash,"GameplayAbility.Movement.Dash","Interaction"); 
	AddTag(Input_MeleeAttack,"GameplayAbility.Attack.Sword","Melee Attack");
	AddTag(Input_CharacterAbility_1, "GameplayAbility.Character.First", "Character Ability");
	
	AddTag(Gameplay_Death, "State.Dead", "Dead");
	
}

void FEnhancedGameplayTags::AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagValue)
{
	OutTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(TagName), FString(TEXT("(Native )"))+FString(TagValue));
}
