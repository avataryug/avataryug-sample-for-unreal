// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../Utilitys/APIEvents.h"
#include "Blueprint/UserWidget.h"
#include "EconomyAPI/EconomyModel.h"
#include "EconomyAPI/EconomyRequest.h"
#include "ContainersData.h"
#include "ContainerDetailPanel.h"
#include "ContainersPanel.generated.h"

/**
 *
 */
UCLASS()
class AVATARYUGDEMO_API UContainersPanel : public UUserWidget
{
    GENERATED_BODY()

protected:
    void NativeConstruct() override;

    UPROPERTY(meta = (BindWidget))
    class UButton *CP_BackButton;

public:
    UPROPERTY(meta = (BindWidget))
    class UListView *ContainerItemListView;

    FOnGetEconomyContainersResult GetEconomyContainersResult;

    UFUNCTION()
    void GetEconomyContainersReply(FGetEconomyContainersResult result);

    FOnApiException GetEconomyContainersApiError;

    UPROPERTY()
    TArray<FContainerDataClass> Containers;

    UFUNCTION()
    void GetEconomyContainersError(FApiException result);

    UFUNCTION()
    void LoadContainerPanelData();

    UFUNCTION()
    void ShowDataAfterLoad();
    UFUNCTION()
    bool IsContainerPresent(FString id);
    UFUNCTION()
    void AddContainers(FGetEconomyContainersResult result);

    UFUNCTION()
    void OnClickBackButton();

    AAPIEvents *APIEvents;

    UPROPERTY(meta = (BindWidget))
    class UContainerDetailPanel *BP_ContainerDetailPanel;
};
