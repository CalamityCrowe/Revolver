// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/TargetLockOnComponent.h"

#include "ShaderPrintParameters.h"
#include "Camera/CameraComponent.h"
#include "Characters/Player/RevolverPlayerCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "TargetingSystem/TargetingSubsystem.h"

// Sets default values for this component's properties
UTargetLockOnComponent::UTargetLockOnComponent()
{

	PrimaryComponentTick.bCanEverTick = false;

}

// this is the function that will be getting called by the owning actor in order to trigger the lock on of the target
void UTargetLockOnComponent::ToggleLockOn()
{
	if (bLockedOn)
	{
		StopLockOn();
	}
	else
	{
		StartLockOn();
	}
}

void UTargetLockOnComponent::SwitchTarget(float AxisValue)
{
	// we exit out of the function straight away if we aren't locked onto a target to begin with
	if (!bLockedOn)
	return;
	
	InputAxis = AxisValue; // we grab the input axis here so we can use it in the the switch delegate later
	// same idea as the lock on system, but instead we are doing it for the switch system
	if (UTargetingSubsystem* TargetSubsystem = UTargetingSubsystem::Get(GetWorld()))
	{
		FTargetingSourceContext SourceContext;
		SourceContext.SourceActor = OwningPlayer;
		
		FTargetingRequestHandle Handle = TargetSubsystem->MakeTargetRequestHandle(TargetingPreset, SourceContext);
		
		FTargetingRequestDynamicDelegate SwitchDelegate;
		SwitchDelegate.BindDynamic(this, &UTargetLockOnComponent::OnSwitchComplete);
		
		TargetingSubsystem->StartAsyncTargetingRequestWithHandle(Handle,FTargetingRequestDelegate(),SwitchDelegate);
	}
}



void UTargetLockOnComponent::BeginPlay()
{
	Super::BeginPlay();
	// we grab a referece to the owning player to handle the correct rotations on them
	if (ARevolverPlayerCharacter* PlayerRef = Cast<ARevolverPlayerCharacter>(GetOwner()))
	{
		OwningPlayer = PlayerRef;
	}
	
	// we cache the targeting subsytem to reduce call backs to a getter
	if (UTargetingSubsystem* Temp = UTargetingSubsystem::Get(GetWorld()))
	{
		TargetingSubsystem = Temp;
	}
	
}

void UTargetLockOnComponent::StartLockOn()
{
	// we clear and invalidate the timer and target if for some reason they are valid at this point
	GetWorld()->GetTimerManager().ClearTimer(LockOnTimer); 
	CurrentTarget = nullptr;
	
	if (!TargetingPreset)
	{
		UE_LOG(LogTemp,Warning, TEXT("Targeting preset hasn't been set within the target lock on component")); 
		return; 
	}
	
	// we check if the targeting sub system is valid in this instance, as we don't want to have it attempting this if it cant
	if (TargetingSubsystem)
	{
		// we set up the source context to be the owner
		FTargetingSourceContext SourceContext;
		SourceContext.SourceActor = OwningPlayer; 
		
		// we create a request based on the target preset and the context. This is so we get the correct resuylts from the target task later
		FTargetingRequestHandle Handle = UTargetingSubsystem::MakeTargetRequestHandle(TargetingPreset, SourceContext);  
		
		// we create a delegate here to bind the correct matching function, in this case the initial lock on system
		FTargetingRequestDynamicDelegate LockOnComplete;
		LockOnComplete.BindDynamic(this, &UTargetLockOnComponent::OnLockOnComplete); 
		
		TargetingSubsystem->StartAsyncTargetingRequestWithHandle(Handle,FTargetingRequestDelegate(),LockOnComplete); 
	}
}

// this will basically reset all the values for the lock oin and allow camera rotation again
void UTargetLockOnComponent::StopLockOn()
{
	GetWorld()->GetTimerManager().ClearTimer(LockOnTimer);
	CurrentTarget = nullptr;
	bLockedOn = false;
	OwningPlayer->GetController()->SetIgnoreLookInput(false);
}


AActor* UTargetLockOnComponent::GetClosestTarget(const TArray<AActor*>& Targets) const
{
	AActor* ClosestTarget = nullptr;
	float LocalCompare = 0.0f;

	const FVector CamLoc = OwningPlayer->GetCamera()->GetComponentLocation(); 
	
	// we loop through all the targetsfound via the targetting system
	for (AActor* Actor : Targets)
	{
		FVector EndLocation = Actor->GetActorLocation();  // we grab the end location we want for the line trace
		FHitResult Hit;
		if (GetWorld()->LineTraceSingleByChannel(Hit, CamLoc, EndLocation, ECC_Visibility)) // we make sure that we can hit something between the owner and target
		{
			if (Hit.GetActor() == Actor) // we then check it was the actual actor we hit and not a wall
			{
				if (float Dot = CloseToCentre(Actor); Dot > LocalCompare) // we check if the dot product is greater to the local compare. the closer to one it is, the cloaser to the centre of the screen it is
				{
					LocalCompare = Dot; 
					ClosestTarget = Actor;
				}
			}
		}
	}
	return ClosestTarget;
}

float UTargetLockOnComponent::CloseToCentre(const AActor* Target) const
{
	// we first find the rotation we would be needing to look at the target from the player
	FRotator LookRotation = UKismetMathLibrary::FindLookAtRotation(OwningPlayer->GetActorLocation(), Target->GetActorLocation());
	// we then perfrom the dot product from the resulting forward vector from the camera and the look at rotation(.vector returns a forward vector)
	return UKismetMathLibrary::Dot_VectorVector(OwningPlayer->GetCamera()->GetForwardVector(), LookRotation.Vector()); 
}

