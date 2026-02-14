// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InteractionComponent.h"
// engine 
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"

// interaction plugin
#include "Interfaces/InteractableInterface.h"
#include "UI/InteractableWidget.h"


UInteractionComponent::UInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
	CharacterRef = Cast<ACharacter>(GetOwner()); 
	if (CharacterRef)
	{
		if (UCapsuleComponent* Collider = CharacterRef->GetCapsuleComponent())
		{
			Collider->OnComponentBeginOverlap.AddDynamic(this, &UInteractionComponent::OnInteractableOverlap); 
			Collider->OnComponentEndOverlap.AddDynamic(this, &UInteractionComponent::OnInteractableEndOverlap);
		}
	}
}


void UInteractionComponent::ResetInteractionProgress()
{
	// we do something with the widget here
	/*if (IsValid(InteractWidgetInstance))
	{
		InteractWidgetInstance->SetHoldTime(0); 
	}*/
	InteractionPressOngoing.Unbind(); 
}

void UInteractionComponent::InteractBegin()
{
	AActor* ActiveInteractable = GetActiveInteractable();
	if (IsValid(ActiveInteractable) && ActiveInteractable->GetClass()->ImplementsInterface(UInteractableInterface::StaticClass()))
	{
		EInteractionType InteractionType = IInteractableInterface::Execute_GetInteractionType(ActiveInteractable); 
		switch (InteractionType)
		{
		case EInteractionType::Press: 
			ActivateInteractAction(); 
			break;
		case EInteractionType::Hold: 
			if (!InteractionPressOngoing.IsBound())
			{
				InteractionPressOngoing.BindUObject(this, &UInteractionComponent::InteractionOngoing); 
			}
			break; 
		default:
			break; 
		}
	}
}

void UInteractionComponent::RenderInteractionWidget()
{

}


void UInteractionComponent::Interact()
{
	InteractBegin(); 
}

void UInteractionComponent::ActivateInteractAction()
{
	if (CharacterRef && !InteractableActors.IsEmpty())
	{
		if (AActor* Act = GetActiveInteractable())
		{
			if (UAnimMontage* InteractMontage = IInteractableInterface::Execute_GetInteractionAnimMontage(Act))
			{
				CharacterRef->GetMesh()->GetAnimInstance()->Montage_Play(InteractMontage); 
				// we will need to do something to reset the widget
			}
			else
			{
				IInteractableInterface::Execute_Interact(Act, GetOwner());
			}
		}
	}
}

void UInteractionComponent::InteractionOngoing(float ElapsedTime)
{
	if (!IsValid(GetActiveInteractable()))
	{
		ResetInteractionProgress(); 
		return;
	}
	float HoldDuration = IInteractableInterface::Execute_GetHoldDuration(GetActiveInteractable()); 
	
	
	
	if (ElapsedTime>HoldDuration)
	{
		ActivateInteractAction(); 
		InteractionPressOngoing.Unbind();
	}
}

void UInteractionComponent::OnInteractableOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetClass()->ImplementsInterface(UInteractionComponent::StaticClass()))
	{
		InteractableActors.AddUnique(OtherActor);
		RenderInteractionWidget(); 
	}
}

void UInteractionComponent::OnInteractableEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->GetClass()->ImplementsInterface(UInteractionComponent::StaticClass()))
	{
		if (OtherActor == GetActiveInteractable())
		{
			InteractionPressOngoing.Unbind();
		}
		
		InteractableActors.Remove(OtherActor);
		
		InteractableActors.RemoveAll([](const TWeakObjectPtr<AActor>& ActorPtr)
		{
			return !ActorPtr.IsValid();
		});
		
		RenderInteractionWidget(); 
	}
}

AActor* UInteractionComponent::GetActiveInteractable() const
{
	AActor* FoundActor = nullptr; 
	float ClosestDistance = FLT_MAX;
	FVector CharacterLoc = CharacterRef->GetActorLocation(); 
	
	if (!InteractableActors.IsEmpty())
	{
		FoundActor = InteractableActors[0].Get(); 
		for (TWeakObjectPtr<AActor> WeakActor : InteractableActors)
		{
			if (AActor* actor = WeakActor.Get())
			{
				const float TempDistance = FVector::Distance(CharacterLoc, actor->GetActorLocation());
				if (TempDistance < ClosestDistance)
				{
					ClosestDistance = TempDistance;
					FoundActor = actor;
				}
			}
		}
	}
	return FoundActor;
}


