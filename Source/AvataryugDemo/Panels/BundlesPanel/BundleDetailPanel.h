// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BundlesData.h"
#include "Components/ListView.h"
#include "../../DataHolders/UserDetailHolder.h"
#include "../../DataHolders/UserInventoryHolder.h"
#include "UserItemManagementAPI/UserItemManagementRequest.h"
#include "UserItemManagementAPI/UserItemManagementHandler.h"
#include "UserAccountManagementAPI/UserAccountManagementAPI.h"
#include "Components/Button.h"
#include "../../Utilitys/APIEvents.h"
#include "BundleDetailPanel.generated.h"

/**
 *
 */
UCLASS()
class AVATARYUGDEMO_API UBundleDetailPanel : public UUserWidget
{
	GENERATED_BODY()
	void NativeConstruct() override;

public:
	UPROPERTY(meta = (BindWidget))
	class UListView *BundlesDetailItemListView;

	UPROPERTY(meta = (BindWidget))
	class UButton *BDP_BackButton;

	UPROPERTY(meta = (BindWidget))
	class UButton *BDP_BuyButton;

	UFUNCTION()
	void OnClickBDP_BackButton();

	UFUNCTION()
	void ShowBundlesDetail(FEconomyBundle itemData);

	UPROPERTY()
	FEconomyBundle bundles;
	UPROPERTY()
	TArray<FContainerBundleContents> bundleContents;
	TArray<FContainerBase> bundlebases;
	FVirtualCurrencyReward virtualCurrrency;

	AAPIEvents *APIEvents;

	UPROPERTY()
	AUserDetailHolder *UserDetailHolder;

	UPROPERTY()
	AUserInventoryHolder *UserInventoryHolder;

	UFUNCTION()
	void BuyBundles();

	FOnPurchaseInstanceResult OnPurchaseInstanceResult;
	UFUNCTION()
	void GetPurchaseInstanceReply(FString result);
	FOnApiException OnPurchaseInstanceApiError;
	UFUNCTION()
	void GetPurchaseInstanceError(FApiException error);

	UPROPERTY()
	FOnGetUserInventoryResult OnUserInventoryResult;
	UFUNCTION()
	void GetUserInventoryReply(FGetUserInventoryResult result);
	FOnApiException OnUserInventoryApiError;
	UFUNCTION()
	void GetUserInventoryError(FApiException error);

	FOnConsumeInstanceResult OnConsumeInstanceResult;

	UFUNCTION()
	void GetConsumeInstanceReply(FConsumeInstanceResult result);

	FOnApiException OnConsumeInstanceApiError;

	UFUNCTION()
	void GetConsumeInstancetError(FApiException error);

	FOnGrantInstanceToUserResult OnGrantInstanceToUserResult;

	UFUNCTION()
	void GetGrantInstanceToUserReply(FGrantInstanceToUserResult result);

	FOnApiException OnGrantInstanceToUserError;

	UFUNCTION()
	void GetGrantInstanceToUserApiError(FApiException error);

	UPROPERTY()
	FOnGetUserInventoryResult OnConsumeUserInventoryResult;
	UFUNCTION()
	void GetConsumeUserInventoryReply(FGetUserInventoryResult result);
	FOnApiException OnConsumeUserInventoryApiError;
	UFUNCTION()
	void GetConsumeUserInventoryError(FApiException error);

	UPROPERTY()
	FOnGetUserAccountInfoResult OnUserAccountInfoResult;
	UFUNCTION()
	void GetUserAccountInfoReply(FGetUserAccountInfoResult result);
	UPROPERTY()
	FOnApiException OnUserAccountInfoApiError;
	UFUNCTION()
	void GetUserAccountInfoError(FApiException error);
};
