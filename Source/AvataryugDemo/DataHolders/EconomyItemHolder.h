// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EconomyAPI/EconomyModel.h"
#include "GameStructs.h"
#include "../DataHolders/CurrentAvatarChanges.h"
#include "AvatarPresetsAPI/AvatarPresetsModel.h"
#include "EconomyItemHolder.generated.h"

UCLASS()
class AVATARYUGDEMO_API AEconomyItemHolder : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEconomyItemHolder();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
	TArray<FEconomyItems> EconomyItems;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
	TArray<FEconomyItems> m_CurrentSelectedItems;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
	TArray<FCurrentEconomyItemTexture> currentEconomyData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
	ACurrentAvatarChanges *CurrentAvatarChangesHolder;
	UFUNCTION()
	void LogOut();
	UFUNCTION()
	bool IsCategoryEconomyItemAdded(FString category);
	UFUNCTION()
	bool IsEconomyItemPresent(FString id);
	UFUNCTION()
	FEconomyItems GetEconomyItemWithId(FString id);
	UFUNCTION()
	FEconomyItems GetEconomyCurrentItemWithId(FString id);
	UFUNCTION()
	FCurrentEconomyItemTexture GetCurrentEconomyTex(FString id);
	UFUNCTION()
	TArray<FEconomyItems> GetEconomysItemWithCat(FString category);
	UFUNCTION()
    void AddEconomyItemData(FGetEconomyItemsResult result);
    UFUNCTION()
    void AddEconomyItemDataFromAvatar( FGetUserAvatarAllDataResponse result) ;

	UFUNCTION()
	bool IsCurrentSelectedEconomyItemPresent(FString id);

	UFUNCTION()
	void OnQueueRemoveItem();

	UPROPERTY()
	int itemListLimit = 2000;

	TArray<FString> BlendshapeCategory = {"FaceShape", "EyeShape", "EyebrowShape", "NoseShape", "LipShape", "EarShape"};
	UFUNCTION()
	bool IsBlendshapeCategory(const FString &category)
	{
		return BlendshapeCategory.Contains(category);
	}
	FEconomyItems GetEconomyItem(FGetEconomyItemsResultDataInner data);
};
