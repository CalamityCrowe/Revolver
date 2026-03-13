// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Attributes/RevolverAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "Characters/CharacterBase.h"
#include "Player/RevolverPlayerController.h"

URevolverAttributeSet::URevolverAttributeSet():Mana(50), MaxMana(50 )
{
	HitDirectionFrontTag = FGameplayTag::RequestGameplayTag(FName("Effect.HitReact.Front"));
	HitDirectionBackTag = FGameplayTag::RequestGameplayTag(FName("Effect.HitReact.Back"));
	HitDirectionRightTag = FGameplayTag::RequestGameplayTag(FName("Effect.HitReact.Right"));
	HitDirectionLeftTag = FGameplayTag::RequestGameplayTag(FName("Effect.HitReact.Left"));
}

void URevolverAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
}

void URevolverAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	/// we do all the typical 
	FGameplayEffectContextHandle Context = Data.EffectSpec.GetContext();
	UAbilitySystemComponent* Source = Context.GetOriginalInstigatorAbilitySystemComponent();
	const FGameplayTagContainer& SourceTags = *Data.EffectSpec.CapturedSourceTags.GetAggregatedTags();
	FGameplayTagContainer SpecAssetTags;
	Data.EffectSpec.GetAllAssetTags(SpecAssetTags);
	
	AActor* TargetActor = nullptr; 
	AController* TargetController = nullptr; 
	ACharacterBase* TargetCharacter= nullptr;
	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get(); 
		TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		TargetCharacter = Cast<ACharacterBase>(TargetActor);
	}
	
	AActor* SourceActor = nullptr; 
	AController* SourceController = nullptr; 
	ACharacterBase* SourceCharacter= nullptr;
	
	if (Source && Source->AbilityActorInfo.IsValid() && Source->AbilityActorInfo->AvatarActor.IsValid())
	{
		SourceActor = Source->AbilityActorInfo->AvatarActor.Get();
		SourceController = Source->AbilityActorInfo->PlayerController.Get();
		if (SourceController == nullptr && SourceActor != nullptr)
		{
			if (APawn* Pawn = Cast<APawn>(SourceActor))
			{
				SourceController = Pawn->GetController();
			}
		}
		
		if (SourceController)
		{
			SourceCharacter = Cast<ACharacterBase>(SourceController->GetPawn()); 
		}
		else
		{
			SourceCharacter = Cast<ACharacterBase>(SourceActor);
		}
		
		if (Context.GetEffectCauser())
		{
			SourceActor = Context.GetEffectCauser();
		}
	}
	
	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		const float LocalDamage = GetDamage(); 
GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::SanitizeFloat(LocalDamage));
		SetDamage(0); 
		
		if (LocalDamage > 0.0f)
		{
			bool bWasAlive = true;
			
			if (TargetCharacter)
			{
				bWasAlive = TargetCharacter->IsAlive();
			}
			
			const float NewHealth = GetHealth() - LocalDamage;
			SetHealth(FMath::Clamp(NewHealth, 0, GetMaxHealth()));
			
			if (TargetCharacter && bWasAlive)
			{
				if (const FHitResult* Hit = Data.EffectSpec.GetContext().GetHitResult())
				{
					EHitReactDirection HitDirection = TargetCharacter->GetHitReactDirection(Data.EffectSpec.GetContext().GetHitResult()->Location); 
					switch (HitDirection)
					{
					case EHitReactDirection::Left:
						TargetCharacter->PlayHitReact(HitDirectionLeftTag); 
						break;
					case EHitReactDirection::Front:
						TargetCharacter->PlayHitReact(HitDirectionFrontTag);
						break;
					case EHitReactDirection::Right:
						TargetCharacter->PlayHitReact(HitDirectionRightTag);
						break;
					case EHitReactDirection::Back:
						TargetCharacter->PlayHitReact(HitDirectionBackTag);
						break;
					default:
						break;
					}
				}
				else
				{
					TargetCharacter->PlayHitReact(HitDirectionFrontTag);
				}
				if (SourceActor != TargetActor)
				{
					if (ARevolverPlayerController* PC = Cast<ARevolverPlayerController>(SourceController))
					{
						// we can do UI stuff here to handle damage numbers if we need them done or not
						
						
					}
				}
				
			}
		}
	} // end of the damage section
}
