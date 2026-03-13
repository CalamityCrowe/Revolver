// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/WeaponManagerComponent.h"

#include "AbilitySystemComponent.h"
#include "Characters/CharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GAS/EnhancedAbilitySet.h"
#include "GAS/EnhancedAbilitySystemComponent.h"
#include "Weapons/WeaponBase.h"

UWeaponManagerComponent::UWeaponManagerComponent()
{
}

void UWeaponManagerComponent::BeginPlay()
{
	Super::BeginPlay();
	if (GetOwner())
	{
		OwningCharacter = Cast<ACharacterBase>(GetOwner()); // we grab the owning character from the GetOwner function 
	}
}

void UWeaponManagerComponent::EquipWeapon(TSubclassOf<AWeaponBase> WeaponToEquip)
{
	// we only run this, if the owning player is valid
	if (OwningCharacter)
	{
		if (IsValid(EquippedWeapon)) // we check that the current equipped weapon is valid, 
		{
			if (EquippedWeapon->GetClass() == WeaponToEquip) // we unequip the current weapon 
			{
				UnEquipWeapon();
			}
			else
			{
				UnEquipWeapon(); 
				SpawnWeapon(WeaponToEquip);
			}
		}
		else
		{
			SpawnWeapon(WeaponToEquip); 
		}
	}
}

void UWeaponManagerComponent::SpawnWeapon(TSubclassOf<AWeaponBase> WeaponToEquip)
{
	EquippedWeapon = GetWorld()->SpawnActor<AWeaponBase>(WeaponToEquip); 
	EquippedWeapon->SetInstigator(OwningCharacter); 
	UAnimInstance* AnimInstance = OwningCharacter->GetMesh()->GetAnimInstance(); 
	if (EquippedWeapon && AnimInstance)
	{
		AnimInstance->OnPlayMontageNotifyBegin.AddDynamic(this, &UWeaponManagerComponent::OnEquipNotifyBegin); 
		
		AnimInstance->Montage_Play(EquippedWeapon->GetWeaponConfig().EquipMontage); 
	}
}
void UWeaponManagerComponent::UnEquipWeapon()
{
	if (EquippedWeapon)
	{
		if (UAnimInstance* AnimInstance = OwningCharacter->GetMesh()->GetAnimInstance())
		{
			AnimInstance->OnPlayMontageNotifyBegin.AddDynamic(this, &UWeaponManagerComponent::OnUnEquipNotifyBegin); 
			AnimInstance->Montage_Play(EquippedWeapon->GetWeaponConfig().UnEquipMontage); 
			OwningCharacter->RemoveAbilities(AbilitiesGrantedByWeapon.GrantedAbilitySpecHandles); 
			AbilitiesGrantedByWeapon.GrantedAbilitySpecHandles.Empty(); 
		}
	}
}

UAnimInstance* UWeaponManagerComponent::GetAnimInstance() const
{
	return OwningCharacter->GetMesh()->GetAnimInstance();
}

void UWeaponManagerComponent::OnEquipNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& Payload)
{
	if (NotifyName == FName("EquipWeapon"))
	{
		if (EquippedWeapon)
		{
			FWeaponConfig CurrentConfig = EquippedWeapon->GetWeaponConfig();
			FWeaponMovementProperties MovementProperties = EquippedWeapon->GetMovementProperties();
			EquippedWeapon->AttachToComponent(OwningCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, CurrentConfig.EquipSocketName); 
			UEnhancedAbilitySystemComponent* OwningASC = Cast<UEnhancedAbilitySystemComponent> (OwningCharacter->GetAbilitySystemComponent());
			CurrentConfig.AbilitiesToGrant->GiveToAbilitySystem(OwningASC,&AbilitiesGrantedByWeapon,this); 
			
			OwningCharacter->GetCharacterMovement()->bOrientRotationToMovement = MovementProperties.bShouldOrientMovement; 
			OwningCharacter->GetCharacterMovement()->bUseControllerDesiredRotation = MovementProperties.bUseControlRotation; 

		}
		
		GetAnimInstance()->OnPlayMontageNotifyBegin.RemoveDynamic(this, &UWeaponManagerComponent::OnEquipNotifyBegin);
		
	}
}

void UWeaponManagerComponent::OnUnEquipNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& Payload)
{
	if (NotifyName == FName("UnEquipWeapon"))
	{
		OwningCharacter->GetCharacterMovement()->bOrientRotationToMovement = DefaultMovementProperties.bShouldOrientMovement;
		OwningCharacter->GetCharacterMovement()->bUseControllerDesiredRotation = DefaultMovementProperties.bUseControlRotation; 
		EquippedWeapon->Destroy(); 
		GetAnimInstance()->OnPlayMontageNotifyBegin.RemoveDynamic(this, &UWeaponManagerComponent::OnUnEquipNotifyBegin); 
	}
}


