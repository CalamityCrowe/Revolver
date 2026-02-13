// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/PooledProjectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

APooledProjectile::APooledProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
	
	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	Collider->InitSphereRadius(15.0f);
	Collider->OnComponentBeginOverlap.AddDynamic(this, &APooledProjectile::OnOverlapBegin); 
	RootComponent = Collider;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
}

void APooledProjectile::SetInUse(const bool InUse)
{
	Super::SetInUse(InUse);
	if (InUse)
	{
		
	}else
	{
		ProjectileMovement->Velocity = FVector::ZeroVector;
	}
}

void APooledProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != GetInstigator())
	{
		SetInUse(false);
	}
}


