// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PropItemButton.h"
#include "GameStructs.h"
#include "../../DataHolders/EconomyItemHolder.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "PropItemGridPanel.generated.h"

/**
 *
 */

UCLASS()
class UListItemData : public UObject
{
	GENERATED_BODY()
public:
	int StartIndex;
	int TotalCount;
	TArray<FEconomyItems> Economyitems;
};

UCLASS()
class AVATARYUGDEMO_API UPropItemGridPanel : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:
	void NativeConstruct() override;
	virtual void NativeOnListItemObjectSet(UObject *ListItemObject) override;

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UPropItemButton *PropItemButtons1;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UPropItemButton *PropItemButtons2;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UPropItemButton *PropItemButtons3;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UPropItemButton *PropItemButtons4;
	TArray<UPropItemButton *> PropItemButtons;
	// UFUNCTION()
	// void SetData(int startingIndex, int totalIndex,TArray<FEconomyItems> items,FOnEconomyItemClick callback);
};
