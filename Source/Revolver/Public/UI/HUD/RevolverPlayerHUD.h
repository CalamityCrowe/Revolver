// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"

#include "RevolverPlayerHUD.generated.h"

class URevolverPlayerHealth;
/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class REVOLVER_API URevolverPlayerHUD : public UCommonUserWidget
{
	GENERATED_UCLASS_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	
protected: 
	UPROPERTY(meta = (BindWidgetOptional), Category = "Revolver|Player Stats", BlueprintReadWrite)
	TObjectPtr<URevolverPlayerHealth> HealthBar; 
	
};
