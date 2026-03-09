// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Abilities/Weapon/Melee/MeleeComboAbility.h"

#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"

UMeleeComboAbility::UMeleeComboAbility()
{
}

// we override the montage start function to cue additional events here. we do this so we can handle the combos getting cued on the ability
void UMeleeComboAbility::MontageStart()
{
	Super::MontageStart();
	ComboCount = 1; 
	UAbilityTask_WaitGameplayEvent* ContinueComboStart = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(
		this,
		ComboStartTag,
		nullptr,
		false,
		true
		);
	ContinueComboStart->EventReceived.AddDynamic(this, &UMeleeComboAbility::ContinueComboStartEvent);
	ContinueComboStart->ReadyForActivation();
	
	UAbilityTask_WaitGameplayEvent* ContinueComboEnd = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(
		this, 
		ComboEndTag,
		nullptr, 
		false,
		true);
	
	ContinueComboEnd->EventReceived.AddDynamic(this, &UMeleeComboAbility::ContinueComboEndEvent);
	ContinueComboEnd->ReadyForActivation();
	
	UAbilityTask_WaitGameplayEvent* EventInputRecieved = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(
		this, 
		ComboInputTag,
		nullptr,
		false,
		true);
	
	EventInputRecieved->EventReceived.AddDynamic(this, &UMeleeComboAbility::InputRecievedEvent);
	EventInputRecieved->ReadyForActivation();
}

void UMeleeComboAbility::HandleHitScanStart(FGameplayEventData Payload)
{
	// we could do something with a combo multiplier here
	Super::HandleHitScanStart(Payload);
}

// we want to reset the input here and say it can trigger the next part of a combo
void UMeleeComboAbility::ContinueComboStartEvent(FGameplayEventData Payload)
{
	GEngine->AddOnScreenDebugMessage(-1,2,FColor::Red,"ContinueComboStart");
	bIsWithinComboWindow = true;
	bRecievedInputAtRightTime = false; 
}

// we close the combo window here and check if input was recieved, if so we increase the combo count otherwise we end the ability here
void UMeleeComboAbility::ContinueComboEndEvent(FGameplayEventData Payload)
{
	bIsWithinComboWindow = false;
	if (bRecievedInputAtRightTime)
	{
		ComboCount++; 
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1,2,FColor::Red,"Combo ENded"); 
		EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,true, false); 
	}
}

// for this one, we want to just make the recived input match the combo window bool
void UMeleeComboAbility::InputRecievedEvent(FGameplayEventData Payload)
{
	GEngine->AddOnScreenDebugMessage(-1,2,FColor::Red,"InputRecievedEvent");
	bRecievedInputAtRightTime = bIsWithinComboWindow;
}
