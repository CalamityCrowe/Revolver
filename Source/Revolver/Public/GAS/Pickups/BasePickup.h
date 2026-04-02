// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "BasePickup.generated.h"

class UGameplayEffect;
class UCapsuleComponent;

UCLASS()
class REVOLVER_API ABasePickup : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABasePickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected: 
	
	UPROPERTY(EditDefaultsOnly, Category = "Abilities|Effects")
	TSubclassOf<UGameplayEffect> EffectClass; 
	
	UPROPERTY(EditDefaultsOnly, Category = "Abilities|Effects", meta = (EditorOnly))
	bool bRandomMagnitude; 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities|Effects", meta = (EditCondition = "bRandomMagnitude",EditConditionHides, UIMin = 0.0f,ClampMin = 0.0f))
	float RandomMagnitudeMinimum; 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities|Effects", meta = (EditCondition = "bRandomMagnitude",EditConditionHides, UIMin = 0.0f,ClampMin = 0.0f))
	float RandomMagnitudeMaximum;
	
	UPROPERTY(EditDefaultsOnly, Category = "Abilities|Effects", meta = (AllowPrivateAccess,EditCondition = "!bRandomMagnitude",ClampMin = 0.0f, UIMin = 0.0f))
	float EffectMagnitude;
	
	UPROPERTY(EditDefaultsOnly, Category = "Abilities|Effects")
	FGameplayTag MagnitudeTag; 
	
	UPROPERTY(EditDefaultsOnly, Category = "Abilities|Effects")
	bool bApplyOnlyToPlayer; 
	
private: 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess))
	TObjectPtr<UStaticMeshComponent> Mesh; 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess))
	TObjectPtr<UCapsuleComponent> Collider; 
	
	UFUNCTION()
	virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult); 
};
