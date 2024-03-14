// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "CurrencyWidget.generated.h"

UCLASS()
class UTotalCurrencyData : public UObject {
	GENERATED_BODY()
public:
	int StartIndex;
    FString Code;
    FString Amount;
};

USTRUCT(BlueprintType)
struct  FCurrencyWithAmount
{
    GENERATED_USTRUCT_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
        FString Code;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
        int Amount;
};
/**
 * 
 */
UCLASS()
class AVATARYUGDEMO_API UCurrencyWidget : public UUserWidget,public IUserObjectListEntry
{
  	GENERATED_BODY()
  
	protected:
        void NativeConstruct() override;
        virtual void NativeOnListItemObjectSet(UObject *ListItemObject) override;

        UPROPERTY(meta = (BindWidget))
    	class UImage *CurrencyImage;

    	UPROPERTY(meta = (BindWidget))
        class UTextBlock *CurrencyText;

        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
        FSlateBrush CurrencyCN;

        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
        FSlateBrush CurrencyCC;

        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
        FSlateBrush ReamMoneyImage;
};
