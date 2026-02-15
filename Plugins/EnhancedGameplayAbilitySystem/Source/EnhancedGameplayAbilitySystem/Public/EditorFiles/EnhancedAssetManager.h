// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "EnhancedAssetManager.generated.h"
 
/**
 * 
 */
UCLASS()
class ENHANCEDGAMEPLAYABILITYSYSTEM_API UEnhancedAssetManager : public UAssetManager
{
	GENERATED_BODY()
	
public: 
	UEnhancedAssetManager();
	
	static UEnhancedAssetManager& Get();
	
	virtual void StartInitialLoading() override;
};
