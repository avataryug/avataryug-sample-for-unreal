// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../../Utilitys/APIEvents.h"
#include "../../DataHolders/DataHolder.h"
#include "UserItemManagementAPI/UserItemManagementHandler.h"
#include "../../DataHolders/UserInventoryHolder.h"
#include "Components/ScrollBox.h"
#include "Components/CanvasPanel.h"
#include "../../AvatarLoader/AvatarHandler.h"
#include "../../DataHolders/CurrentAvatarChanges.h"
#include "UserAccountManagementAPI/UserAccountManagementHandler.h"
#include "../../DataHolders/UserDetailHolder.h"
#include "AvatarPresetsAPI/AvatarPresetsModel.h"
#include "AvatarPresetsAPI/AvatarPresetsRequest.h"
#include "UserItemManagementAPI/UserItemManagementRequest.h"
#include "glTFRuntimeFunctionLibrary.h"
#include "Components/Button.h"
#include "OnBoardingTwoPanel.generated.h"

/**
 *
 */
UCLASS()
class AVATARYUGDEMO_API UOnBoardingTwoPanel : public UUserWidget
{
	GENERATED_BODY()

protected:
	void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UButton *LetsBeginWithAvatarButton;

	UPROPERTY(meta = (BindWidget))
	class UButton *SelectGenderCloseButton;

	UPROPERTY(meta = (BindWidget))
	class UButton *CreateCustomButton;

	UPROPERTY(meta = (BindWidget))
	class UButton *MaleButton;

	UPROPERTY(meta = (BindWidget))
	class UButton *FemaleButton;
	// UPROPERTY( meta = ( BindWidget ) )
	// class UListView *OnBoardingThreeListView;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel *SelectGenderPanel;

	UPROPERTY(meta = (BindWidget))
	class UScrollBox *OnboardingTwoScrollBox_1;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> AvatarButton;

public:
	AAPIEvents *APIEvents;

	AUserInventoryHolder *UserInventoryHolder;
	AUserDetailHolder *UserDetailHolder;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MyCategory")
	int32 scrollerindex;

	UPROPERTY()
	TArray<FGetAvatarPresetsResultDataInner> ArtifactList;

	UFUNCTION()
	void LetsBeginWithAvatar();

	UFUNCTION()
	void LoadOnBoardingPanelDetail();

	UFUNCTION()
	void CreateCustomAvatar();

	UFUNCTION()
	void MaleGenderSelected();

	UFUNCTION()
	void FemaleGenderSelected();

	UFUNCTION()
	void CloseGenderPanel();

	UPROPERTY()
	FOnGetAvatarPresetsResult GetAvatarPresetsResult;

	UFUNCTION()
	void OnGetAvatarPresetsResult(FGetAvatarPresetsResult result);

	UPROPERTY()
	FOnApiException GetAvatarPresetsError;

	UFUNCTION()
	void OnGetAvatarPresetsError(FApiException error);

	UFUNCTION()
	void OnClickMaleFemaleButton(EGender gender);

	UFUNCTION()
	void ShowPropItems();

	UFUNCTION()
	void LoadArtifact();

	FString avatarDataStr;

	FString avatarid;

	TArray<UUserWidget *> ButtonsH;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
	TSubclassOf<class AGltfFullActor> BP_GltfFullActorHome;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
	TArray<AGltfFullActor *> GltfFullActorList;

	// UFUNCTION()
	// void OnModelAssetHomeCallback(UglTFRuntimeAsset *asset);

	UFUNCTION()
	void ResetData();

	// FglTFRuntimeHttpResponse onGltfModelHomeCallback;

	UPROPERTY()
	FOnGrantAvatarPresetItemsToUserResponse GrantAvatarPresetItemsToUserResponse;
	UFUNCTION()
	void OnGrantAvatarPresetItemsToUserResponse(FGrantAvatarPresetItemsToUserResponse result);

	UPROPERTY()
	FOnApiException GrantAvatarPresetItemsToUserError;
	UFUNCTION()
	void OnGrantAvatarPresetItemsToUserError(FApiException error);

	UPROPERTY()
	FOnGrantAvatarToUserResponse GrantAvatarToUserResponse;
	UFUNCTION()
	void OnGrantAvatarToUserResponse(FGrantAvatarToUserResponse result);
	UPROPERTY()
	FOnApiException GrantAvatarToUserError;
	UFUNCTION()
	void OnGrantAvatarToUserError(FApiException error);

	UPROPERTY()
	FOnUpdateDefaultAvatarIDResult UpdateDefaultAvatarIDResult;
	UFUNCTION()
	void OnUpdateDefaultAvatarIDResult(FUpdateDefaultAvatarIDResult result);
	UPROPERTY()
	FOnApiException UpdateDefaultAvatarIDError;
	UFUNCTION()
	void OnUpdateDefaultAvatarIDError(FApiException error);

	UPROPERTY()
	FOnGetUserInventoryResult OnGetUserInventoryResult;
	UFUNCTION()
	void GetUserInventoryResult(FGetUserInventoryResult result);
	UPROPERTY()
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

	UPROPERTY()
	AAvatarHandler *AvatarHandler;

	UPROPERTY()
	ADataHolder *DataHolder;

	UPROPERTY()
	ACurrentAvatarChanges *CurrentAvatarChangesHolder;
	UPROPERTY()
        ACommonFunction *CommonFunctionHolder;
        void LoadCurrentAvatarData(TFunction<void()> oncomplete) ;
};
