// Fill out your copyright notice in the Description page of Project Settings.


#include "EditorFiles/RevolverAssetManager.h"
#include "AbilitySystemGlobals.h"
#include "EditorFiles/RevolverGameplayTags.h"


URevolverAssetManager::URevolverAssetManager()
{
}

URevolverAssetManager& URevolverAssetManager::Get()
{
	check(GEngine); 
	
	if (URevolverAssetManager* Singleton = Cast<URevolverAssetManager>(GEngine->AssetManager))
	{
		return *Singleton; 
	}
	
	UE_LOG(LogTemp, Fatal, TEXT("Invalid AssetManager ClassName in DefualtEngine.ini.")); 
	
	return *NewObject<URevolverAssetManager>(); 
}

void URevolverAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	
	FRevolverGameplayTags::InitializeNativeTags(); 
	UAbilitySystemGlobals::Get().InitGlobalData(); 
}
