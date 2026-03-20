// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GAS/Data/AbilityCameraData.h"

#include "AbilityCameraManagerComponent.generated.h"


class UAbilitySystemComponent;
class UCameraComponent;
class USpringArmComponent;
class ARevolverPlayerCharacter;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class REVOLVER_API UAbilityCameraManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAbilityCameraManagerComponent();

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	void InitializeCameraSetup();

protected: 
	
	UFUNCTION()
	void OnTagChange(FGameplayTag GameplayTag, int NewCount);
	
	UAbilityCameraData* FindDataForTag(const FGameplayTag& Tag);

	void AbilityFinished(); 
	
private: 
	
	UPROPERTY()
	USpringArmComponent* CameraBoomRef;
	UPROPERTY()
	UCameraComponent* CameraRef; 
	UPROPERTY()
	ARevolverPlayerCharacter* PlayerRef;
	UPROPERTY()
	UAbilitySystemComponent* ASC; 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera Data", meta = (AllowPrivateAccess))
	FAbilityCameraSetups CameraSetups;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera|Transition", meta = (ClampMin = "0.0", UIMin = "0.0", AllowPrivateAccess = true))
	float TimerStep; 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera|Transition", meta = (AllowPrivateAccess))
	UCurveFloat* BlendCurve;
	
	TMap<FGameplayTag, FDelegateHandle> TagDelegateHandles;
	
	
	float TransitionTime;  // we will set this value when it starts the transition

	
	float ElapsedTime; 
	FVector StartSocket;
	float StartArmLength;
	float StartFOV; 
	
	FVector TargetSocket;
	float TargetArmLength;
	float TargetFOV; 
	
	FTimerHandle CameraLerpTimer; 
	FGameplayTag ActiveAbilityTag; 
private: 
	
	void LerpCamera();
	void SetStartingValues();
	void ResetCameraLerp();
	
	
};
