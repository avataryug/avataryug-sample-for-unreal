// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameStructs.h"
#include "HeadActor.h"
#include "GltfFullActor.h"
#include "../DataHolders/LocalDataFunctionLibrary.h"
#include "../CameraController/CameraControllerPawn.h"
#include "../DataHolders/UserDetailHolder.h"
#include "../Utilitys/LoadTextureFromURL.h"
#include "../Utilitys/APIEvents.h"
#include "../DataHolders/EconomyItemHolder.h"
#include "../DataHolders/DataHolder.h"
#include "../AvatarLoader/GltfActor.h"
#include "../Utilitys/CustomizeFacePoint.h"
#include "GameStructs.h"
#include "../DataHolders/CurrentAvatarChanges.h"
#include "../AvatarLoader/GltfStaticActorPoint.h"
#include "../DataHolders/CurrentAvatarChanges.h"
#include "AvatarLoaderBase.generated.h"

DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnLoadSkinToneNewCallback, UTexture *, texture, FString, category);

UCLASS()
class AVATARYUGDEMO_API AAvatarLoaderBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAvatarLoaderBase();

	UFUNCTION()
	void SetParentPoint();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
	TSubclassOf<class AEmptyActor> BP_EmptyActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
	AEmptyActor *SpawnedOnboardingParent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
	AEmptyActor *SpawnedHomeParent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
	AEmptyActor *SpawnedCustomizeParent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
	AEmptyActor *SpawnedCustomizeDefaultParent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
	AEmptyActor *SpawnedCustomizeDefaultParentClone;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
	TSubclassOf<class AEmptyActor> Bp_SpawnedCustomizeDefaultParentClone;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
	AEmptyActor *spawnedNewCustomizeActor;

	UFUNCTION()
	void SetParentVisibility(bool onbaording, bool homeparent, bool customizeparent);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyCategory)
	int count = 0;

	UPROPERTY()
	ACameraControllerPawn *CameraControllerPaw;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyCategory)
	TSubclassOf<class AGltfStaticActorPoint> BucketPoint_BP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyCategory)
	TArray<AGltfStaticActorPoint *> cloneBodyPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyCategory)
	TArray<FModelDataResponce> cloneDefaultModelList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "currentData")
	AGltfActor *HairModel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "currentData")
	AGltfActor *HeadwearModel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AvatarLocalData")
	UTexture *DefaultBodySkinTone;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AvatarLocalData")
	UTexture *DefaultFaceSkinTone;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AvatarLocalData")
	UTexture *DefaultEyebrowTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AvatarLocalData")
	UTexture *DefaultLipsTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AvatarLocalData")
	UTexture *DefaultEyeballTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AvatarLocalData")
	UTexture *EmptyTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AvatarLocalData|Material")
	class UMaterial *BodyMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AvatarLocalData|Material")
	UMaterialInstanceDynamic *BodyDynamicMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AvatarLocalData|Material")
	class UMaterial *HeadMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AvatarLocalData|Material")
	UMaterialInstanceDynamic *HeadDynamicMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AvatarLocalData|Material")
	class UMaterial *HairMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AvatarLocalData|Material")
	UMaterialInstanceDynamic *HairDynamicMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AvatarLocalData|Material")
	class UMaterial *EyeballMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AvatarLocalData|Material")
    UMaterialInstanceDynamic *EyeballDynamicMaterial;
        
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AvatarLocalData|Material")
    class UMaterial *MouthMaterial;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AvatarLocalData|Material")
    UMaterialInstanceDynamic *MouthDynamicMaterial;
        

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AvatarLocalData|Default Color")
	FString DefaultFacialHairColor = "#3b3b3b";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AvatarLocalData|Default Color")
	FString DefaultEyebrowColor = "#272727";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AvatarLocalData|Default Color")
	FString DefaultHairColor = "#2a2a2a";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AvatarLocalData|Default Color")
	FString DefaultLipColor = "#ff9e7e";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AvatarLocalData|Default Color")
	FString DefaultMaleLipColor = "#ff9e7e";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "currentData")
	FEconomyItems currentTopData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "currentData")
	FEconomyItems currentWristwearData = FEconomyItems();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "currentData")
	FEconomyItems currentBottomData = FEconomyItems();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "currentData")
	FEconomyItems currentOutfitData = FEconomyItems();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "currentData")
	FEconomyItems currentFootwearData = FEconomyItems();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "currentData")
	FEconomyItems currentHandwearData = FEconomyItems();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "currentData")
	FEconomyItems currentLispData = FEconomyItems();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "currentData")
	FEconomyItems currentfacialHairData = FEconomyItems();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "currentData")
	FEconomyItems currentEyeballData = FEconomyItems();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "currentData")
	FEconomyItems currentEyebrowData = FEconomyItems();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "currentData")
	FEconomyItems currentHairData = FEconomyItems();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "currentData")
	FEconomyItems currentHeadwearData = FEconomyItems();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "currentData")
	FEconomyItems currentFaceshapeData = FEconomyItems();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "currentData")
	FEconomyItems currentEarshapeData = FEconomyItems();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "currentData")
	FEconomyItems currentNoseshapeData = FEconomyItems();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "currentData")
	FEconomyItems currentEyebrowshapeData = FEconomyItems();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "currentData")
	FEconomyItems currentEyeshapeData = FEconomyItems();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "currentData")
	FEconomyItems currentLipshapeData = FEconomyItems();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "currentData")
	FEconomyItems currentskintoneData = FEconomyItems();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "currentData")
	FExpression currentExpressionData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "currentData")
	TArray<AGltfStaticActorPoint *> bodyPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
	TArray<AGltfActor *> LoadedModelList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
	TArray<AGltfActor *> CloneLoadedModelList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "currentData")
	TArray<FModelDataResponce> loadDefaultModellist;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyCategory)
	TSubclassOf<class AGltfActor> GltfActor_BP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
	TSubclassOf<class AGltfFullActor> BP_GltfFullActorHome;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
	TSubclassOf<class ACustomizeFacePoint> BP_CustomizeFacePoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "currentData")
	TArray<FModelDataResponce> defaultModelList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "currentData")
	AGltfActor *TopToDestroy;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "currentData")
	AGltfActor *BottomToDestroy;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "currentData")
	AGltfActor *HandwearToDestroy;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "currentData")
	AGltfActor *FootwearToDestroy;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "currentData")
	AGltfActor *OutfitToDestroy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "currentData")
	TArray<AGltfActor *> GltfModelList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "currentData")
	TArray<FLoadedTattoo> lastLoadedTattoos;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "currentData")
	FExpression currentexpression = FExpression();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "currentData")
	FClip currentClip = FClip();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "currentData")
	bool addDelay = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "currentData")
	bool isResetToCurrent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "currentData")
	FString HeadCoreBuck = "";

	UPROPERTY(EditAnywhere, Category = "CustomizeAvatarLoader")
	TSubclassOf<class ACustomizeAvatarLoader> DefaultCustomizeParentAvatarLoader;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "currentData")
	TSubclassOf<class AHeadActor> BP_HeadActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "currentData")
	AHeadActor *spawnedHeadActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "currentData")
	AHeadActor *spawnedCustomizeHeadActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "currentData")
	TArray<FEconomyItems> networkModelQueue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CustomizeAvatarLoader")
	EGender Gender;

	UFUNCTION()
	EGender GetGender();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void LoadStartData();

	UFUNCTION()
	void LoadHeadModel();

	void LoadHeadModel(TFunction<void()> OnComplete);

	UFUNCTION()
	void LoadCustomizeModel();

	UFUNCTION()
	void DelayFunction();

	UFUNCTION()
	void ResetToDefaultData();

	UFUNCTION()
	void AddLoadingDelay();




	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    TArray<ACustomizeFacePoint *> SpawnedFacePoints;
	void FunctionToCallAfterOneSecond(TFunction<void()> OnComplete);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyCategory)
	FModelDataResponce modelDataRes;

	// TArray<ACustomizeFacePoint *> SpawnedFacePoints;

	void DownloadDefaultModel(FModelDataResponce modelData, TFunction<void()> OnComplete);
	UFUNCTION()
	void OnDefaultModelCallback(UglTFRuntimeAsset *asset);

	UFUNCTION()
	void TestAddingDelay();

	UFUNCTION()
	void ResetAvatarLoader();

	UFUNCTION()
	void CheckMissingModelAfterRemovingSameModel(FEconomyItems modelData);

	UFUNCTION()
	void ResetData();

	UFUNCTION()
	void ClearCurrent();

	UFUNCTION()
	void CheckMissingAfterModelLoad(FEconomyItems modelData);

	UFUNCTION()
	void LoadDetaultModels();
	void AddNewDefaultBodyPart(AGltfActor *gltfActor, FModelDataResponce modelDataResponce, TFunction<void()> OnComplete);
	UFUNCTION()
	void ShowHideItems(bool show);
	UFUNCTION()
	void ShowClip(FClip clip);
	void OnLoadQueueDefaultModel(TFunction<void()> OnComplete);


    void LoadTwoDHair(FEconomyItems modelData, TFunction<void()> complete);

	UFUNCTION()
	void AddDefaultBodyPart(AGltfActor *gltfActor, FModelDataResponce modelDataResponce);

	UFUNCTION()
	void DuplicateActor(AGltfActor *gltfActor, FModelDataResponce modelDataResponce);

	UFUNCTION()
	void SetExpression(FExpression ExpressionItem);

	UFUNCTION()
	void ResetExpression();

	UFUNCTION()
	void ChangeBlendPointValue(FString Shapename, float Slidervalue);

	UFUNCTION()
	void LoadNetworkModel(FEconomyItems modelData);

	void OnLoadQueModel();

	void DownloadNetworkModel(FEconomyItems modelData);

	UFUNCTION()
	void DownloadTattos(FEconomyItems modelData);



	UFUNCTION()
	FString GetBucketname(FString corebutckt);

	UPROPERTY()
	FEconomyItems currentClickTatto;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Current Selected")
	FEconomyItems currentClickEconomyItem;

	UPROPERTY()
	FOnReceiveData FOnReceiveModelData;

	UPROPERTY()
	FOnReceiveData FOnReceiveFaceModelData;

	UPROPERTY()
	FOnReceiveData FOnReceiveModelBodywearData;

	UPROPERTY();
	AGltfActor *currentWristwearActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
	TSubclassOf<class AGltfActor> BP_GltfActor;

	UFUNCTION()
	void OnProcessModelTexture();

	void LoadBodyPart(FEconomyItems modelData);

	UFUNCTION()
	void ResetToDetaultModel();

	UFUNCTION()
	void ResetToCurrentSelected();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
	int FaceBody;

	UFUNCTION()
	void OnReceiveFaceModelData(TArray<uint8> byte);

	UFUNCTION()
	void OnReceiveModelBodywearData(TArray<uint8> byte);

	UFUNCTION()
	void AddNetworkBodywearPart(AGltfActor *gltfActor, FEconomyItems modelData);

	FString Blendshapecat;
	UFUNCTION()
	void LoadBodywearPart(FEconomyItems modelData);

	UFUNCTION()
	bool IsBodyCategory(FEconomyItems modelData);

	UFUNCTION()
	bool IsTattooCategory(FEconomyItems modelData);

	UFUNCTION()
	void SpawnCustomizePoint(FFacePoint point);

	UFUNCTION()
	void SetBodyPartColor(FLinearColor OutColor, FString category);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
	FLinearColor outColor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
	FLinearColor tempcat;
	bool IsBlendshapeCategory(FEconomyItems modelData);

	UFUNCTION()
	void ResetBlendShapesWeight(USkeletalMeshComponent *SkeletalMeshComponent);

	UFUNCTION()
	void SetBlendShapesWeight(USkeletalMeshComponent *SkeletalMeshComponent, FString bucketname);

	UFUNCTION()
	bool IsFace2DCategory(FEconomyItems modelData);


	UFUNCTION()
	void LoadSkinTone(FEconomyItems modelData);

	UFUNCTION()
	void OnReceiveModelByte(TArray<uint8> byte);

	UFUNCTION()
	void AddNetworkFacePart(AGltfActor *gltfActor, FEconomyItems modelData);

	UFUNCTION()
	void LoadBlendshape(FEconomyItems modelData);

	UFUNCTION()
	void LoadHead2dCategory(FEconomyItems modelData);

	UFUNCTION()
	void LoadFaceAccessary(FEconomyItems modelData);

	UFUNCTION()
	void ResetToCurrentSelectedModel();

	void ResetToCurrentSelectedModel(TFunction<void()> Oncomplete);

	UFUNCTION()
	void ResetToCurrentMaterial();

	void ResetToDefault(TFunction<void()> complete);

	FOnReceiveTexture ReceiveTexture;

	FOnReceiveTexture ReceiveHairTexture;



	UPROPERTY()
	FLoadNetworkModelDelegate LoadNetworkModelDelegate;

	UPROPERTY()
	FOnReceiveData FOnReceiveClipData;


	UFUNCTION()
	void OnReceiveHairTexture(UTexture *texture);




	UFUNCTION()
	void DestroySpawnCustomizePoint();

	UFUNCTION()
	void ShowCustomizePoint(FString direction);
	// void LoadDefaultModels();

	UPROPERTY()
	TArray<FEconomyItems> netwrokModelList;

	UPROPERTY()
	AAPIEvents *APIEvents;

	UPROPERTY()
	AGltfFullActor *GltfFullActorHome;

	UFUNCTION()
	void AddNetworkBodyPart(AGltfActor *gltfActor, FEconomyItems modelData);

	UPROPERTY()
	AUserDetailHolder *UserDetailHolder;

	ADataHolder *DataHolder;

	ACurrentAvatarChanges *AvatarCurrentChangesInstance;

	AEconomyItemHolder *EconomyItemHolder;

	UFUNCTION()
	void LoadDefaultModels();
	void LoadFacialHair(FEconomyItems modelData,TFunction<void()> complete);
};
