// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../DataHolders/DataHolder.h"
#include "../../DataHolders/EconomyItemHolder.h"
#include "../../DataHolders/UserDetailHolder.h"
#include "UserItemManagementAPI/UserItemManagementRequest.h"
#include "../../Utilitys/APIEvents.h"
#include "../../DataHolders/AllGraphicsHolder.h"
#include "../../DataHolders/UserInventoryHolder.h"
#include "Blueprint/UserWidget.h"
#include "Components/ListView.h"
#include "Components/Button.h"
#include "BuyListItem.h"
#include "CurrencyWidget.h"
#include "BuyItemPanel.generated.h"

/**
 * 
 */
UCLASS()
class AVATARYUGDEMO_API UBuyItemPanel : public UUserWidget
{
	GENERATED_BODY()
	protected:
        void NativeConstruct() override;
          
		UPROPERTY(meta = (BindWidget))
        class UButton *CloseButton;

        UPROPERTY(meta = (BindWidget))
        class UButton *CloseButton1;
        
        UPROPERTY(meta = (BindWidget))
        class UButton *BuyButton;

        UPROPERTY( meta = (BindWidget))
        class UListView *BuyItemListView;

        UPROPERTY( meta = (BindWidget))
        class UListView *CurrencyListView;
                
        UFUNCTION()
        void CloseBuyItemPanel();
        
        UFUNCTION()
        void OnClickBuyItem();

        UFUNCTION()
        void UpdatePrise();

        UFUNCTION()
        void AddCurrency(FString code, int amount);
        
        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyCategory)
        TArray<FCurrencyWithAmount> currencyWithAmounts;

        UFUNCTION()
        void OnQueueBuyItem();

        UFUNCTION()
        void PurchaseItem(FEconomyItems economyItem);

        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
        AAllGraphicsHolder *AllGraphicsHolder;
public:
        UFUNCTION()
        void LoadBuyPanelData();
        
		 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyCategory)
        TArray<FEconomyItems> BuyItemList;

        UPROPERTY()
        TArray<FEconomyItems> BuyItemQueueList;

        //Class References
	    UPROPERTY()
        AUserDetailHolder *UserDetailHolder;
            
        UPROPERTY()
        AUserInventoryHolder *UserInventoryHolder;

        UPROPERTY()
        ADataHolder *DataHolder;

        UPROPERTY()
        AAPIEvents *APIEvents;
        
        UFUNCTION()
        void AddingDelay();

        UPROPERTY()
    	FOnGetUserAccountInfoResult OnGetUserAccountInfoResult;
    	UFUNCTION()
    	void OnReceiveGetUserAccountInfoResult(FGetUserAccountInfoResult result);
    	UPROPERTY()
    	FOnApiException OnGetUserAccountInfoError;
		UFUNCTION()
                void OnReceiveGetUserAccountInfoError(FApiException error);
                
		UPROPERTY()
        FOnGetUserInventoryResult OnGetUserInventoryResult;
		UFUNCTION()
		void GetUserInventoryResult(FGetUserInventoryResult result);
		FOnApiException OnInventoryApiError;
		UFUNCTION()
        void InventoryApiError(FApiException error);

		UPROPERTY()
        FOnPurchaseInstanceResult OnPurchaseInstanceResult;
        UFUNCTION()
        void PurchaseInstanceResult(FString result);
        UPROPERTY()
        FOnApiException OnPurchaseInstanceError;
        UFUNCTION()
        void OnPurchaseError(FApiException error);
		FEconomyItems currentEconomyItem;
                
};
