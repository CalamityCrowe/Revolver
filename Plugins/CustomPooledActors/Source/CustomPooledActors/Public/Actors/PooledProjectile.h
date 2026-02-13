// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PooledActor.h"
#include "PooledProjectile.generated.h"

class UProjectileMovementComponent;
class UStaticMeshComponent;
class USphereComponent;

UCLASS(Abstract, Hidden)
class CUSTOMPOOLEDACTORS_API APooledProjectile : public APooledActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APooledProjectile();
	
	virtual void SetInUse(bool InUse) override;
	
	UStaticMeshComponent* GetMesh() const {return Mesh; }
	UProjectileMovementComponent* GetProjectileMovement() const{return ProjectileMovement; };
	USphereComponent* GetCollider() const {return Collider; }
	
private: 
	
	UPROPERTY(EditDefaultsOnly, BLueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> Mesh; 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	TObjectPtr<USphereComponent> Collider;
	
	
	float Speed; 
	float Range; 
	
	UFUNCTION() 
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult); 
};
