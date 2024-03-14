// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserItemManagementAPI/UserItemManagementHandler.h"
#include "../../DataHolders/UserInventoryHolder.h"
#include "Components/Button.h"
#include "../../Utilitys/APIEvents.h"
#include "UserAccountManagementAPI/UserAccountManagementHandler.h"
#include "Kismet/GameplayStatics.h"
#include "AvatarPresetsAPI/AvatarPresetsHandler.h"
#include "../../DataHolders/CurrentAvatarChanges.h"
#include "UserItemManagementAPI/UserItemManagementRequest.h"
#include "glTFRuntimeFunctionLibrary.h"
#include "Serialization/JsonSerializerMacros.h"
#include "../../DataHolders/DataHolder.h"
#include "../../AvatarLoader/AvatarHandler.h"
#include "Components/ScrollBox.h"
#include "Components/SizeBox.h"
#include "Components/VerticalBox.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CanvasPanel.h"
#include "CommonModels.h"
#include "../../DataHolders/UserDetailHolder.h"
#include "../../DataHolders/CommonFunction.h"
#include "DefaultAPI/DefaultHandler.h"
#include "Components/HorizontalBox.h"
#include "../../DataHolders/EconomyItemHolder.h"
#include "GameStructs.h"
#include "OnBoardingPanel.generated.h"

/**
 *
 */
UCLASS()
class AVATARYUGDEMO_API UOnBoardingPanel : public UUserWidget
{
    GENERATED_BODY()

protected:
    void NativeConstruct() override;

    UPROPERTY(meta = (BindWidget))
    class UButton *CreateCustomButton;

    UPROPERTY(meta = (BindWidget))
    class UButton *LetsBeginWithAvatarButton;

    UPROPERTY(meta = (BindWidget))
    class UButton *SelectGenderCloseButton;

    UPROPERTY(meta = (BindWidget))
    class USizeBox *BottomPanelSizeBox;

    UPROPERTY(meta = (BindWidget))
    class UVerticalBox *BottomScrollerVerticalBox;

    UPROPERTY(meta = (BindWidget))
    class UVerticalBox *BottomButtonVerticalBox;

    UPROPERTY(meta = (BindWidget))
    class USizeBox *TopTextSizeBox;

    UPROPERTY(meta = (BindWidget))
    class UButton *MaleButton;

    UPROPERTY(meta = (BindWidget))
    class UButton *FemaleButton;

public:
    UFUNCTION()
    void LoadOnBoardingPanelDetail();

    UFUNCTION()
    void LetsBeginWithAvatar();

    UFUNCTION()
    void CreateCustomAvatar();

    UFUNCTION()
    void CloseGenderPanel();

    UPROPERTY()
    AAvatarHandler *AvatarHandler;

    UPROPERTY()
    FOnGetAvatarPresetsResult GetAvatarPresetsResult;

    UFUNCTION()
    void OnGetAvatarPresetsResult(FGetAvatarPresetsResult result);

    // UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    // FGetAvatarPresetsResult presetsResult;

    FGetAvatarPresetsResult presetsResult;
    TArray<FGetAvatarPresetsResultDataInner> presetsQueue;
    TArray<FString> m_thumburls;
    TArray<FString> avatarUrl;
    TArray<AGltfFullActor *> m_SpawnedModels;

    UPROPERTY()
    FOnApiException GetAvatarPresetsError;

    UFUNCTION()
    void OnGetAvatarPresetsError(FApiException error);

    UPROPERTY()
    TArray<FGetAvatarPresetsResultDataInner> ArtifactList;

    UPROPERTY()
    TArray<FGetAvatarPresetsResultDataInner> ArtifactQueueList;

    UFUNCTION()
    void QueuePresetModel();

    UFUNCTION()
    void NewQueuePresetModel();

    UFUNCTION()
    void LoadArtifact(FGetAvatarPresetsResultDataInner artdata);

    UFUNCTION()
    void LoadArtifacts(FGetAvatarPresetsResultDataInner resultDataInner, int i);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    TSubclassOf<class AGltfFullActor> BP_GltfFullActorHome;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    TArray<AGltfFullActor *> GltfFullActorList;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    TArray<FString> meshURLList;
    UFUNCTION()
    void OnModelAssetHomeCallback(UglTFRuntimeAsset *asset);
    FglTFRuntimeHttpResponse onGltfModelHomeCallback;

    ADataHolder *DataHolder;

    int CurrentIndex;

