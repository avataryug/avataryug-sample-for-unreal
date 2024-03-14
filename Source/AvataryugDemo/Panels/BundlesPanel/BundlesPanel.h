// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EconomyAPI/EconomyModel.h"
#include "../../Utilitys/APIEvents.h"
#include "EconomyAPI/EconomyRequest.h"
#include "BundlesData.h"
#include "Components/ListView.h"
#include "BundleDetailPanel.h"
#include "Kismet/GameplayStatics.h"
#include "BundlesPanel.generated.h"

/**
 * 
 */
UCLASS()
class AVATARYUGDEMO_API UBundlesPanel : public UUserWidget
{
	GENERATED_BODY()

	protected:
	void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UButton *Bundles_BackButton;

public:

	UPROPERTY()
    TArray<FEconomyBundle> m_EconomyBundles;

	UPROPERTY( meta = ( BindWidget ) )
	class UListView* BundlesItemListView;

	FOnGetEconomyBundlesResult GetEconomyBundlesResult ;

	UFUNCTION()
	void GetEconomyBundlesReply(FGetEconomyBundlesResult result);

	FOnApiException GetEconomyBundlesApiError;


	UFUNCTION()
	void GetEconomyBundlesError(FApiException result);

	void AddBundles(FGetEconomyBundlesResult result);

	bool IsBundlePresent(FString id);

	UFUNCTION()
	void LoadBundlePanelData();

	UFUNCTION()
	void ShowDataAfterLoad();

	UFUNCTION()
	void OnClickBundles_BackButton();

	 UPROPERTY(meta = (BindWidget))
     class UBundleDetailPanel *BP_BundlesDetailPanel;

	 AAPIEvents *APIEvents;
};
