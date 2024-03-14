// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../../../AvatarLoader/AvatarHandler.h"
#include "Components/Button.h"
#include "AvataryugFunctionLibrary.h"
#include "GameStructs.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"
#include "ColorPickerButton.generated.h"

/**
 *
 */
UCLASS()
class AVATARYUGDEMO_API UColorPickerButton : public UUserWidget
{
	GENERATED_BODY()

protected:
	void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UButton *ColorButton;

	UPROPERTY(meta = (BindWidget))
	class UImage *ColorImage;

	UFUNCTION()
	void OnClickColorButton();

	UPROPERTY()
	FString Category;

	UPROPERTY()
	FString m_Color;

	UPROPERTY()
	FLinearColor OutColor;

public:
	UFUNCTION()
	void SetButton(FString cat, FString color);

	UPROPERTY()
	AAvatarHandler *AvatarHandler;
};
