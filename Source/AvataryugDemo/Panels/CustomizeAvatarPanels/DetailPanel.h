// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "../../DataHolders/DataHolder.h"
#include "../../DataHolders/EconomyItemHolder.h"
#include "../../DataHolders/UserInventoryHolder.h"
#include "../../DataHolders/UserDetailHolder.h"
#include "Components/ListView.h"
#include "../../DataHolders/AllGraphicsHolder.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanel.h"
#include "../../Utilitys/APIEvents.h"
#include "DetailPropItemButton.h"
#include "Components/Image.h"
#include "DetailPanel.generated.h"

/**
 * 
 */
UCLASS()
class AVATARYUGDEMO_API UDetailPanel : public UUserWidget
{
	GENERATED_BODY()
protected:
        void NativeConstruct() override;

    UPROPERTY(meta = (BindWidget))
    class UButton *CloseButton;

    UPROPERTY(meta = (BindWidget))
    class UButton *CloseButton1;

    UPROPERTY(meta = (BindWidget))
    class UImage *ItemImage;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock *ItemNameText;
       
    UPROPERTY(meta = (BindWidget))
    class UTextBlock *TagsText;
    
    UPROPERTY(meta = (BindWidget))
    class UImage *CurrencyImage;
    
    UPROPERTY(meta = (BindWidget))
    class UTextBlock *CurrencyText;

    UPROPERTY( meta = (BindWidget))
    class UListView *SimilarTagListView;
        
    UPROPERTY(meta = (BindWidget))
    class UButton *BuyButton;

    UPROPERTY(meta = (BindWidget))
	class UCanvasPanel *FullDetail_Panel;

    UFUNCTION()
    void OnClickBuyButton();

    UFUNCTION()
    void CloseDetailPanel();
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FEconomyItems economyItems;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    AAllGraphicsHolder *AllGraphicsHolder;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    ADataHolder *DataHolder;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    AAPIEvents *APIEvents;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    AUserInventoryHolder *UserInventoryHolder;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    AEconomyItemHolder *EconomyItemHolder;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FSlateBrush CurrencyCN;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FSlateBrush CurrencyCC;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FSlateBrush ReamMoneyImage;
public:
	 UFUNCTION()
    void LoadDetailPanelData();
    UFUNCTION()
    void SetDetailPanelOrientation(bool isLandscape);
    
};

