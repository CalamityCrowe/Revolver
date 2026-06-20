// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Components/Credits/CreditRole.h"

#include "CommonTextBlock.h"
#include "SkeletalMeshAttributes.h"
#include "MenuFiles/CreditsStructure.h"

UCreditRole::UCreditRole(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	
}

void UCreditRole::SetRoleText(const FText& InRole)
{
	if (CT_Role)
	{
		CT_Role->SetText(InRole);
	}
}

void UCreditRole::AddRole(const FCredits& InCredits)
{
	FText Names;
	
	for (int i = 0; i < InCredits.Names.Num(); ++i)
	{
		if (i == 0)
		{
			Names = InCredits.Names[i];
		}
		else
		{
			FFormatNamedArguments Args; 
			Args.Add(TEXT("l1"), Names);
			Args.Add(TEXT("l2"), InCredits.Names[i]);
			Names = FText::Format(NSLOCTEXT("Credits","NamesList", "{l1}\n{l2}"), Args); 
		}
	}
	CT_Names->SetText(Names); 
}
