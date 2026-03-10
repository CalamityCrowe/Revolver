// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Projectiles/BaseProjectile.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
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
	RootComponent = Collider;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	
	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement")); 
	MovementComponent->ProjectileGravityScale = 0.f;
	MovementComponent->bAutoActivate = false;
	MovementComponent->bRotationFollowsVelocity = true;
}


void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	FVector Direction = UKismetMathLibrary::GetDirectionUnitVector(GetActorLocation(), TargetLocation);
	MovementComponent->Velocity = Direction*Speed;
	MovementComponent->Activate();
}

void ABaseProjectile::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != GetInstigator())
	{
		if (OtherActor->GetClass()->ImplementsInterface(UAbilitySystemInterface::StaticClass()))
		{
			IAbilitySystemInterface* ASInterface = Cast<IAbilitySystemInterface>(OtherActor); 
			if (UAbilitySystemComponent* ASC = ASInterface->GetAbilitySystemComponent())
			{
				// we would do damage stuff here
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

