// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RevolverGamemode.generated.h"

class AWaveManager;
/**
 * 
 */
UCLASS()
class REVOLVER_API ARevolverGamemode : public AGameModeBase
{
	GENERATED_BODY()
	
public: 
	ARevolverGamemode(); 
	
	virtual void BeginPlay() override;
	
private: 
	UPROPERTY()
	AWaveManager* WaveManagerRef;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Classes, NoClear, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AWaveManager> WaveManagerClass;
};
