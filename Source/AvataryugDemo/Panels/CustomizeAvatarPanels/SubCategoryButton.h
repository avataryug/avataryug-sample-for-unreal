// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "CustomizeData.h"
#include "Components/SizeBox.h"
#include "Components/Button.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "SubCategoryButton.generated.h"

/**
 * 
 */
UCLASS()
class AVATARYUGDEMO_API USubCategoryButton : public UUserWidget ,public IUserObjectListEntry
{
		GENERATED_BODY()
protected:
    void NativeConstruct() override;
	 virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock *CategoryText;

	UPROPERTY(meta = (BindWidget))
	class UButton *CategoryButton;

	UPROPERTY(meta = (BindWidget))
	class USizeBox *ButtonSizeBox;
	UFUNCTION()
	void OnCategoryButtonClick();

	FOnClickSubCategory OnClickSubCategory;
	FString Cat;
};
