// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../../Utilitys/APIEvents.h"
#include "Styling/SlateBrush.h"
#include "PaperSpriteComponent.h"
#include "Slate/SlateBrushAsset.h"
#include "Slate/SlateTextureAtlasInterface.h"
#include "CategoryButton.generated.h"
USTRUCT(BlueprintType)
struct  FCategoryButtonData
{
    GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
        FString Category;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
        FSlateBrush ButtonImage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
        FSlateBrush ButtonPressImage;
};

/**
 * 
 */
UCLASS()
class AVATARYUGDEMO_API UCategoryButton : public UUserWidget
{
  GENERATED_BODY()
  
	protected:
        void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
        class UButton *CatButton;

        UPROPERTY(meta = (BindWidget))
        class UImage *SelectedImage;

        UPROPERTY(meta = (BindWidget))
        class UImage *OutlineImage;

        UPROPERTY(meta = (BindWidget))
        class UImage *FillImage;
        
	UPROPERTY()
        FOnClickMainCategory OnClickMainCategory;

        UPROPERTY()
        FString category;
        UFUNCTION()
        void OnClickCategoryButton();

      public:
        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyCategory)
        TArray<FCategoryButtonData> CategoryButtonData;
        UFUNCTION()
        void SetButton(int index, FString _category,FOnClickMainCategory _onClickMainCat);
        UFUNCTION()
        void SetSelectVisible(FString _category);
        
};
