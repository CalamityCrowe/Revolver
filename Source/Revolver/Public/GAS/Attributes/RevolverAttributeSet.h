// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/Attributes/EnhancedAttributeSet.h"
#include "RevolverAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class REVOLVER_API URevolverAttributeSet : public UEnhancedAttributeSet
{
	GENERATED_BODY()
public: 
	URevolverAttributeSet(); 
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS_BASIC(URevolverAttributeSet, Mana); 
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData MaxMana; 
	ATTRIBUTE_ACCESSORS_BASIC(URevolverAttributeSet, MaxMana);
protected: 
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
private: 
	FGameplayTag HitDirectionFrontTag;
	FGameplayTag HitDirectionBackTag;
	FGameplayTag HitDirectionRightTag;
	FGameplayTag HitDirectionLeftTag;
	
};
