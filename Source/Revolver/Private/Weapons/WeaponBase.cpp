// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/WeaponBase.h"
// engine
#include "AbilitySystemComponent.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
AWeaponBase::AWeaponBase()
{
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>("Weapon Mesh");
	WeaponMesh->SetupAttachment(RootComponent);
	
	TraceStart = CreateDefaultSubobject<USceneComponent>("Trace Start");
	TraceStart->SetupAttachment(WeaponMesh);
	
	TraceEnd = CreateDefaultSubobject<USceneComponent>("Trace End");
	TraceEnd->SetupAttachment(WeaponMesh);
}



// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWeaponBase::HitScan()
{
	FVector StartLocation = TraceStart->GetComponentLocation(); 
	FVector EndLocation = TraceEnd->GetComponentLocation();
	
	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(GetInstigator()); 
	
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes; 
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
	
	TArray<FHitResult> HitResults;
	
	bool bHit = UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(), StartLocation, EndLocation,TraceRadius,ObjectTypes,
	false,IgnoreActors,EDrawDebugTrace::ForDuration,HitResults,true); 
	for (FHitResult Hit : HitResults)
	{
		if (!Hit.GetActor())continue; 
		if (UAbilitySystemComponent* ASC =  Hit.GetActor()->GetComponentByClass<UAbilitySystemComponent>())
		{
			if (!HitActors.Contains(Hit.GetActor()))
			{
				HitActors.AddUnique(Hit.GetActor());
				ASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
			}
		}
	}
}

// the activation of the montage it will play an event and the event will call this from the weapon reference. 
void AWeaponBase::HitScanStart(const FGameplayEffectSpecHandle& InEffectSpecHandle)
{
	EffectSpecHandle = InEffectSpecHandle;
	HitActors.Empty(); 
	GetWorldTimerManager().SetTimer(HitScanTimer,this, &AWeaponBase::HitScan,TraceTimer,true); 
}

// same idea but with it waiting for the ability to end 
void AWeaponBase::HitScanEnd()
{
	GetWorldTimerManager().ClearTimer(HitScanTimer); 
}


