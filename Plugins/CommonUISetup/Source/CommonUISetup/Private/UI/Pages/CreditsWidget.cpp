// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Pages/CreditsWidget.h"

#include "Components/ScrollBox.h"
#include "Components/Spacer.h"
#include "MenuFiles/CreditsStructure.h"
#include "UI/Components/BaseMenuButton.h"
#include "UI/Components/Credits/CreditCategory.h"

UCreditsWidget::UCreditsWidget(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer), SpacerSize(FVector2D(0, 1000))
{
}

void UCreditsWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	InitializeCredits();
}

void UCreditsWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (WB_BackButton)
	{
		WB_BackButton->OnClicked().AddUObject(this, &UCreditsWidget::OnBackButtonPressed);
	}
	
}


void UCreditsWidget::RollCredits()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(ScrollTimerHandle))
	{
		GetWorld()->GetTimerManager().ClearTimer(ScrollTimerHandle);
	}
	ResetCredits();
	GetWorld()->GetTimerManager().SetTimer(ScrollTimerHandle, this, &UCreditsWidget::ScrollCredits, 0.05f, true);
}

void UCreditsWidget::OnBackButtonPressed()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(ScrollTimerHandle))
	{
		GetWorld()->GetTimerManager().ClearTimer(ScrollTimerHandle);
	}
	ResetCredits();
	if (OnCreditsFinished.IsBound())
	{
		OnCreditsFinished.Execute();
	}
}

void UCreditsWidget::ResetCredits()
{
	SCB_Credits->SetScrollOffset(0);
}

void UCreditsWidget::InitializeCredits()
{
	if (CreditsTable && CreditCategoryWidgetClass)
	{
		AddSpacer(); 
		
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
					CreditCategory = CreateWidget<UCreditCategory>(this,CreditCategoryWidgetClass); 
					CreditCategory->InitializeCategory(Credit->Category); 
					CreditCategories.Add(Key, CreditCategory);
					SCB_Credits->AddChild(CreditCategory);
				}
				CreditCategory->AddCredit(*Credit); 
			}
		}
		
		AddSpacer(); 
	}
}

void UCreditsWidget::AddSpacer()
{
	if (USpacer* CreditSpacer = NewObject<USpacer>(this))
	{
		CreditSpacer->SetSize(SpacerSize); 
		SCB_Credits->AddChild(CreditSpacer);
	}
}

void UCreditsWidget::ScrollCredits()
{
	float CurrentOffset = SCB_Credits->GetScrollOffset();
	float EndOffset = SCB_Credits->GetScrollOffsetOfEnd();
    
    if (CurrentOffset < EndOffset)
    {
		SCB_Credits->SetScrollOffset(CurrentOffset + ScrollSpeed);
    }
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(ScrollTimerHandle);
		OnCreditsFinished.Execute(); 
	}
}
