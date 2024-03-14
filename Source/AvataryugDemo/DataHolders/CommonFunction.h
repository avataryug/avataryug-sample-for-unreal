// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../DataHolders/UserDetailHolder.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DefaultAPI/DefaultHandler.h"
#include "../DataHolders/CurrentAvatarChanges.h"
#include "../DataHolders/UserDetailHolder.h"
#include "CommonModels.h"
#include "AvatarPresetsAPI/AvatarPresetsHandler.h"
#include "AvatarPresetsAPI/AvatarPresetsModel.h"
#include "../Utilitys/APIEvents.h"
#include "../DataHolders/UserInventoryHolder.h"
#include "CommonFunction.generated.h"

UCLASS()
class AVATARYUGDEMO_API ACommonFunction : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACommonFunction();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	EPlatform GetPlatform();

	UFUNCTION()
	FString GetPlatformAsString();

	UFUNCTION()
	int32 GetPlatformAsInt();

	UFUNCTION()
	void SetCurrentAvatarDetail();

	// FOnComplete OnComplete;
	// UPROPERTY()
	// FOnIsSameModel isSameModel;

	UFUNCTION(BlueprintCallable, Category = "Avatar")
	void UpdateDefaultAvatarID(FString AvatarID);

	UFUNCTION()
	void CheckAvatarDifference();

	void CheckAvatarDifference(TFunction<void(bool)> OnComplete);

	void GetCommonUserInventory(TFunction<void()> InventoryLoaded);

	void UpdateDefaultAvatarID(FString avatarid, TFunction<void()> Callback);

	void CallFun(TFunction<void(FString)> Callback);

	void SyncAvatar(FString platform, TFunction<void()> OnComplete);

	void GetUserAccountInfo(TFunction<void(FGetUserAccountInfoResult)> OnComplete);

	void GetUserAccountInfo(TFunction<void()> OnComplete);

	void GetUserAllAvatars(TFunction<void()> OnComplete);

	void GetUserAllAvatars(TFunction<void(FGetUsersAllAvatarsResult)> OnComplete);

	void RenderImage(FString avatarid, TFunction<void(FRenderAvatarImageResponse)> OnComplete);

	void RenderImageBG(FString avatarid);

	void GenerateMesh(FString avatarid, TFunction<void(FGenerateAvatarMeshResponse)> OnComplete);

	UFUNCTION()
	int CheckMissingThumbnailAndAvatar();

	UPROPERTY()
	FOnUpdateDefaultAvatarIDResult UpdateDefaultAvatarIDResult;

	UPROPERTY()
	FOnApiException UpdateDefaultAvatarIDError;

	AUserDetailHolder *UserDetailHolder;

	UPROPERTY()
	ACurrentAvatarChanges *AvatarCurrentChangesHolder;

	AUserInventoryHolder *UserInventoryHolder;

	AAPIEvents *APIEvents;

        bool isSameModels = true;
        void LoadCurrentAvatarData(TFunction<void()> oncomplete);
};
