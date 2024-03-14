

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "AdsData.h"
#include "../../DataHolders/UserDetailHolder.h"
#include "../../DataHolders/UserInventoryHolder.h"
#include "Kismet/GameplayStatics.h"
#include "UserAccountManagementAPI/UserAccountManagementAPI.h"
#include "DefaultAPI/DefaultHandler.h"
#include "Components/ListView.h"
#include "AdsButtonsGrid.h"
#include "UserItemManagementAPI/UserItemManagementHandler.h"
#include "../../Utilitys/APIEvents.h"
#include "AdsPanel.generated.h"

/**
 *
 */
UCLASS()
class AVATARYUGDEMO_API UAdsPanel : public UUserWidget
{
	GENERATED_BODY()

protected:
	void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UButton *AP_BackButton;

public:
	UPROPERTY(meta = (BindWidget))
	class UListView *RewardAdsItemListView;

	UFUNCTION()
	void OnclickAP_BackButton();

	UFUNCTION()
	void LoadRewardedData();

	// TArray<FString> AdsIDs = { "01cefe6a-3619-4605-ba4f-546695adb17d", "da969855-c470-4567-8055-2b12cc829c50" };
	TArray<FString> AdsIDs = {"87dd639f-e812-448e-9950-46c852389e88", "5015655b-589e-4d7c-888f-c3d81a090b86"};
	TArray<FString> quelist;
	TArray<FAdsPlacementClass> getAdsPlacements;

	UFUNCTION()
	void OnQueData();

	UFUNCTION()
	void GetAdsPlacement(FString id);

	UPROPERTY()
	FOnGetAdsPlacementResponse OnGetAdsPlacementResponse;

	UFUNCTION()
	void GetAdsPlacementReply(FGetAdsPlacementResponse result);

	UPROPERTY()
	FOnApiException OnGetAdsPlacementApiError;

	UFUNCTION()
	void GetAdsPlacementError(FApiException result);

	UFUNCTION()
	void ShowRewardDataAfterLoad();

	UPROPERTY()
	FRewardItemClick OnRewardItemClick;

	UFUNCTION()
	void OnClickRewardsItemButton(FAdsPlacementClass item);

	FOnRecordAdsActivityResponse OnRecordAdsActivityResponse;

	UFUNCTION()
	void GetRecordAdsActivityReply(FRecordAdsActivityResponse result);

	FOnApiException OnRecordAdsActivityApiError;

	UFUNCTION()
	void GetRecordAdsActivityError(FApiException result);

	FOnGrantAdsRewardResponse OnGrantAdsRewardResponse;

	UFUNCTION()
	void GetGrantAdsRewardReply(FGrantAdsRewardResponse result);

	FOnApiException OnGrantAdsRewardApiError;

	UFUNCTION()
	void GetGrantAdsRewardError(FApiException result);

	FAdsPlacementClass currentItem;

	UPROPERTY()
	AUserDetailHolder *UserDetailHolder;

	UPROPERTY()
	AUserInventoryHolder *UserInventoryHolder;

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

	UPROPERTY()
	AAPIEvents *APIEvents;
};
