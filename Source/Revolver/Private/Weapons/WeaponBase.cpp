// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/WeaponBase.h"


// Sets default values
AWeaponBase::AWeaponBase() : TraceRadius(50.f)
{
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>("Weapon Mesh");
	WeaponMesh->SetupAttachment(RootComponent);
	
	SpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	SpawnPoint->SetupAttachment(WeaponMesh);
}


FVector AWeaponBase::GetSpawnPoint() const
{
	return SpawnPoint->GetComponentLocation(); 
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();

}