    UPROPERTY()
    FOnGrantAvatarPresetItemsToUserResponse GrantAvatarPresetItemsToUserResponse;
    UFUNCTION()
    void OnGrantAvatarPresetItemsToUserResponse(FGrantAvatarPresetItemsToUserResponse result);
    UPROPERTY()
    FOnApiException GrantAvatarPresetItemsToUserError;
    UFUNCTION()
    void OnGrantAvatarPresetItemsToUserError(FApiException error);

    FString avatarDataStr;

    AUserDetailHolder *UserDetailHolder;

    FOnUpdateUserDemographicsResponse UpdateUserDemographicsResponse;

    FOnApiException UpdateUserDemographicsError;
    UFUNCTION()
    void OnUpdateUserDemographicsResponse(FUpdateUserDemographicsResponse result);

    UFUNCTION()
    void OnUpdateUserDemographicsError(FOnApiException error);

    FOnGrantAvatarToUserResponse GrantAvatarToUserResponse;
    FOnApiException GrantAvatarToUserError;
    UFUNCTION()
    void OnGrantAvatarToUserResponse(FGrantAvatarToUserResponse result);
    UFUNCTION()
    void OnGrantAvatarToUserError(FApiException error);

    UPROPERTY()
    FOnRenderAvatarImageResponse RenderAvatarImageResponse;
    UFUNCTION()
    void OnRenderAvatarImageResponse(FRenderAvatarImageResponse result);
    UPROPERTY()
    FOnApiException RenderAvatarImageError;
    UFUNCTION()
    void OnRenderAvatarImageError(FApiException error);
    FString avatarid;

    UPROPERTY()
    FOnGenerateAvatarMeshResponse GenerateAvatarMeshResponse;
    UFUNCTION()
    void OnGenerateAvatarMeshResponse(FGenerateAvatarMeshResponse result);
    UPROPERTY()
    FOnApiException GenerateAvatarMeshError;
    UFUNCTION()
    void OnGenerateAvatarMeshError(FApiException error);

    UPROPERTY()
    FOnUpdateDefaultAvatarIDResult UpdateDefaultAvatarIDResult;
    UFUNCTION()
    void OnUpdateDefaultAvatarIDResult(FUpdateDefaultAvatarIDResult result);
    UPROPERTY()
    FOnApiException UpdateDefaultAvatarIDError;
    UFUNCTION()
    void OnUpdateDefaultAvatarIDError(FApiException error);

    UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite)
    class UScrollBox *ScrollBox_166;

    UFUNCTION(BlueprintCallable)
    void LoadModelScrollerValue(int index);
    UPROPERTY(meta = (BindWidget))
    class UHorizontalBox *OnBoardingAvatarBox;

    UPROPERTY(EditAnywhere)
    TSubclassOf<class UUserWidget> AvatarButton;

    UFUNCTION()
    void ShowOnBoarding();

    UFUNCTION()
    void ShowNewOnBoarding();

    AAPIEvents *APIEvents;

    UPROPERTY()
    FAvatarPresetArtifacts artifactDatalist;
    // FDelegateOnChangeFlipbookIndex OnChangeIndex;

    // FDelegateOnClickIndex OnClickIndex;

    UFUNCTION()
    void ScrollOnClick(int value);

    UFUNCTION()
    void OnBoardingScreenOrientation(bool isLandscape);
    UFUNCTION()
    void MaleGenderSelected();

    UFUNCTION()
    void FemaleGenderSelected();

    UFUNCTION()
    void OnClickMaleFemaleButton(EGender gender);

    UFUNCTION()
    void ResetData();

    TArray<UUserWidget *> ButtonsH;

    FOnGetUserInventoryResult OnGetUserInventoryResult;
    UFUNCTION()
    void GetUserInventoryResult(FGetUserInventoryResult result);
    FOnApiException OnInventoryApiError;
    UFUNCTION()
    void InventoryApiError(FApiException error);

    UPROPERTY()
    FOnGetUsersAllAvatarsResult GetUsersAllAvatarsResult;
    UFUNCTION()
    void OnGetUsersAllAvatarsResult(FGetUsersAllAvatarsResult result);
    UPROPERTY()
    FOnApiException GetUsersAllAvatarsError;
    UFUNCTION()
    void OnGetUsersAllAvatarsError(FApiException error);

    AUserInventoryHolder *UserInventoryHolder;

    UPROPERTY()
    ACommonFunction *CommonFunctionHolder;

    UPROPERTY()
    ACurrentAvatarChanges *CurrentAvatarChangesHolder;

    TArray<FString> itemID;

    UPROPERTY(meta = (BindWidget))
    class UCanvasPanel *SelectGenderPanel;
};
