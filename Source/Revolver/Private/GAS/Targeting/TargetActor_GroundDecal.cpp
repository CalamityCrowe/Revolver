// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Targeting/TargetActor_GroundDecal.h"

#include "Kismet/GameplayStatics.h"

void ATargetActor_GroundDecal::BeginPlay()
{
	Super::BeginPlay();
	
	UGameplayStatics::SpawnDecalAttached(
		DecalMaterial, FVector(256.f,DecalSize,DecalSize),
		GetRootComponent(),FName(""),
		FVector(),FRotator(0,-90,0)); 
}
