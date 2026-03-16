// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Projectiles/BaseProjectile.h"

// engine.GAS
#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "AbilitySystemInterface.h"
#include "GameplayCueManager.h"
//Engine
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"


ABaseProjectile::ABaseProjectile():Speed(2000)
{
	PrimaryActorTick.bCanEverTick = false;
	AutoReceiveInput = EAutoReceiveInput::Disabled; 
	
	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider")); 
	Collider->SetSphereRadius(20.f); 
	Collider->OnComponentBeginOverlap.AddDynamic(this, &ABaseProjectile::OnBeginOverlap); 
	Collider->OnComponentEndOverlap.AddDynamic(this, &ABaseProjectile::OnEndOverlap);
	Collider->OnComponentHit.AddDynamic(this, &ABaseProjectile::OnHit);
	RootComponent = Collider;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	
	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement")); 
	MovementComponent->ProjectileGravityScale = 0.f;
	MovementComponent->bAutoActivate = false;
	MovementComponent->bRotationFollowsVelocity = true;
}


void ABaseProjectile::SetProjectileDamage(const FGameplayEffectSpecHandle& InDamageEffect)
{
	EffectSpecHandle = InDamageEffect;
}



void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	FVector Direction = UKismetMathLibrary::GetDirectionUnitVector(GetActorLocation(), TargetLocation);
	MovementComponent->Velocity = Direction*Speed;
	MovementComponent->Activate();
	
	FGameplayCueParameters SpawnParameters;
	SpawnParameters.Location = GetActorLocation();
	
	UAbilitySystemGlobals::Get().GetGameplayCueManager()->HandleGameplayCue(this, SpawnCueTag, EGameplayCueEvent::Executed, SpawnParameters); 	
}

void ABaseProjectile::Destroyed()
{
	Super::Destroyed();
	
	FGameplayCueParameters SpawnParameters;
	SpawnParameters.Location = GetActorLocation();
	
	UAbilitySystemGlobals::Get().GetGameplayCueManager()->HandleGameplayCue(this, ImpactCueTag, EGameplayCueEvent::Executed, SpawnParameters);
}

void ABaseProjectile::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != GetInstigator()) // we check that the owning player isn't the one that was hit 
	{
		if (OtherActor->GetClass()->ImplementsInterface(UAbilitySystemInterface::StaticClass())) // we check if the hit actor has an asc
		{
			IAbilitySystemInterface* ASInterface = Cast<IAbilitySystemInterface>(OtherActor); 
			if (UAbilitySystemComponent* ASC = ASInterface->GetAbilitySystemComponent()) // we grab the ASC and lastly apply damage to the target
			{
				// we would do damage stuff here
				if (bFromSweep)
				EffectSpecHandle.Data.Get()->GetContext().AddHitResult(SweepResult,true); 
				ASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());  
			}
		}
		Destroy(); 
	}
}

void ABaseProjectile::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor != GetInstigator())
	{
		
	}
}

void ABaseProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,FVector NormalImpulse, const FHitResult& Hit)
{
	Destroy(); 
}

