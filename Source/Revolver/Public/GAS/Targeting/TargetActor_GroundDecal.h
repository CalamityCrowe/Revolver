// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor_GroundTrace.h"
#include "TargetActor_GroundDecal.generated.h"

/**
 * 
 */
UCLASS()
class REVOLVER_API ATargetActor_GroundDecal : public AGameplayAbilityTargetActor_GroundTrace
{
	GENERATED_BODY()
public:
	ATargetActor_GroundDecal(); 
	
	virtual void BeginPlay() override;
	
protected: 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties|Materials")
	TObjectPtr<UMaterialInterface> DecalMaterial;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties|Materials")
	float DecalSize;
};
