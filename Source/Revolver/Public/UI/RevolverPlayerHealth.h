// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/EnhancedPlayerHealth.h"
#include "RevolverPlayerHealth.generated.h"

/**
 * 
 */
UCLASS()
class REVOLVER_API URevolverPlayerHealth : public UEnhancedPlayerHealth
{
	GENERATED_UCLASS_BODY()
public: 
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	
protected: 
	virtual void UpdateHealth(const FOnAttributeChangeData& Data) override;
};
