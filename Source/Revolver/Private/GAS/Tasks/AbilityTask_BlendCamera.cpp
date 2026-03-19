// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Tasks/AbilityTask_BlendCamera.h"

#include "Abilities/Tasks/AbilityTask_SpawnActor.h"
#include "Characters/Player/RevolverPlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"

UAbilityTask_BlendCamera* UAbilityTask_BlendCamera::BlendCamera(UGameplayAbility* OwningAbility, FVector TargetOffset,
                                                                float TargetArmLength, float BlendTime, UCurveFloat* BlendCurve)
{
	UAbilityTask_BlendCamera* BlendTask = NewAbilityTask<UAbilityTask_BlendCamera>(OwningAbility);
	BlendTask->TargetSocketOffset = TargetOffset;
	BlendTask->TargetArmLength = TargetArmLength;
	BlendTask->BlendTime = BlendTime;
	BlendTask->BlendCurve = BlendCurve;
	BlendTask->bTickingTask = true; 
	return BlendTask;
}

void UAbilityTask_BlendCamera::Activate()
{
	Super::Activate();
	ElapsedTime = 0; // on activation we set the elapsed time to be 0 so it starts at the correct point
	
	// we grab the socket and length for the starting point
	if (ARevolverPlayerCharacter* Player = Cast<ARevolverPlayerCharacter>(GetAvatarActor()))
	{
		StartSocketOffset = Player->GetCameraBoom()->SocketOffset; 
		StartArmLength = Player->GetCameraBoom()->TargetArmLength; 
		OriginalArmLength = Player->GetDefaultArmLength(); 
		OriginalSocketOffset = Player->GetDefaultSocketOffset();
	}
	else
	{
		
		EndTask();
	}
}

void UAbilityTask_BlendCamera::OnDestroy(bool bInOwnerFinished)
{
	if (!bInOwnerFinished)
	{
		if (ARevolverPlayerCharacter* Player = Cast<ARevolverPlayerCharacter>(GetAvatarActor()))
		{
			USpringArmComponent* Boom = Player->GetCameraBoom();
			Boom->SocketOffset = OriginalSocketOffset;
			Boom->TargetArmLength = OriginalArmLength;
		}
	}
	Super::OnDestroy(bInOwnerFinished);
}


void UAbilityTask_BlendCamera::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);
	if (!bOwnerFinished)
	{
		ElapsedTime += DeltaTime; // we incrementy the elapsed time by delta time so we can get the correct alpha later
	
		// we clamp the value of the elapsed time/blend time to makle sure the alpha cant go above or below 0 and 1
		float Alpha = FMath::Clamp(ElapsedTime/BlendTime, 0.f, 1.f);
		if (BlendCurve) // if there is a blend curve assigned then we just use the value from there instead
		{
			Alpha = BlendCurve->GetFloatValue(Alpha); 
		}
	
		// we grab the player and lerp the starting to target postion based on the alpha
		if (ARevolverPlayerCharacter* Player = Cast<ARevolverPlayerCharacter>(GetAvatarActor()))
		{
			USpringArmComponent* Boom = Player->GetCameraBoom();
			Boom->SocketOffset = FMath::Lerp(StartSocketOffset, TargetSocketOffset, Alpha);
			Boom->TargetArmLength = FMath::Lerp(StartArmLength, TargetArmLength, Alpha);
		}
	
		// lasty once we hit the blend time, then we end the task and destroy it in the process
		if (ElapsedTime > BlendTime)
		{
			OnBlendFinished.Broadcast();
			EndTask();
		}	
	}
}


