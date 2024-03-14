// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Components/ListView.h"
#include "EconomyAPI/EconomyHandler.h"
#include "../../DataHolders/UserDetailHolder.h"
#include "../../DataHolders/UserInventoryHolder.h"
#include "EconomyAPI/EconomyRequest.h"
#include "UserItemManagementAPI/UserItemManagementHandler.h"
#include "../../Utilitys/APIEvents.h"
#include "StoreData.h"
#include "../../DataHolders/CommonFunction.h"
#include "Kismet/GameplayStatics.h"
#include "StorePanel.generated.h"

/**
 *
 */

UCLASS()
class AVATARYUGDEMO_API UStorePanel : public UUserWidget
{
	GENERATED_BODY()
protected:
	void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UButton *CurrencyStore_BackButton;

public:
	UPROPERTY(meta = (BindWidget))
	class UListView *CurrencyItemListView;

	UFUNCTION()
	void OnClickStoreBackButton();

	UFUNCTION()
	void StorePanelData();

	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
	FString StoreID = "252a6e92-9def-429c-81ec-bad861493510";

	// FGetEconomyStoresResult

	//=================================
	FGetStoreItemsByIDResult getEconomyStore;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
	FStoreContents storecontents;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
	FStoreContent newstoreContent;

	TArray<FStoreContent> QueueList;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
	TArray<FMyBundleContents> bundleContents;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
	TArray<FMyContainerBase> Currencies;

	UFUNCTION()
	void OnQueueData();

	UFUNCTION()
	void LoadStoreItemDetail(FStoreContent data, int32 index);

	FOnGetEconomyBundleByIDResult GetEconomyBundleByIDResult;

	UFUNCTION()
	void GetEconomyBundleByIDReply(FGetEconomyBundleByIDResult result);

	FOnApiException GetEconomyBundleByIDApiError;

	UFUNCTION()
	void GetEconomyBundleByIDError(FApiException result);

	UFUNCTION()
	void LoadCurrencyData();

	UPROPERTY()
	FOnSelectedIndex SelectedIndexReceived;

	UFUNCTION()
	void PurchaseItem(int32 index);

	FOnPurchaseInstanceResult OnPurchaseInstanceResult;

	UFUNCTION()
	void GetPurchaseInstanceReply(FString result);

	FOnApiException OnPurchaseInstanceApiError;

	UFUNCTION()
	void GetPurchaseInstanceError(FApiException result);

	AUserDetailHolder *UserDetailHolder;

	FOnGetUserInventoryResult OnGetUserInventoryResult;
	UFUNCTION()
	void GetUserInventoryResult(FGetUserInventoryResult result);
	FOnApiException OnInventoryApiError;
	UFUNCTION()
	void InventoryApiError(FApiException error);

	AUserInventoryHolder *UserInventoryHolder;

	AAPIEvents *APIEvents;

	UFUNCTION()
	void ConsumeInstance(FStoreContent content, int32 qut, FString id);

	int32 indexRedceived;

	FOnConsumeInstanceResult OnConsumeInstanceResult;

	UFUNCTION()
	void OnConsumeInstanceReply(FConsumeInstanceResult result);

	FOnApiException OnConsumeInstanceError;

	UFUNCTION()
	void OnConsumeInstancetApiError(FApiException error);

	FOnGrantInstanceToUserResult OnGrantInstanceToUserResult;

	UFUNCTION()
	void OnGrantInstanceToUserReply(FGrantInstanceToUserResult result);

	FOnApiException OnGrantInstanceToUserError;

	UFUNCTION()
    void OnGrantInstanceToUserApiError(FApiException error);

    UPROPERTY()
    ACommonFunction *CommonFunction;
};
