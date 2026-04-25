// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Components/Credits/CreditCategory.h"

#include "CommonTextBlock.h"
#include "Components/VerticalBox.h"
#include "UI/Components/Credits/CreditRole.h"

UCreditCategory::UCreditCategory(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	
}

void UCreditCategory::InitializeCategory(const FText& InText)
{
	if (CT_CreditCategory)
	{
		CT_CreditCategory->SetText(InText);
	}
}

void UCreditCategory::AddCredit(const FCredits& Credit)
{
	FString Key = Credit.Role.ToString();
	UCreditRole** Found = Roles.Find(Key); 
	UCreditRole* CreditRole = Found? *Found:nullptr;
	if (!CreditRole)
	{
		CreditRole = CreateWidget<UCreditRole>(this, CreditRoleWidgetClass); 
		CreditRole->SetRoleText(Credit.Role);
		VB_Credit->AddChild(CreditRole);
		Roles.Add(Key, CreditRole);
	}
	CreditRole->AddRole(Credit);
}
