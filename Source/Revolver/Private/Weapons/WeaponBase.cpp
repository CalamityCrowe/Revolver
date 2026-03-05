// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/WeaponBase.h"
// engine

// Sets default values
AWeaponBase::AWeaponBase() : TraceRadius(50.f)
{
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>("Weapon Mesh");
	WeaponMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}


