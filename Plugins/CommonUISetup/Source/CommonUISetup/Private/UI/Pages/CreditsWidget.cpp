// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Pages/CreditsWidget.h"

#include "Components/ScrollBox.h"
#include "MenuFiles/CreditsStructure.h"
#include "UI/Components/Credits/CreditCategory.h"

UCreditsWidget::UCreditsWidget(const FObjectInitializer& ObjectInitializer)
{
}

void UCreditsWidget::NativeOnActivated()
{
	Super::NativeOnActivated();
	InitializeCredits(); 
}

void UCreditsWidget::InitializeCredits()
{
	if (CreditsTable && CreditCategoryWidgetClass)
	{
		TArray<FName> RowNames = CreditsTable->GetRowNames();
		for (FName RowName : RowNames)
		{
			if (FCredits* Credit = CreditsTable->FindRow<FCredits>(RowName, TEXT("")))
			{
				FString Key = Credit->Category.ToString(); 
				UCreditCategory** Found = CreditCategories.Find(Key);
				UCreditCategory* CreditCategory = Found ? *Found : nullptr;
				if (!CreditCategory)
				{
					CreditCategory = CreateWidget<UCreditCategory>(GetOwningPlayer(),CreditCategoryWidgetClass); 
					CreditCategory->InitializeCategory(Credit->Category); 
					CreditCategories.Add(Key, CreditCategory);
					SCB_Credits->AddChild(CreditCategory);
				}
				CreditCategory->AddCredit(*Credit); 
			}
		}
	}
}
