// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/WeaponBase.h"
// engine
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"


// Sets default values
AWeaponBase::AWeaponBase() : TraceRadius(50.f)
{
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>("Weapon Mesh");
	WeaponMesh->SetupAttachment(RootComponent);
}

void AWeaponBase::SpawnWeaponParticle()
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation
	(
		GetWorld(), 
		SpawnParticle, GetActorLocation(), 
		FRotator::ZeroRotator);
	WeaponMesh->SetVisibility(true);
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	// since all the weapons are spawned into the game on equip, we will do a particle to explode them in 
	WeaponMesh->SetVisibility(false);
}


