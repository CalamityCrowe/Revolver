// fill out copyright stuff here


#include "Weapons/MeleeWeapon.h"

#include "AbilitySystemComponent.h"
#include "Kismet/KismetSystemLibrary.h"


AMeleeWeapon::AMeleeWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
	
	TraceStart = CreateDefaultSubobject<USceneComponent>("Trace Start");
	TraceStart->SetupAttachment(GetMesh());
	
	TraceEnd = CreateDefaultSubobject<USceneComponent>("Trace End");
	TraceEnd->SetupAttachment(GetMesh());
}


void AMeleeWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMeleeWeapon::HitScan()
{
	Super::HitScan();
	FVector StartLocation = TraceStart->GetComponentLocation(); 
	FVector EndLocation = TraceEnd->GetComponentLocation();
	
	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(GetInstigator()); 
	
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes; 
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
	
	TArray<FHitResult> HitResults;
	
	bool bHit = UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(), StartLocation, EndLocation,TraceRadius,ObjectTypes,
	false,IgnoreActors,EDrawDebugTrace::ForDuration,HitResults,true,FLinearColor::Red,FLinearColor::Green,1); 
	for (FHitResult Hit : HitResults)
	{
		if (!Hit.GetActor())continue; 
		if (UAbilitySystemComponent* ASC =  Hit.GetActor()->GetComponentByClass<UAbilitySystemComponent>())
		{
			if (!HitActors.Contains(Hit.GetActor()))
			{
				HitActors.AddUnique(Hit.GetActor());
				
				// we copy the spec from the const version so we can safely give it the hit location 
				FGameplayEffectSpec SpecCopy = *EffectSpecHandle.Data.Get(); 
				SpecCopy.GetContext().AddHitResult(Hit,true); 
				
				ASC->ApplyGameplayEffectSpecToSelf(SpecCopy);
			}
		}
	}
}

void AMeleeWeapon::HitScanStart(const FGameplayEffectSpecHandle& InEffectSpecHandle)
{
	EffectSpecHandle = InEffectSpecHandle;
	HitActors.Empty(); 
	GetWorldTimerManager().SetTimer(HitScanTimer,this, &AMeleeWeapon::HitScan,TraceTimer,true); 
}

void AMeleeWeapon::HitScanEnd()
{
	GetWorldTimerManager().ClearTimer(HitScanTimer);
}

