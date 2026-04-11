// Fill out your copyright notice in the Description page of Project Settings.


#include "Gamefiles/RevolverGamemode.h"

#include "Enemy/Spawn/WaveManager.h"

ARevolverGamemode::ARevolverGamemode()
{
	
}

void ARevolverGamemode::BeginPlay()
{
	Super::BeginPlay();
	check(WaveManagerClass)
	WaveManagerRef = GetWorld()->SpawnActor<AWaveManager>(WaveManagerClass); 
	if (WaveManagerRef)
	{
		WaveManagerRef->InitializeWaveManager(); 
	}
}
