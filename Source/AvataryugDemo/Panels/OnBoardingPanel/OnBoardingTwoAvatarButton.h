// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ImageUtils.h"
#include "../../Utilitys/LoadTextureFromURL.h"
#include "AvatarPresetsAPI/AvatarPresetsModel.h"
#include "Components/Image.h"
#include "JsonUtilities.h"
#include "JsonObjectConverter.h"
#include "Json.h"
#include "Http.h"
#include "OnBoardingTwoAvatarButton.generated.h"

/**
 *
 */
UCLASS()
class AVATARYUGDEMO_API UOnBoardingTwoAvatarButton : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta = (BindWidget))
	class UButton *AvatarButton;

	UPROPERTY(meta = (BindWidget))
	class UImage *AvatarImage;
	void NativeConstruct() override;

public:
	UFUNCTION()
	void SetButtonData(FGetAvatarPresetsResultDataInner item);
	UFUNCTION()
	void OnLoadImage(UTexture2D *textures);

	UPROPERTY()
	FOnReceiveTexture OnReceiveTexture;
};
