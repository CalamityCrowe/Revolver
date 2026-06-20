#pragma once
#include "CoreMinimal.h"
#include "MenuDelegates.generated.h"

DECLARE_DYNAMIC_DELEGATE(FOnButtonPressed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOptionsChanged, int, SelectedIndex);

USTRUCT(meta = (HideInEditor))
struct FMenuDelegateDummy
{
	GENERATED_BODY(); 
};