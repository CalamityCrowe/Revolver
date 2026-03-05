// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/InstrumentWeapon.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "GAS/EnhancedAbilitySystemComponent.h"
#include "Kismet/KismetSystemLibrary.h"

AInstrumentWeapon::AInstrumentWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AInstrumentWeapon::HitScanStart(const FGameplayEffectSpecHandle& InEffectSpecHandle)
{
	Super::HitScanStart(InEffectSpecHandle);
	EffectSpecHandle = InEffectSpecHandle; 
	//UserSpecHandle = InUserEffectSpecHandle;
	HitScan(); 
}

void AInstrumentWeapon::HitScan()
{
	Super::HitScan();
	FVector StartLocation = this->GetActorLocation();
	FVector EndLocation = GetInstigator()->GetActorLocation();
	
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
	
	TArray<FHitResult> HitResults;
	
	bool bHit = UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(),StartLocation,EndLocation,TraceRadius, ObjectTypes,
		false,TArray<AActor*>(),EDrawDebugTrace::ForDuration,HitResults,true, FLinearColor::Yellow,FLinearColor::Green,1); 
	if (bHit)
	{
		for (FHitResult& Hit: HitResults)
		{
			if (!Hit.GetActor())continue; 
			if (Hit.GetActor()->GetClass()->ImplementsInterface(UAbilitySystemInterface::StaticClass()))
			{	
				IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(Hit.GetActor()); 
				if (UAbilitySystemComponent* ASC = ASCInterface->GetAbilitySystemComponent())
				{
					if (!HitActors.Contains(Hit.GetActor()))
					{
						HitActors.AddUnique(Hit.GetActor());
						if (Hit.GetActor() == GetInstigator())
						{
							ASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get()); // the target gets a full effect from the bell
						}else
						{
							ASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get()); // the target gets a full effect from the bell
						} 
					}
				}
			}
		}
	}
}

void AInstrumentWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}



