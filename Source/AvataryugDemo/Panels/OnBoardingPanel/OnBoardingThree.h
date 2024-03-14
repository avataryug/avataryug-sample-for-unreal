// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../DataHolders/UserInventoryHolder.h"
#include "Components/Button.h"
#include "UserItemManagementAPI/UserItemManagementHandler.h"
#include "Kismet/GameplayStatics.h"
#include "../../DataHolders/UserInventoryHolder.h"
#include "JsonObjectConverter.h"
#include "Serialization/JsonSerializerMacros.h"
#include "UserAccountManagementAPI/UserAccountManagementHandler.h"
#include "../../DataHolders/CurrentAvatarChanges.h"
#include "../../Utilitys/APIEvents.h"
#include "../../AvatarLoader/AvatarHandler.h"
#include "../../DataHolders/CommonFunction.h"
#include "../../DataHolders/DataHolder.h"
#include "AvatarPresetsAPI/AvatarPresetsModel.h"
#include "AvatarPresetsAPI/AvatarPresetsRequest.h"
#include "UserItemManagementAPI/UserItemManagementRequest.h"
#include "glTFRuntimeFunctionLibrary.h"
#include "../../DataHolders/UserDetailHolder.h"
#include "Components/ListView.h"
#include "Blueprint/UserWidget.h"
#include "OnBoardingThree.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSelectAvatarPreset, FGetAvatarPresetsResultDataInner, item);
/**
 *
 */
UCLASS()
class AVATARYUGDEMO_API UOnBoardingThree : public UUserWidget
{
	GENERATED_BODY()

protected:
	void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UButton *LetsBeginWithAvatarButton;

	UPROPERTY(meta = (BindWidget))
	class UButton *SelectGenderCloseButton;

	UPROPERTY(meta = (BindWidget))
	class UButton *MaleButton;

	UPROPERTY(meta = (BindWidget))
	class UButton *FemaleButton;

	UPROPERTY(meta = (BindWidget))
	class UListView *OnBoardingThreeListView;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel *SelectGenderPanel;

public:
    UPROPERTY()
	AAPIEvents *APIEvents;

    UPROPERTY()
    AUserInventoryHolder *UserInventoryHolder;
    
	UPROPERTY()
    AUserDetailHolder *UserDetailHolder;

    UPROPERTY()
    FOnSelectAvatarPreset OnSelectAvatarPreset;
        
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

	UFUNCTION()
	void OnClickMaleFemaleButton(EGender gender);

	UPROPERTY()
	FOnGetAvatarPresetsResult GetAvatarPresetsResult;

	UFUNCTION()
	void OnGetAvatarPresetsResult(FGetAvatarPresetsResult result);

	UPROPERTY()
	FOnApiException GetAvatarPresetsError;

	UFUNCTION()
	void OnGetAvatarPresetsError(FApiException error);

	UFUNCTION()
	void ShowPropItems();

	UFUNCTION()
	void LoadArtifact();

	FString avatarDataStr;

	FString avatarid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
	TSubclassOf<class AGltfFullActor> BP_GltfFullActorHome;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
	TArray<AGltfFullActor *> GltfFullActorList;

	UFUNCTION()
	void ResetData();

	UPROPERTY()
	AAvatarHandler *AvatarHandler;

	UPROPERTY()
	ADataHolder *DataHolder;

	UPROPERTY()
	ACommonFunction *CommonFunctionHolder;

	UPROPERTY()
	ACurrentAvatarChanges *CurrentAvatarChangesHolder;
        FGetAvatarPresetsResultDataInner SelectedPreset;
        void LoadCurrentAvatarData(TFunction<void()> oncomplete);

};
