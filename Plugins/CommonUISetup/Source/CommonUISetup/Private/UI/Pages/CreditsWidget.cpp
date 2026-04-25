// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Pages/CreditsWidget.h"

#include "Components/ScrollBox.h"
#include "Components/Spacer.h"
#include "MenuFiles/CreditsStructure.h"
#include "UI/Components/Credits/CreditCategory.h"

UCreditsWidget::UCreditsWidget(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer), SpacerSize(FVector2D(0, 1000))
{
}

void UCreditsWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	InitializeCredits();
}

void UCreditsWidget::NativeOnActivated()
{
	//Super::NativeOnActivated();
	Super::NativeOnActivated();
	//InitializeCredits();
	GetWorld()->GetTimerManager().SetTimer(ScrollTimerHandle, this, &UCreditsWidget::ScrollCredits, 0.05f, true);

}

void UCreditsWidget::ResetCredits()
{
	SCB_Credits->SetScrollOffset(0);
}

void UCreditsWidget::InitializeCredits()
{
	if (CreditsTable && CreditCategoryWidgetClass)
	{
		ResetCredits();
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
    
	UE_LOG(LogTemp, Warning, TEXT("Scrolling: %s | Current: %f | End: %f"), bScrolling ? TEXT("true") : TEXT("false"), CurrentOffset, EndOffset);
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
