// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameStructs.h"
#include "../../../DataHolders/ColorListData.h"
#include "ColorPickerButton.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "ColorPickerButtonGrid.generated.h"

/**
 *
 */
UCLASS()
class AVATARYUGDEMO_API UColorPickerButtonGrid : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:
	void NativeConstruct() override;
	virtual void NativeOnListItemObjectSet(UObject *ListItemObject) override;

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UColorPickerButton *ColorPickerButton1;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UColorPickerButton *ColorPickerButton2;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UColorPickerButton *ColorPickerButton3;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UColorPickerButton *ColorPickerButton4;
	TArray<UColorPickerButton *> PropItemButtons;
};
