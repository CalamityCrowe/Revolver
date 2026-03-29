// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Targeting/TargetActor_GroundDecal.h"

#include "Kismet/GameplayStatics.h"

ATargetActor_GroundDecal::ATargetActor_GroundDecal(): DecalMaterial(nullptr), DecalSize(0.0f)
{
	
}

void ATargetActor_GroundDecal::BeginPlay()
{
	Super::BeginPlay();
	
	UGameplayStatics::SpawnDecalAttached(
		DecalMaterial, FVector(256.f,DecalSize,DecalSize),
		GetRootComponent(),FName(""),
		FVector(),FRotator(-90,0,0)); 
}
