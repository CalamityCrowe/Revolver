// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "RevolverAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class REVOLVER_API URevolverAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:	
	URevolverAssetManager();
	
	static URevolverAssetManager& Get(); 
	
	virtual void StartInitialLoading() override;
};
