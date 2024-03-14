// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "../../DataHolders/EconomyItemHolder.h"
#include "../../DataHolders/AllGraphicsHolder.h"
#include "CustomizeData.h"
#include "../../Utilitys/LoadTextureFromURL.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "DetailPropItemButton.generated.h"

UCLASS()
class USameTagListData : public UObject {
	GENERATED_BODY()
public:
	int Index;
	FEconomyItems Economyitem;
};


/**
 * 
 */
UCLASS()
class AVATARYUGDEMO_API UDetailPropItemButton : public UUserWidget,public IUserObjectListEntry
{
	GENERATED_BODY()

    protected:
    void NativeConstruct() override;

    virtual void
    NativeOnListItemObjectSet(UObject *ListItemObject) override;

    
    UPROPERTY(meta = (BindWidget))
    class UImage *ItemImage;

    UPROPERTY(meta = (BindWidget))
    class UImage *CurrencyImage;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock *CurrencyText;

    FString Id;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FSlateBrush CurrencyCN;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FSlateBrush CurrencyCC;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FSlateBrush ReamMoneyImage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    AAllGraphicsHolder *AllGraphicsHolder;

    UFUNCTION()
    void OnLoadImage( UTexture2D *textures);
    
    UPROPERTY()
    FOnReceiveTexture OnReceiveTexture;


};
