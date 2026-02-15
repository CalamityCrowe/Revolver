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
	
	// Ability Inputs
	AddTag(Input_Dash,"GameplayAbility.Movement.Dash","Interaction"); 
	
	
}

void FEnhancedGameplayTags::AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagValue)
{
	OutTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(TagName), FString(TEXT("(Native )"))+FString(TagValue));
}
