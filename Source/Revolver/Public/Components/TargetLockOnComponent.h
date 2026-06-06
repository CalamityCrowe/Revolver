// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "TargetLockOnComponent.generated.h"


class UTargetingSubsystem;
class ARevolverPlayerCharacter;
class UTargetingPreset;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class REVOLVER_API UTargetLockOnComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTargetLockOnComponent();

	UFUNCTION(BlueprintCallable, Category = "Target Lock-On") 
	void ToggleLockOn(); 
	
	UFUNCTION(BlueprintCallable, Category = "Target Lock-On")
	void SwitchTarget(float AxisValue); // in the context of this code. Axis value is refering to the X axis of the right stick of the gamepad/ left to right movement of the mouse 
	
	
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	void StartLockOn();
	
	void StopLockOn(); 
	
	
	AActor* GetClosestTarget(const TArray<AActor*>& Targets) const ; 
	
	float CloseToCentre(const AActor* Target) const;
	
	void AdjustCamera();
	FRotator GetLockOnCameraRotation(const AActor* Target) const;
	
	bool IsStillInRange() const; 
	bool StillHasLOS() const;
	
	
private: 
	
	UPROPERTY()
	ARevolverPlayerCharacter* OwningPlayer; 
	
	UPROPERTY()
	FTimerHandle LockOnTimer; 
	
	UPROPERTY(EditDefaultsOnly, Category = "Targetting|Targetting Data", meta = (AllowPrivateAccess = true))
	TObjectPtr<UTargetingPreset> TargetingPreset; 
	UPROPERTY(EditDefaultsOnly, Category = "Targetting|Lock On", meta = (AllowPrivateAccess = true, ClampMin = 0.f, UIMin= 0.0f))
	float LockOnScale; // this will be what we use to decide where about on the Z axis we should be looking	
		
	UPROPERTY(EditDefaultsOnly, Category = "Targetting|Lock On", meta = (AllowPrivateAccess = true, ClampMin = 0.f, UIMin= 0.0f))
	float InterpSpeed; // this is what we will use to scale how fast we turn the camera to look at the target 
	
	UPROPERTY(EditDefaultsOnly, Category = "Targetting|Lock On", meta = (AllowPrivateAccess = true, ClampMin = 0.0f, UIMin= 0.0f))
	float LockOnRadius; 
	
	
	// we use these values to cache references in the components itself
	bool bLockedOn;
	UPROPERTY()
	AActor* CurrentTarget; 
	float InputAxis;
	UPROPERTY()
	UTargetingSubsystem* TargetingSubsystem; 
	
	
	UFUNCTION()
	virtual void OnLockOnComplete(FTargetingRequestHandle TargetingHandle); 
	
	UFUNCTION()
	virtual void OnSwitchComplete(FTargetingRequestHandle TargetingHandle); 
	
};
