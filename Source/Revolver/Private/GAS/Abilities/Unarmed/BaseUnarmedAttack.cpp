// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Abilities/Unarmed/BaseUnarmedAttack.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Characters/Enemies/EnemyCharacter.h"
#include "GAS/Abilities/Weapon/Melee/BaseMeleeAttack.h"
#include "GAS/Data/PayloadData.h"
#include "Kismet/KismetSystemLibrary.h"

UBaseUnarmedAttack::UBaseUnarmedAttack()
{
}

void UBaseUnarmedAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle,const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	UAbilityTask_PlayMontageAndWait* PlayMontageAndWait = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
		this, NAME_None,MontageToPlay,1);
	
	GEngine->AddOnScreenDebugMessage(-1,5,FColor::Red, "AAAAAAAAAAAAAAA"); 
	
	PlayMontageAndWait->OnCompleted.AddDynamic(this, &UBaseUnarmedAttack::OnMontageCompleted); 
	PlayMontageAndWait->OnCancelled.AddDynamic(this, &UBaseUnarmedAttack::OnMontageCanceled);
	PlayMontageAndWait->OnBlendOut.AddDynamic(this, &UBaseUnarmedAttack::OnMontageBlendOut);
	PlayMontageAndWait->ReadyForActivation(); 
	
	
	UAbilityTask_WaitGameplayEvent* HitScanStartEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(
		this,
		HitScanStartTag,
		nullptr, 
		false, 
		true);
	
	HitScanStartEvent->EventReceived.AddDynamic(this, &UBaseUnarmedAttack::HitScanStarted); 
	HitScanStartEvent->ReadyForActivation(); 
}

void UBaseUnarmedAttack::OnMontageCompleted()
{
	if (AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(CurrentActorInfo->AvatarActor))
	{
		EnemyCharacter->OnAttackEnded.Broadcast();
	}
	EndAbility(CurrentSpecHandle, CurrentActorInfo,CurrentActivationInfo,true, false);
}

void UBaseUnarmedAttack::OnMontageCanceled()
{
	if (AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(CurrentActorInfo->AvatarActor))
	{
		EnemyCharacter->OnAttackEnded.Broadcast();
	}
	EndAbility(CurrentSpecHandle, CurrentActorInfo,CurrentActivationInfo,true, true);
}

void UBaseUnarmedAttack::OnMontageBlendOut()
{
	if (AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(CurrentActorInfo->AvatarActor))
	{
		EnemyCharacter->OnAttackEnded.Broadcast();
	}
	EndAbility(CurrentSpecHandle, CurrentActorInfo,CurrentActivationInfo,true, false);
}

// we set up the timer for the ability
void UBaseUnarmedAttack::HitScanStarted(FGameplayEventData PayLoad)
{
	// we clear the hit actors to ensure the targets can be hit again 
	HitActors.Empty();
	
	if (const USocketCollisionParamsObject* ParamsObj = Cast<USocketCollisionParamsObject>(PayLoad.OptionalObject))
	{
		SocketName = ParamsObj->Params.SocketName;
		CollisionRadius = ParamsObj->Params.CollisionRadius;
	}
	
	if (GetWorld()->GetTimerManager().IsTimerActive(HitScanTimer))
	{
		GetWorld()->GetTimerManager().ClearTimer(HitScanTimer);
	}
	
	GetWorld()->GetTimerManager().SetTimer(HitScanTimer, this,&UBaseUnarmedAttack::HitScan, ScanInterval, true); 
}
// clears and invalidates the timer of the ability
void UBaseUnarmedAttack::HitScanEnded(FGameplayEventData PayLoad)
{
	GetWorld()->GetTimerManager().ClearTimer(HitScanTimer);
}

void UBaseUnarmedAttack::HitScan()
{
	FVector Start = GetCharacterFromActorInfo()->GetMesh()->GetSocketLocation(SocketName);
	
	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(GetAvatarActorFromActorInfo());
	
	TArray<FHitResult> HitResults;
	
	UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(),
		Start,Start,
		CollisionRadius,ObjectTypes,
		false,IgnoreActors,
		EDrawDebugTrace::ForDuration,HitResults, false ); 
	
	if (HitResults.Num() > 0)
	{
		for (FHitResult Hit : HitResults)
		{
			UAbilitySystemComponent* HitASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Hit.GetActor()); 
			if (HitASC && !HitActors.Contains(Hit.GetActor()))
			{
				HitActors.AddUnique(Hit.GetActor()); 
				FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingGameplayEffectSpec(EffectClass, 1);
				EffectSpecHandle.Data->SetSetByCallerMagnitude(EffectMagnitudeTag, EffectMagnitude); 
				
				EffectSpecHandle.Data->GetContext().AddHitResult(Hit, true);
				HitASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get()); 
			}
		}
	}
	
}

