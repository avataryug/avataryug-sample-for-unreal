// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "CoinPanel.generated.h"

UCLASS()
class UCurrencyItemData : public UObject {
	GENERATED_BODY()
public:
	int Index;
    FString CurrencyAmount;
    FString CurrencyCode;
	
};
/**
 * 
 */
UCLASS()
class AVATARYUGDEMO_API UCoinPanel : public UUserWidget,public IUserObjectListEntry
{
	GENERATED_BODY()
	protected:
        void NativeConstruct() override;
        virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

        UPROPERTY(meta = (BindWidget))
        class UImage *CurrencyImage;

        UPROPERTY(meta = (BindWidget))
        class UTextBlock *CurrencyAmount;

        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
        FSlateBrush CNImage;

        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
        FSlateBrush CCImage;

 
};
