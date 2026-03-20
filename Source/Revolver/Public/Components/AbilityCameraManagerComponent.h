// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AbilityCameraManagerComponent.generated.h"


class ARevolverPlayerCharacter;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class REVOLVER_API UAbilityCameraManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAbilityCameraManagerComponent();
	
	virtual void BeginPlay() override;
	
	void IntializeCameraSetup(); 

protected: 
	
	UFUNCTION()
	void OnAbility1CameraLerp();
	
	UFUNCTION()
	void AbilityFinished(); 
	
private: 
	
	void LerpCamera();
	
	UPROPERTY()
	USpringArmComponent* CameraBoomRef;
	UPROPERTY()
	ARevolverPlayerCharacter* PlayerRef;
	
	FVector StartSocket;
	float StartArmLength;
	
	FVector TargetSocket;
	float TargetArmLength;
	
	FVector DefaultSocket; 
	float DefaultArmLength;
	
	FTimerHandle CameraLerpTimer; 
	
};
