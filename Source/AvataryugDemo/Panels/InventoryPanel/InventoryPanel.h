// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../DataHolders/UserInventoryHolder.h"
#include "../../DataHolders/UserDetailHolder.h"
#include "UserItemManagementAPI/UserItemManagementModels.h"
#include "UserItemManagementAPI/UserItemManagementRequest.h"
#include "UserItemManagementAPI/UserItemManagementHandler.h"
#include "UserAccountManagementAPI/UserAccountManagementAPI.h"
#include "JsonObjectConverter.h"
#include "EconomyAPI/EconomyHandler.h"
#include "../ContainersPanel/ContainersData.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "../../Utilitys/APIEvents.h"
#include "JsonUtilities.h"
#include "InventoryItemButton.h"
#include "Components/VerticalBox.h"
#include "Components/ListView.h"
#include "InventoryPanel.generated.h"

/**
 *
 */
UCLASS()
class AVATARYUGDEMO_API UInventoryPanel : public UUserWidget
{
	GENERATED_BODY()

protected:
	void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UButton *BackButton;

	// UPROPERTY(meta = (BindWidget))
	// class UVerticalBox *InventoryItemParent;

public:
	void LoadInventoryData();

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> InventoryItemButton;

	UPROPERTY()
	TArray<UInventoryItemButton *> InventoryItemButtonList;

	AAPIEvents *APIEvents;

	UPROPERTY(meta = (BindWidget))
	class UListView *InvetroyItemListView;

	UPROPERTY()
	AUserDetailHolder *UserDetailHolder;

	UPROPERTY()
	AUserInventoryHolder *UserInventoryHolder;
	UPROPERTY()
	FOnInventoryItemClick OnInvebtoryItemClick;
	UFUNCTION()
	void OnClickInventoryItemButton(FGetUserInventoryResultDataInner item);

	UFUNCTION()
	void OnClickBackButton();

	TArray<FGetUserInventoryResultDataInner> inventory;

	FGetUserInventoryResultDataInner currentItem;

	FGetEconomyContainerByIDResult containerItem;

	FOnGetEconomyContainerByIDResult OnEconomyContainerByIDResult;

	FGetEconomyBundleByIDResult bundleItem;
	// FContainerBundleContents containerContents;

	UFUNCTION()
	void GetEconomyContainerByIDReply(FGetEconomyContainerByIDResult result);

	FOnApiException OnEconomyContainerByIDApiError;

	UFUNCTION()
	void GetEconomyContainerByIDError(FApiException error);

	FOnConsumeInstanceResult OnConsumeInstanceResult;

	UFUNCTION()
	void GetConsumeInstanceReply(FConsumeInstanceResult result);

	FOnApiException OnConsumeInstanceApiError;

	UFUNCTION()
	void GetConsumeInstancetError(FApiException error);

	UFUNCTION()
	static FContainerBundleContents GetContainerContents(FGetEconomyContainerByIDResult &Result);

	UFUNCTION()
	static FContainerBundleContents GetBundleContents(FGetEconomyBundleByIDResult &Result);

	FOnGrantInstanceToUserResult OnGrantInstanceToUserResult;

	UFUNCTION()
	void GetGrantInstanceToUserReply(FGrantInstanceToUserResult result);

	FOnApiException OnGrantInstanceToUserApiError;

	UFUNCTION()
	void GetGrantInstanceToUserError(FApiException error);

	UPROPERTY()
	FOnGetUserInventoryResult OnUserInventoryResult;
	UFUNCTION()
	void GetUserInventoryReply(FGetUserInventoryResult result);
	FOnApiException OnUserInventoryApiError;
	UFUNCTION()
	void GetUserInventoryError(FApiException error);

	UPROPERTY()
	FOnGetUserAccountInfoResult OnUserAccountInfoResult;
	UFUNCTION()
	void GetUserAccountInfoReply(FGetUserAccountInfoResult result);
	UPROPERTY()
	FOnApiException OnUserAccountInfoApiError;
	UFUNCTION()
	void GetUserAccountInfoError(FApiException error);

	FOnGetEconomyBundleByIDResult OnGetEconomyBundleByIDResult;

	UFUNCTION()
	void GetEconomyBundleByIDReply(FGetEconomyBundleByIDResult result);

	FOnApiException OnGetEconomyBundleByIDApiError;

	UFUNCTION()
	void GetEconomyBundleByIDError(FApiException error);

	FOnConsumeInstanceResult OnConsumeBundleInstanceResult;

	UFUNCTION()
	void GetConsumeBundleInstanceReply(FConsumeInstanceResult result);

	FOnApiException OnConsumeBundleInstanceApiError;

	UFUNCTION()
	void GetConsumeBundleInstancetError(FApiException error);
};