void UTargetLockOnComponent::AdjustCamera()
{
	if (CurrentTarget == nullptr) // we don't want to run this if the target is not valid
	{
		StopLockOn(); 
		return; 
	}
	FRotator LockOnRotation = GetLockOnCameraRotation(CurrentTarget); 
	FRotator ControlRotation = OwningPlayer->GetControlRotation(); 
	FRotator NewRotation = UKismetMathLibrary::RInterpTo(ControlRotation, LockOnRotation, 0.01, InterpSpeed); 
	
	NewRotation.Roll = ControlRotation.Roll; // we correct the roll rotation to be that of the control rotation. we dont want this to randomly tilt at random
	
	OwningPlayer->GetController()->SetControlRotation(NewRotation); // lastly we just set the control rotation
	
	// we check if the current target is still in range or we have LOS still, if not we stop the lock on
	if (!IsStillInRange())
	{
		StopLockOn(); 
	}
}

FRotator UTargetLockOnComponent::GetLockOnCameraRotation(const AActor* Target) const 
{
	if (!IsValid(Target))
	{
		return FRotator(); 
	}
	FVector CameraLocation = OwningPlayer->GetCamera()->GetComponentLocation(); // we first want to grab the cameras location
	FVector TargetLocation = Target->GetActorLocation();
	float DistanceToTarget = FVector::Dist(OwningPlayer->GetActorLocation(), TargetLocation)/LockOnScale; // we get the distance between the player and target, then divide it to get the correct look at location
	
	TargetLocation.Z = TargetLocation.Z - DistanceToTarget; // we change the Z axis of the target location to be the current Z offset by the new Z
	
	
	return UKismetMathLibrary::FindLookAtRotation(CameraLocation, TargetLocation); // lastly we find the new look at location from the camera to the "Target location"
}

bool UTargetLockOnComponent::IsStillInRange() const
{
	if (IsValid(OwningPlayer) && IsValid(CurrentTarget))
	{
		return FVector::Distance(OwningPlayer->GetActorLocation(), CurrentTarget->GetActorLocation()) < LockOnRadius; 
	}
	return false;
}

bool UTargetLockOnComponent::StillHasLOS() const
{
	FHitResult Hit;
	if (GetWorld()->LineTraceSingleByChannel(Hit, OwningPlayer->GetCamera()->GetComponentLocation(), CurrentTarget->GetActorLocation(), ECC_Visibility))
	{
		return Hit.GetActor() == CurrentTarget;
	}
	return false; 
}

void UTargetLockOnComponent::OnLockOnComplete(FTargetingRequestHandle TargetingHandle)
{
	// we check that the targetting system is still valid at this point
	if (!TargetingSubsystem)
	{
		return;	
	}
	// we grab all the actors from the targetting subsystem that have been filtered automatically
	TArray<AActor*> TargetingActors;
	TargetingSubsystem->GetTargetingResultsActors(TargetingHandle,TargetingActors);
	CurrentTarget = GetClosestTarget(TargetingActors); // we call this function to find the one closest to the center of the camere
	
	// lastly we set a timer to adjust the new look at rotation and toggle bools to handle look movement correctly
	GetWorld()->GetTimerManager().SetTimer(LockOnTimer,this,&UTargetLockOnComponent::AdjustCamera,0.01f,true); 
	bLockedOn = true;
	OwningPlayer->GetController()->SetIgnoreLookInput(true); 
}

void UTargetLockOnComponent::OnSwitchComplete(FTargetingRequestHandle TargetingHandle)
{
	// we make sure the subsystem is still valid here
	if (!TargetingSubsystem)
		return;
	
	AActor* NewTarget = nullptr; // we make a temp value here to assign the next closest target  
	
	// we want to grab the locations and directiosn of objects that wont change here, as this will all be running on the same call so these wont change in the for loop
	FVector CameraLocaction = OwningPlayer->GetCamera()->GetComponentLocation();
	FVector CameraRight = OwningPlayer->GetCamera()->GetRightVector(); 
	float LocalCompare = 0.0f; 
	
	TArray<AActor*> TargetingActors;
	TargetingSubsystem->GetTargetingResultsActors(TargetingHandle,TargetingActors);
	
	// we loop through all the target actors to find the closest one to the centre of the camere
	for (AActor* Actor : TargetingActors)
	{
		FVector TargetLocation = Actor->GetActorLocation();
		FVector DirectionToEnemy = (TargetLocation - CameraLocaction).GetSafeNormal(); 
		
		FHitResult Hit;
		if (GetWorld()->LineTraceSingleByChannel(Hit,CameraLocaction,TargetLocation, ECC_Visibility ))
		{
			if (Actor != CurrentTarget)
			{
				// we check if it is greater than 0 to see if it is to the right ofd the camera, and left if it is < 0
				if (const float DotProduct = CameraRight|DirectionToEnemy; (InputAxis > 0.0f && DotProduct > 0 ) || (InputAxis< 0.0f && DotProduct < 0))
				{
					if (float DistanceToCenter = CloseToCentre(Actor); DistanceToCenter > LocalCompare)
					{
						LocalCompare = DistanceToCenter;
						NewTarget = Actor;
					}
				}
			}
		}
	}
	
	// if we have a valid target, we switch the current target to it
	if (IsValid(NewTarget))
	{
		CurrentTarget = NewTarget;
	}
}

