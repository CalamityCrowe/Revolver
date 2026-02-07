#pragma once
#include "CoreMinimal.h"
#include "MenuDelegates.generated.h"

DECLARE_DYNAMIC_DELEGATE(FOnButtonPressed);

USTRUCT(meta = (HideInEditor))
struct FMenuDelegateDummy
{
	GENERATED_BODY(); 
};