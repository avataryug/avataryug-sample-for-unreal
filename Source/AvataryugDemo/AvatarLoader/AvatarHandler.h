// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "CoreMinimal.h"
#include "GameStructs.h"
#include "GltfFullActor.h"
#include "../Utilitys/APIEvents.h"
#include "GameEnums.h"
#include "EmptyActor.h"
#include "../DataHolders/UserDetailHolder.h"
#include "../DataHolders/EconomyItemHolder.h"
#include "../DataHolders/CommonFunction.h"
#include "EconomyAPI/EconomyModel.h"
#include "../DataHolders/DataHolder.h"
#include "EconomyAPI/EconomyHandler.h"
#include "CustomizeAvatarLoader.h"
#include "Engine/ExponentialHeightFog.h"
#include "AvatarHandler.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPropProcessed);
UCLASS()
class AVATARYUGDEMO_API AAvatarHandler : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAvatarHandler();

	static AAvatarHandler *GetInstance();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyCategory")
	// FTransform m_OnBoardingModelParent;

	// UFUNCTION(BlueprintCallable, Category = "MyCategory")
	// FTransform GetOnBoardingModelParent() const
	// {
	//     return m_OnBoardingModelParent;
	// }

	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyCategory")
	// FTransform m_CustomizeParent;

	// UFUNCTION(BlueprintCallable, Category = "MyCategory")
	// FTransform GetCustomizeParent() const
	// {
	//     return m_CustomizeParent;
	// }

	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyCategory")
	// FTransform m_CustomizeDefaultParent;

	// UFUNCTION(BlueprintCallable, Category = "MyCategory")
	// FTransform GetCustomizeDefaultParent() const
	// {
	//     return m_CustomizeDefaultParent;
	// }
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyCategory")
	AExponentialHeightFog *Foger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyCategory")
	USceneComponent *m_DummyTestParent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyCategory")
	AEmptyActor *CurrentModel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
	TSubclassOf<class AEmptyActor> BP_EmptyActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
	TSubclassOf<class ACustomizeAvatarLoader> BP_CustomizeAvatarLoader;

	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
	// ACustomizeAvatarLoader *m_CustomizeAvatarLoader;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
	AHeadActor *spawnedHeadActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyCategory")
	AEmptyActor *m_AllModelParent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
	AEmptyActor *SpawnedOnBoardingParent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
	ACustomizeAvatarLoader *SpawnedCustomizeParent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
	ACustomizeAvatarLoader *HandlerSpawnedCustomizeDefaultParent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
	ACustomizeAvatarLoader *SpawnedCustomizeDefaultParentClone;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyCategory")
	EAppType typeOfPlatform = EAppType::GAME;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyCategory")
	EMonitizeType TypeOfMontization = EMonitizeType::Monitize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyCategory")
	EOnBoarding typeOfOnBoarding = EOnBoarding::OnBoarding1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyCategory")
	bool isMonetize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyCategory")
	bool CreateCustomModel = false;

	// Store all selected body items
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyCategory")
	TArray<FEconomyItems> CurrentSelectedBodyParts;

	// Store current selected item
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyCategory")
	FEconomyItems CurrentSelectedProp;

	// Queue for loading economy item detail
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyCategory")
	TArray<FProp> Props;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyCategory")
	ACustomizeAvatarLoader *CustomizeDefaultAvatarLoader;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyCategory")
	ACustomizeAvatarLoader *customizeAvatarLoader;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyCategory")
	ACustomizeAvatarLoader *ForCustomizeAvatar;

	UPROPERTY()
	AGltfFullActor *GltfFullActorHome;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
	TSubclassOf<class AGltfFullActor> BP_GltfFullActorHome;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Current Selected")
	FEconomyItems currentLoadEconomyItem;


	UPROPERTY()
	AAPIEvents *APIEvents;

	UPROPERTY()
	AUserDetailHolder *UserDetailHolder;

	UFUNCTION()
	void LoadParents();

	void LoadHomePanelModel(FString modelurl,TFunction<void()> OnComplete);



	UFUNCTION()
	void SetModelParentEnable(EModelParent modelParent);

	UFUNCTION()
	void RotateActor(float DeltaTime, FVector TouchLocation);
	
	UFUNCTION()
	void RotateOnSwipe(FVector SwipeDirection);

	UFUNCTION()
	void LoadTheDefaultHead();

	UFUNCTION()
	void ResetToCurrentSelected();

	UFUNCTION()
	void SetCurrentAvatarDetail();

	UFUNCTION()
	void DelayedFunction();

	UFUNCTION()
	void LoadInventoryPropDetail();
	void LoadInventoryPropDetail(TFunction<void()> OnComplete);

	UFUNCTION()
	void OnQueProp();
	void OnQueProp(TFunction<void()> OnComplete);

	UFUNCTION()
	void LoadPropDetail(FProp prop);

	void LoadPropDetail(FProp prop, TFunction<void()> OnComplete);

	void ApiEvents_ResetToDefault(TFunction<void()> OnComplete);

	AEconomyItemHolder *EconomyItemHolder;

	ACurrentAvatarChanges *AvatarChangesInstance;

	ADataHolder *DataHolder;

	UPROPERTY()
	ACommonFunction *CommonFunctionHolder;

	FOnGetEconomyItemsByIDResult OnGetEconomyItemsByIDResult;

	UFUNCTION()
	void GetEconomyItemsByIDReply(FGetEconomyItemsByIDResult result);

	FOnApiException OnGetEconomyItemsByIDError;

	UFUNCTION()
	void GetEconomyItemsByIDApiError(FApiException error);

	FOnGetEconomyItemsResult OnGetEconomyItemsResult;
	UFUNCTION()
	void OnReceiveEconomyItems(FGetEconomyItemsResult result);

	FOnApiException OnGetEconomyItemsError;
	UFUNCTION()
	void OnReceiveEconomyItemsError(FApiException result);

	UFUNCTION()
	void RemovePart(FEconomyItems item);

	void AddCurrentBodyPartWithid(FEconomyItems item);

	UFUNCTION()
	void AddCurrentBodyPart(FEconomyItems item);

	UFUNCTION()
	void LogOut();

	UFUNCTION()
	void DelayDuplicateModel();

	UFUNCTION()
	void DuplicateModel();

	UPROPERTY(BlueprintAssignable, Category = "Props")
	FOnPropProcessed OnPropProcess;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyCategory")
	AEmptyActor *HomeModelParent;
UFUNCTION()
void OnGetHorizontalInput(float value);
UFUNCTION()
void OnGetVerticalInput(float value);
UPROPERTY()
bool stopRotate;
private:
	static AAvatarHandler *SingletonInstance;
};
