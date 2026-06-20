// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "CreditsStructure.generated.h"

USTRUCT(BlueprintType)
struct FCredits : public FTableRowBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Category; 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Role;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FText> Names ;
};
