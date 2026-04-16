// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GraphicsOptions.generated.h"

UENUM(Blueprintable)

enum class EGraphicsOptions : uint8
{
	Overall UMETA(DisplayName = "Overall"),
	GlobalIllumination UMETA(DisplayName = "Global Illumination"),
	Shadows UMETA(DisplayName = "Shadows"),
	AntiAliasing UMETA(DisplayName = "Anti Aliasing"),
	ViewDistance UMETA(DisplayName = "View Distance"),
	TextureQuality UMETA(DisplayName = "Texture Quality"),
	Effects UMETA(DisplayName = "Effects"),
	Reflections UMETA(DisplayName = "Reflections"),
	PostProcessing UMETA(DisplayName = "Post Processing"),
	Foliage UMETA(DisplayName = "Foliage"),
	Shading UMETA(DisplayName = "Shading"),
	COUNT UMETA (Hidden)
};
