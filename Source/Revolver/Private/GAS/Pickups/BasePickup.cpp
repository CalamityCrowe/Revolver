
#include "GAS/Pickups/BasePickup.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "Characters/Player/RevolverPlayerCharacter.h"
#include "Components/CapsuleComponent.h"


ABasePickup::ABasePickup(): EffectClass(nullptr), EffectMagnitude(0.0f), MagnitudeTag(FGameplayTag::EmptyTag), bApplyOnlyToPlayer(true)
{
	PrimaryActorTick.bCanEverTick = false;
	
	Collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collider"));
	RootComponent = Collider;
	Collider->OnComponentBeginOverlap.AddDynamic(this, &ABasePickup::BeginOverlap); 
	
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
}

void ABasePickup::BeginPlay()
{
	Super::BeginPlay();
	if (bRandomMagnitude)
	{
		EffectMagnitude = FMath::RandRange(RandomMagnitudeMinimum, RandomMagnitudeMaximum); 
	}
}

void ABasePickup::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// we only want to run this if it is only the player, the function has been marked as virtual so we can override this to do "damage effects if we want to"
	if (bApplyOnlyToPlayer)
	{
		if (ARevolverPlayerCharacter* Player = Cast<ARevolverPlayerCharacter>(OtherActor))
		{
			// we grab the ability component from the actor that has overlapped with the pickup and validate it
			if (UAbilitySystemComponent* ASC =  UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Player))
			{
				GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green, FString::Printf(TEXT("Effect Magnitude %f"), EffectMagnitude)); 
				
				FGameplayEffectContextHandle ContextHandle = ASC->MakeEffectContext(); 
				ContextHandle.AddSourceObject(this);
				FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(EffectClass, 1.f, ContextHandle); 
				SpecHandle.Data->SetSetByCallerMagnitude(MagnitudeTag, EffectMagnitude);
				ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get()); 
				// todo: make a gameplaycue to burst heal or something 
				Destroy(); 
			}
		}
	}
}

