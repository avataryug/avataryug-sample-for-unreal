// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Http.h"
#include "../../Utilitys/LoadTextureFromURL.h"
#include "../../AvatarLoader/AvatarHandler.h"
#include "../..//DataHolders/EconomyItemHolder.h"
#include "../../DataHolders/DataHolder.h"
#include "../../DataHolders/UserInventoryHolder.h"
#include "../../Utilitys/APIEvents.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "../../DataHolders/AllGraphicsHolder.h"
#include "CustomizeData.h"
#include "Kismet/GameplayStatics.h"
#include "PropItemButton.generated.h"

/**
 *
 */
UCLASS()
class AVATARYUGDEMO_API UPropItemButton : public UUserWidget
{
  GENERATED_BODY()
protected:
  void NativeConstruct() override;

  UPROPERTY(meta = (BindWidget))
  class UCanvasPanel *LoadingPanel;

  UPROPERTY(meta = (BindWidget))
  class UButton *ItemButton;

  UPROPERTY(meta = (BindWidget))
  class UImage *ItemImage;

  UPROPERTY(meta = (BindWidget))
  class UImage *CurrencyImage;

  UPROPERTY(meta = (BindWidget))
  class UImage *SelectImage;

  // UPROPERTY(meta = (BindWidget))
  // class UImage *CustomImage;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyCategory")
  UTexture2D *CustomImage;

  UPROPERTY(meta = (BindWidget))
  class UImage *TickImage;

  UPROPERTY(meta = (BindWidget))
  class UTextBlock *CurrencyText;

  //FOnEconomyItemClick OnCallback;
  FEconomyItems EconomyItem;
  FExpression ExpressionItem;
  FClip ClipItem;
  FString Id;
  FString Category;
  FUserAvatar thisUserAvatar;
public:
  UFUNCTION()
  void SetButton(FEconomyItems item);

  UFUNCTION()
  void SetButtonExpression(FExpression item);

  UFUNCTION()
  void SetButtonClip(FClip item);

  UFUNCTION()
  void SetButtonAvatar(FUserAvatar userAvatar);

  UFUNCTION()
  void UpdateExpData();

  UFUNCTION()
  void UpdateClipData();

  UFUNCTION()
  void UpdateButtonData();

  UFUNCTION()
  void OnLoadImage(UTexture2D *textures);

  UPROPERTY()
  FOnReceiveTexture OnReceiveTexture;

  UPROPERTY()
  AAllGraphicsHolder *AllGraphicsHolder;

  UFUNCTION()
  void OnClickButton();

  // UPROPERTY()
  // AAvatarLoader *AvatarLoader;

  AEconomyItemHolder *EconomyItemHolder;

  UPROPERTY()
  AAvatarHandler *AvatarHandler;

  AAPIEvents *APIEvents;

  AUserInventoryHolder *UserInventoryHolder;

  ADataHolder *DataHolder;

  UFUNCTION()
  void UpdateUiAfterItemSelect();
};
