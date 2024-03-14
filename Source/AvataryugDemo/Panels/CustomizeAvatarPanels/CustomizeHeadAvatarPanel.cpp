// Fill out your copyright notice in the Description page of Project Settings.

#include "CustomizeHeadAvatarPanel.h"
#include "Components/Button.h"
#include "CommonModels.h"
#include "PropItemGridPanel.h"
#include "CustomizeData.h"
#include "EconomyAPI/EconomyHandler.h"
#include "EconomyAPI/EconomyRequest.h"
#include "EconomyAPI/EconomyModel.h"
#include "Components/ListView.h"
#include "Kismet/GameplayStatics.h"
#include "CategoryButton.h"
#include "EngineUtils.h"
#include "Components/ExponentialHeightFogComponent.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/SizeBoxSlot.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/OverlaySlot.h"
#include "PropItemButton.h"

void UCustomizeHeadAvatarPanel::NativeConstruct()
{
  Super::NativeConstruct();

  GetReference();

  SubscribeEvents();

  SetButtonEvents();

  ColorPickerWidgetPanel->SetVisibility(ESlateVisibility::Hidden);
  ColorButonPanel->SetVisibility(ESlateVisibility::Hidden);

  UndoButton->SetVisibility(ESlateVisibility::Hidden);

  OnItemSelected();
}

void UCustomizeHeadAvatarPanel::GetReference()
{
  if (UserDetailHolder == nullptr)
  {
    AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AUserDetailHolder::StaticClass());
    UserDetailHolder = Cast<AUserDetailHolder>(FoundActor);
    if (UserDetailHolder == nullptr)
    {
      UserDetailHolder = GetWorld()->SpawnActor<AUserDetailHolder>();
    }
  }
  if (EconomyItemHolder == nullptr)
  {
    AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AEconomyItemHolder::StaticClass());
    EconomyItemHolder = Cast<AEconomyItemHolder>(FoundActor);
    if (EconomyItemHolder == nullptr)
    {
      EconomyItemHolder = GetWorld()->SpawnActor<AEconomyItemHolder>();
    }
  }
  if (AvatarHandler == nullptr)
  {
    AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AAvatarHandler::StaticClass());
    AvatarHandler = Cast<AAvatarHandler>(FoundActor);
  }
  if (DataHolder == nullptr)
  {
    AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), ADataHolder::StaticClass());
    DataHolder = Cast<ADataHolder>(FoundActor);
    if (DataHolder == nullptr)
    {
      DataHolder = GetWorld()->SpawnActor<ADataHolder>();
    }
  }
  if (APIEvents == nullptr)
  {
    AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AAPIEvents::StaticClass());
    APIEvents = Cast<AAPIEvents>(FoundActor);
    if (APIEvents == nullptr)
    {
      APIEvents = GetWorld()->SpawnActor<AAPIEvents>();
    }
    if (APIEvents)
    {
      APIEvents->OnScreenOrientation.AddDynamic(this, &UCustomizeHeadAvatarPanel::FaceScreenOrientation);
    }
  }
  if (AllGraphicsHolder == nullptr)
  {
    AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AAllGraphicsHolder::StaticClass());
    AllGraphicsHolder = Cast<AAllGraphicsHolder>(FoundActor);
  }
  if (UserInventoryHolder == nullptr)
  {
    AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AUserInventoryHolder::StaticClass());
    UserInventoryHolder = Cast<AUserInventoryHolder>(FoundActor);
    if (UserInventoryHolder == nullptr)
    {
      UserInventoryHolder = GetWorld()->SpawnActor<AUserInventoryHolder>();
    }
  }
  if (UndoHandler == nullptr)
  {
    AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AUndoHandler::StaticClass());
    UndoHandler = Cast<AUndoHandler>(FoundActor);
    if (UndoHandler == nullptr)
    {
      UndoHandler = GetWorld()->SpawnActor<AUndoHandler>();
    }
  }

  if (CommonFunctionHolder == nullptr)
  {
    AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), ACommonFunction::StaticClass());
    CommonFunctionHolder = Cast<ACommonFunction>(FoundActor);
    if (CommonFunctionHolder == nullptr)
    {
      CommonFunctionHolder = GetWorld()->SpawnActor<ACommonFunction>();
    }
  }

  if (CurrentAvatarChanges == nullptr)
  {
    AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), ACurrentAvatarChanges::StaticClass());
    CurrentAvatarChanges = Cast<ACurrentAvatarChanges>(FoundActor);
  }


}

void UCustomizeHeadAvatarPanel::SubscribeEvents()
{
  APIEvents->OnUpdateUiAfterItemSelect.RemoveDynamic(this, &UCustomizeHeadAvatarPanel::OnItemSelected);
  APIEvents->OnUpdateUiAfterItemSelect.AddDynamic(this, &UCustomizeHeadAvatarPanel::OnItemSelected);

  APIEvents->OnUpdateUiAfterPurchase.RemoveDynamic(this, &UCustomizeHeadAvatarPanel::UpdateUIAfterPurchase);
  APIEvents->OnUpdateUiAfterPurchase.AddDynamic(this, &UCustomizeHeadAvatarPanel::UpdateUIAfterPurchase);


  APIEvents->OnUpdateHeadCatBuyButtonUI.RemoveDynamic(this, &UCustomizeHeadAvatarPanel::UpdateHeadBuyUI);
  APIEvents->OnUpdateHeadCatBuyButtonUI.AddDynamic(this, &UCustomizeHeadAvatarPanel::UpdateHeadBuyUI);

  OnClickMainCategory.RemoveDynamic(this, &UCustomizeHeadAvatarPanel::OnClickMainCategoryButton);
  OnClickMainCategory.AddDynamic(this, &UCustomizeHeadAvatarPanel::OnClickMainCategoryButton);

  OnGetEconomyItemsResult.BindUFunction(this, "OnReceiveEconomyItems");
  OnGetEconomyItemsError.BindUFunction(this, "OnReceiveEconomyItemsError");
  OnClickSubCategory.BindUFunction(this, "OnClickSubCategoryButton");

}
void UCustomizeHeadAvatarPanel::UpdateUIAfterPurchase()
{
  UpdateBuySaveButtonAfterChanges();
}
void UCustomizeHeadAvatarPanel::SetButtonEvents()
{
  BackButton->OnClicked.RemoveDynamic(this, &UCustomizeHeadAvatarPanel::OnClickBackButton);
  BackButton->OnClicked.AddDynamic(this, &UCustomizeHeadAvatarPanel::OnClickBackButton);

  HeadCustomizeButton->OnClicked.RemoveDynamic(this, &UCustomizeHeadAvatarPanel::OnClickHeadCustomizeButton);
  HeadCustomizeButton->OnClicked.AddDynamic(this, &UCustomizeHeadAvatarPanel::OnClickHeadCustomizeButton);

  FullBodyModification_Button->OnClicked.RemoveDynamic(this, &UCustomizeHeadAvatarPanel::OnClickFullBodyCustomizeButton);
  FullBodyModification_Button->OnClicked.AddDynamic(this, &UCustomizeHeadAvatarPanel::OnClickFullBodyCustomizeButton);

  ExpressionClipButton->OnClicked.RemoveDynamic(this, &UCustomizeHeadAvatarPanel::OnClickExpressionClipButton);
  ExpressionClipButton->OnClicked.AddDynamic(this, &UCustomizeHeadAvatarPanel::OnClickExpressionClipButton);

  InfoButton->OnClicked.RemoveDynamic(this, &UCustomizeHeadAvatarPanel::OnClickInfoButton);
  InfoButton->OnClicked.AddDynamic(this, &UCustomizeHeadAvatarPanel::OnClickInfoButton);

  UndoButton->OnClicked.RemoveDynamic(this, &UCustomizeHeadAvatarPanel::OnClickUndoButton);
  UndoButton->OnClicked.AddDynamic(this, &UCustomizeHeadAvatarPanel::OnClickUndoButton);

  ResetButton->OnClicked.RemoveDynamic(this, &UCustomizeHeadAvatarPanel::OnClickResetButton);
  ResetButton->OnClicked.AddDynamic(this, &UCustomizeHeadAvatarPanel::OnClickResetButton);

  SortButton->OnClicked.RemoveDynamic(this, &UCustomizeHeadAvatarPanel::OnClickSortButton);
  SortButton->OnClicked.AddDynamic(this, &UCustomizeHeadAvatarPanel::OnClickSortButton);

  hightolowButton->OnClicked.RemoveDynamic(this, &UCustomizeHeadAvatarPanel::SortHighToLow);
  hightolowButton->OnClicked.AddDynamic(this, &UCustomizeHeadAvatarPanel::SortHighToLow);

  lowtohighButton->OnClicked.RemoveDynamic(this, &UCustomizeHeadAvatarPanel::SortLowToHigh);
  lowtohighButton->OnClicked.AddDynamic(this, &UCustomizeHeadAvatarPanel::SortLowToHigh);

  CancelSortButton->OnClicked.RemoveDynamic(this, &UCustomizeHeadAvatarPanel::SortCancelButton);
  CancelSortButton->OnClicked.AddDynamic(this, &UCustomizeHeadAvatarPanel::SortCancelButton);

  FixedColorButton->OnClicked.RemoveDynamic(this, &UCustomizeHeadAvatarPanel::OnClickFixedColorButton);
  FixedColorButton->OnClicked.AddDynamic(this, &UCustomizeHeadAvatarPanel::OnClickFixedColorButton);

  CustomColorButton->OnClicked.RemoveDynamic(this, &UCustomizeHeadAvatarPanel::OnClickCustomColorButton);
  CustomColorButton->OnClicked.AddDynamic(this, &UCustomizeHeadAvatarPanel::OnClickCustomColorButton);

  HeadDarkModeButton->OnCheckStateChanged.RemoveDynamic(this, &UCustomizeHeadAvatarPanel::OnHeadDarkModeToggleStateChanged);
  HeadDarkModeButton->OnCheckStateChanged.AddDynamic(this, &UCustomizeHeadAvatarPanel::OnHeadDarkModeToggleStateChanged);

  OKButton->OnClicked.RemoveDynamic(this, &UCustomizeHeadAvatarPanel::OnClickOkButton);
  OKButton->OnClicked.AddDynamic(this, &UCustomizeHeadAvatarPanel::OnClickOkButton);
  SubCatListView->SetScrollbarVisibility(ESlateVisibility::Hidden);
    OKButton->SetVisibility(ESlateVisibility::Hidden);
  // OnClickMainCategoryButton("SkinTone");
  UndoButton->SetVisibility(ESlateVisibility::Hidden);
  // UpdateHeadBuyUI(false);
}

void UCustomizeHeadAvatarPanel::OnClickFixedColorButton()
{
  ColorPickerWidgetPanel->SetVisibility(ESlateVisibility::Visible);
  ColorPickerWidgetPanel->OnClickFixedColorButton(CurrentSelectedMainCategory);
  OKButton->SetVisibility(ESlateVisibility::Visible);
}

void UCustomizeHeadAvatarPanel::OnClickCustomColorButton()
{
  ColorPickerWidgetPanel->SetVisibility(ESlateVisibility::Visible);
  ColorPickerWidgetPanel->OnClickCustomColorButton(CurrentSelectedMainCategory);
  OKButton->SetVisibility(ESlateVisibility::Visible);
}

void UCustomizeHeadAvatarPanel::OnClickOkButton()
{
  ColorPickerWidgetPanel->SetVisibility(ESlateVisibility::Hidden);
  ColorPickerWidgetPanel->OnClickOkButton();
  OKButton->SetVisibility(ESlateVisibility::Hidden);
}

void UCustomizeHeadAvatarPanel::OnClickBackButton()
{
  if (APIEvents->isCustomize)
  {
    AvatarHandler->LogOut();
    CurrentAvatarChanges->Logout();
    EconomyItemHolder->LogOut();
    UserInventoryHolder->LogOut();
    if (AvatarHandler->ForCustomizeAvatar->spawnedHeadActor != nullptr)
    {
      //  AvatarHandler->ForCustomizeAvatar->spawnedHeadActor->SkeletalHeadComponent->SetVisibility(false);
      AvatarHandler->ForCustomizeAvatar->SetActorLocation(FVector(0, 0, 1000));
    }
    if (AvatarHandler->CustomizeDefaultAvatarLoader->spawnedHeadActor != nullptr)
    {
      //  AvatarHandler->ForCustomizeAvatar->spawnedHeadActor->SkeletalHeadComponent->SetVisibility(false);
      AvatarHandler->CustomizeDefaultAvatarLoader->SetActorLocation(FVector(0, 0, 1000));
    }
    if (AvatarHandler->ForCustomizeAvatar->LoadedModelList.Num() > 0)
    {
      UE_LOG(LogTemp, Display, TEXT("--ForCustomizeAvatar--->>GltfModelList->---->> "));
      for (int k = 0; k < AvatarHandler->ForCustomizeAvatar->LoadedModelList.Num(); k++)
      {
        UE_LOG(LogTemp, Display, TEXT("--ForCustomizeAvatar--->>LoadedModelList->---->> "));

        AvatarHandler->ForCustomizeAvatar->LoadedModelList[k]->Destroy();
        //  AvatarHandler->CustomizeDefaultAvatarLoader->bodyPoints.RemoveAt(k);
      }
    }
    if (AvatarHandler->ForCustomizeAvatar->bodyPoints.Num() > 0)
    {
      UE_LOG(LogTemp, Display, TEXT("ForCustomizeAvatar->bodyPoints---->> "));
      for (int k = 0; k < AvatarHandler->ForCustomizeAvatar->bodyPoints.Num(); k++)
      {
        UE_LOG(LogTemp, Display, TEXT("ForCustomizeAvatar->---->> "));
        AvatarHandler->ForCustomizeAvatar->bodyPoints[k]->Destroy();
        //  AvatarHandler->CustomizeDefaultAvatarLoader->bodyPoints.RemoveAt(k);
      }
    }

    if (AvatarHandler->CustomizeDefaultAvatarLoader->LoadedModelList.Num() > 0)
    {
      for (int k = 0; k < AvatarHandler->CustomizeDefaultAvatarLoader->LoadedModelList.Num(); k++)
      {
        UE_LOG(LogTemp, Display, TEXT("LoadedModelList->---->> "));

        AvatarHandler->CustomizeDefaultAvatarLoader->LoadedModelList[k]->Destroy();
        //  AvatarHandler->CustomizeDefaultAvatarLoader->bodyPoints.RemoveAt(k);
      }
    }
    if (AvatarHandler->CustomizeDefaultAvatarLoader->bodyPoints.Num() > 0)
    {
      UE_LOG(LogTemp, Display, TEXT("CustomizeDefaultAvatarLoader->bodyPoints---->> "));
      for (int k = 0; k < AvatarHandler->CustomizeDefaultAvatarLoader->bodyPoints.Num(); k++)
      {
        UE_LOG(LogTemp, Display, TEXT("CustomizeDefaultAvatarLoader->---->> "));

        AvatarHandler->CustomizeDefaultAvatarLoader->bodyPoints[k]->Destroy();
        //  AvatarHandler->CustomizeDefaultAvatarLoader->bodyPoints.RemoveAt(k);
      }
    }
    AvatarHandler->ForCustomizeAvatar->LoadedModelList.Empty();
    AvatarHandler->ForCustomizeAvatar->bodyPoints.Empty();
    AvatarHandler->ForCustomizeAvatar->GltfModelList.Empty();
    AvatarHandler->CustomizeDefaultAvatarLoader->GltfModelList.Empty();
    AvatarHandler->CustomizeDefaultAvatarLoader->bodyPoints.Empty();
    AvatarHandler->CustomizeDefaultAvatarLoader->LoadedModelList.Empty();
    AvatarHandler->CustomizeDefaultAvatarLoader->count = 0;
    switch (AvatarHandler->typeOfOnBoarding)
    {
    case EOnBoarding::OnBoarding1:
      this->SetVisibility(ESlateVisibility::Hidden);
      APIEvents->ShowPanel(EUIPanels::ONBOARDING, true);
      APIEvents->OnChangeCamera.Broadcast(CameraPanels::OnBoarding);
      break;
    case EOnBoarding::OnBoarding2:
      this->SetVisibility(ESlateVisibility::Hidden);
      APIEvents->ShowPanel(EUIPanels::ONBOARDING2, true);
      APIEvents->OnChangeCamera.Broadcast(CameraPanels::OnBoarding);
      break;
    case EOnBoarding::OnBoarding3:
      this->SetVisibility(ESlateVisibility::Hidden);
      APIEvents->ShowPanel(EUIPanels::ONBOARDING2, true);
      APIEvents->OnChangeCamera.Broadcast(CameraPanels::OnBoarding);
      break;
    }
  }
  else
  {
    this->SetVisibility(ESlateVisibility::Hidden);
    APIEvents->ShowPanel(EUIPanels::CUSTOMIZEFULL, true);
    APIEvents->OnChangeCamera.Broadcast(CameraPanels::CustomizeAvatar_FullBody);
  }
}

void UCustomizeHeadAvatarPanel::LoadCustomizeAvatarHeadPanelData()
{
    if (APIEvents->isDarkMode)
    {
      HeadDarkModeButton->SetCheckedState(ECheckBoxState::Checked);
      OnHeadDarkModeToggleStateChanged(APIEvents->isDarkMode);
    }
    else
    {
      HeadDarkModeButton->SetCheckedState(ECheckBoxState::Unchecked);
      OnHeadDarkModeToggleStateChanged(APIEvents->isDarkMode);
    }
 
  if(AvatarHandler->TypeOfMontization == EMonitizeType::NonMonitize)
  {
     UE_LOG(LogTemp, Display, TEXT("TypeOfMontization->--NonMonitize-->> "));
      FaceCoinTop_Panel->SetVisibility(ESlateVisibility::Hidden);
        SortButtonBox->SetVisibility(ESlateVisibility::Collapsed);
  }
  else
  {
     UE_LOG(LogTemp, Display, TEXT("TypeOfMontization->--Monitize-->> "));
    FaceCoinTop_Panel->SetVisibility(ESlateVisibility::Visible);
      SortButtonBox->SetVisibility(ESlateVisibility::Visible);
  }
  AvatarHandler->SetActorRotation(FRotator(0, 0, 0));
  APIEvents->OnSetModelParentDelegate.Broadcast(EModelParent::CUSTOMIZE);
  if (MainCategoryButton.Num() <= 0)
  {

    MainCategoryButton.Add(InventoryButton);
    MainCategoryButton.Add(SkinToneButton);
    MainCategoryButton.Add(HairButton);
    MainCategoryButton.Add(EyebrowButton);
    MainCategoryButton.Add(EyeballButton);
    MainCategoryButton.Add(LipsButton);
    MainCategoryButton.Add(FacialhairButton);
    MainCategoryButton.Add(FaceShapeButton);
    MainCategoryButton.Add(NoseShapeButton);
    MainCategoryButton.Add(EyebrowsShapeButton);
    MainCategoryButton.Add(EyeShapeButton);
    MainCategoryButton.Add(LipShapeButton);
    MainCategoryButton.Add(EarShapeButton);
    MainCategoryButton.Add(HeadwearButton);
    MainCategoryButton.Add(EyewearButton);
    MainCategoryButton.Add(AccessoriesButton);
  }
  UE_LOG(LogTemp, Display, TEXT("MainCategory Button Category COUNT---->>  %d"), MainCategoryButton.Num());
  for (int i = 0; i < MainCategoryButton.Num(); i++)
  {
    UE_LOG(LogTemp, Display, TEXT("Set Button Category   %s"), *MainCategorys[i]);
    if (APIEvents->isCustomize)
    {

      UOverlaySlot *SwiftLeftImageBoxSlot = Cast<UOverlaySlot>(SwiftRounded_Left->Slot);
      SwiftLeftImageBoxSlot->SetPadding(FMargin(0.0f, 0.0f, 178.0f, 0.0f));

      UOverlaySlot *SwiftCenterImageBoxSlot = Cast<UOverlaySlot>(SwiftRounded_Center->Slot);
      SwiftCenterImageBoxSlot->SetPadding(FMargin(990.0f, 0.0f, 542.5f, 0.0f));

      // Assuming UOverlaySlot is part of the UMG framework
      UOverlaySlot *SwiftRightImageBoxSlot = Cast<UOverlaySlot>(SwiftRounded_Right->Slot);
      SwiftRightImageBoxSlot->SetPadding(FMargin(625.0f, 0.0f, 0.0f, 0.0f));

      if (i == 0)
      {
        MainCategoryButton[i]->SetVisibility(ESlateVisibility::Collapsed);
        UE_LOG(LogTemp, Display, TEXT("INDEX 0 Button Category   %s"), *MainCategorys[i]);
      }
      else
      {
        MainCategoryButton[i]->SetButton(i, MainCategorys[i], OnClickMainCategory);
      }
    }
    else
    {
      UOverlaySlot *SwiftLeftImageBoxSlot = Cast<UOverlaySlot>(SwiftRounded_Left->Slot);
      SwiftLeftImageBoxSlot->SetPadding(FMargin(-100.0f, 0.0f, 0.0f, 0.0f));

      UOverlaySlot *SwiftCenterImageBoxSlot = Cast<UOverlaySlot>(SwiftRounded_Center->Slot);
      SwiftCenterImageBoxSlot->SetPadding(FMargin(1142.5f, 0.0f, 542.5f, 0.0f));

      // Assuming UOverlaySlot is part of the UMG framework
      UOverlaySlot *SwiftRightImageBoxSlot = Cast<UOverlaySlot>(SwiftRounded_Right->Slot);
      SwiftRightImageBoxSlot->SetPadding(FMargin(700.0f, 0.0f, 0.0f, 0.0f));
      MainCategoryButton[i]->SetButton(i, MainCategorys[i], OnClickMainCategory);
    }
  }
    if(AvatarHandler->TypeOfMontization == EMonitizeType::NonMonitize)
  {

  }
  else
  {
  CoinHeaderPanel->SetCoins();
  }
  ResetHeadAvatarPanel->SetVisibility(ESlateVisibility::Hidden);
  OnClickMainCategoryButton("SkinTone");
  //  BuySaveButton->SetVisibility(ESlateVisibility::Hidden);

  OnItemSelected();
}

void UCustomizeHeadAvatarPanel::OnClickMainCategoryButton(FString category)
{
  // if (CurrentSelectedMainCategory != category)
  // {
  CurrentSelectedMainCategory = category;
  if (category == "Inventory")
  {
    ColorPickerWidgetPanel->SetVisibility(ESlateVisibility::Collapsed);
    ColorButonPanel->SetVisibility(ESlateVisibility::Collapsed);
    CurrentSelectedSubCategory = "All";
    OnClickSubCategoryButton(CurrentSelectedSubCategory);

    SubHeadCategorySizeBox->bOverride_MinDesiredHeight = true;
    SubHeadCategorySizeBox->SetMinDesiredHeight(100.0f);
    SubHeadCategorySizeBox->SetVisibility(ESlateVisibility::Visible);
    AllGraphicsHolder->GraphicsWithIDList.Empty();
    if (SubCatListView)
    {
      SubCatListView->ClearListItems();
    }
    TArray<FString> InventoryCategory = { "All","SkinTone","Hair","Eyebrow","Eyeball","Lips","Facialhair", "Headwear","Eyewear","Mouthwear", "Earwear","Eyebrowswear","Facewear","Neckwear","Nosewear", };
    for (int i = 0; i < InventoryCategory.Num(); i++)
    {
      UCustomizeSubCatListData *item = NewObject<UCustomizeSubCatListData>();
      item->Index = i;
      item->Category = InventoryCategory[i];
      item->ClickSubCategory = OnClickSubCategory;
      SubCatListView->AddItem(item);
      SubCatListView->SetScrollbarVisibility(ESlateVisibility::Collapsed);
    }
  }
  else
  {
    ColorPickerWidgetPanel->SetVisibility(ESlateVisibility::Collapsed);
    ColorButonPanel->SetVisibility(ESlateVisibility::Collapsed);

    if (CurrentSelectedMainCategory == "Hair" || CurrentSelectedMainCategory == "Eyebrow" || CurrentSelectedMainCategory == "Facialhair" || CurrentSelectedMainCategory == "Lips")
    {
      ColorButonPanel->SetVisibility(ESlateVisibility::Visible);
    }
    if (category == "Accessories")
    {
      SubHeadCategorySizeBox->SetVisibility(ESlateVisibility::Visible);
      SubHeadCategorySizeBox->bOverride_MinDesiredHeight = true;
      SubHeadCategorySizeBox->SetMinDesiredHeight(100.0f);
      AllGraphicsHolder->GraphicsWithIDList.Empty();
      if (SubCatListView)
      {
        SubCatListView->ClearListItems();
      }
      TArray<FString> Accessarys = {"Mouthwear", "Earwear", "Eyebrowswear", "Facewear", "Neckwear", "Nosewear"};
      for (int i = 0; i < Accessarys.Num(); i++)
      {
        UCustomizeSubCatListData *item = NewObject<UCustomizeSubCatListData>();
        item->Index = i;
        item->Category = Accessarys[i];
        item->ClickSubCategory = OnClickSubCategory;
        SubCatListView->AddItem(item);
      }
    }
    else
    {
      UE_LOG(LogTemp, Display, TEXT("Other CAts---->>>"));
      SubHeadCategorySizeBox->SetVisibility(ESlateVisibility::Collapsed);
      if (PropItemListView)
    {
      PropItemListView->ClearListItems();
    }
      APIEvents->ShowLoading();
      if (MainCategoryButton.Num() > 0)
      {
        for (int i = 0; i < MainCategoryButton.Num(); i++)
        {
          MainCategoryButton[i]->SetSelectVisible(category);
        }
      }
      if (!EconomyItemHolder->IsCategoryEconomyItemAdded(category))
      {
        UE_LOG(LogTemp, Display, TEXT("Other IsCategoryEconomyItemAdded---->>"));
        int gender = 3;
        UEconomyHandler::GetEconomyItems(category, 1, gender, 0, 500, OnGetEconomyItemsResult, OnGetEconomyItemsError);
        // ShowPropItems(CurrentSelectedMainCategory);
      }
      else
      {
        UE_LOG(LogTemp, Display, TEXT("Other ShowPropItems---->>"));
        ShowPropItems(CurrentSelectedMainCategory);
      }
    }
    UE_LOG(LogTemp, Display, TEXT("OnClickMainCategoryButton   %s"), *category);
    AvatarHandler->ForCustomizeAvatar->Blendshapecat = category;
  }
  //}
}

void UCustomizeHeadAvatarPanel::OnReceiveEconomyItems(FGetEconomyItemsResult result)
{
  EconomyItemHolder->AddEconomyItemData(result);
  if (CurrentSelectedMainCategory == "Accessories")
  {
    ShowPropItems(CurrentSelectedSubCategory);
  }
  else
  {
    ShowPropItems(CurrentSelectedMainCategory);
  }
}
void UCustomizeHeadAvatarPanel::ShowPropItems(FString categtory)
{
  currentSelectedItems = EconomyItemHolder->GetEconomysItemWithCat(categtory);
  if (EconomyItemHolder->IsBlendshapeCategory(categtory))
  {
    UE_LOG(LogTemp, Display, TEXT("IsBlendshapeCategory------>>%s"), *categtory);
    AllGraphicsHolder->GraphicsWithIDList.Empty();
    if (PropItemListView)
    {
      PropItemListView->ClearListItems();
    }
    currentSelectedItems = EconomyItemHolder->GetEconomysItemWithCat(categtory);
    FEconomyItems newItem;
    newItem.itemCategory = categtory;
    newItem.displayName = "Custom";
    currentSelectedItems.Insert(newItem, 0);

    float floatValue = currentSelectedItems.Num();
    float contaientGridCount = floatValue / 4;
    int myCeilInt = FMath::CeilToInt(contaientGridCount);
    for (int i = 0; i < myCeilInt; i++)
    {
      UCustomizeListData *item = NewObject<UCustomizeListData>();
      item->StartIndex = 4 * i;
      item->TotalCount = currentSelectedItems.Num();
      item->currentSelectedItems = currentSelectedItems;
      PropItemListView->AddItem(item);
    }
  }
  else
  {
    AllGraphicsHolder->GraphicsWithIDList.Empty();
    if (PropItemListView)
    {
      PropItemListView->ClearListItems();
    }

    float floatValue = currentSelectedItems.Num();
    float contaientGridCount = floatValue / 4;
    int myCeilInt = FMath::CeilToInt(contaientGridCount);
    for (int i = 0; i < myCeilInt; i++)
    {
      UCustomizeListData *item = NewObject<UCustomizeListData>();
      item->StartIndex = 4 * i;
      item->TotalCount = currentSelectedItems.Num();
      item->currentSelectedItems = currentSelectedItems;
      PropItemListView->AddItem(item);
      PropItemListView->SetScrollbarVisibility(ESlateVisibility::Hidden);
    }
  }
  APIEvents->HideLoading();
}
void UCustomizeHeadAvatarPanel::UpdateHeadBuyUI(bool isUpdate)
{
  if (isUpdate)
  {
  }
}
void UCustomizeHeadAvatarPanel::OnReceiveEconomyItemsError(FApiException result)
{
}

void UCustomizeHeadAvatarPanel::OnClickHeadCustomizeButton()
{
}

void UCustomizeHeadAvatarPanel::OnClickExpressionClipButton()
{
  this->SetVisibility(ESlateVisibility::Hidden);
  APIEvents->ShowPanel(EUIPanels::EXPRESSIONCLIP, true);
}

void UCustomizeHeadAvatarPanel::OnClickFullBodyCustomizeButton()
{
  UE_LOG(LogTemp, Display, TEXT("OnClickFullBodyCustomizeButton----->>>>"));
  this->SetVisibility(ESlateVisibility::Hidden);
  // APIEvents->OnUpdateBuyButtonUI.RemoveDynamic(this, &UCustomizeFullAvatarPanel::UpdateBuyUI);
  APIEvents->ShowPanel(EUIPanels::CUSTOMIZEFULL, true);
  APIEvents->OnChangeCamera.Broadcast(CameraPanels::CustomizeAvatar_FullBody);
}

void UCustomizeHeadAvatarPanel::OnClickInfoButton()
{
  APIEvents->ShowPanel(EUIPanels::DETAILS, true);
}

void UCustomizeHeadAvatarPanel::OnClickUndoButton()
{
  UndoHandler->OnClickUndo();
}

void UCustomizeHeadAvatarPanel::OnClickResetButton()
{
  ResetHeadAvatarPanel->SetVisibility(ESlateVisibility::Visible);
}

void UCustomizeHeadAvatarPanel::OnClickBuySaveButton()
{
  APIEvents->ShowPanel(EUIPanels::BUYITEMS, true);
}

void UCustomizeHeadAvatarPanel::OnClickSortButton()
{
  SortPanel->SetVisibility(ESlateVisibility::Visible);
}
void UCustomizeHeadAvatarPanel::SortHighToLow()
{

  currentSelectedItems.Sort([](const FEconomyItems &A, const FEconomyItems &B)
                            {
    const float PriceA = FCString::Atof(*A.virtualCurrency.virtualCurrencys[0].Amount);
    const float PriceB = FCString::Atof(*B.virtualCurrency.virtualCurrencys[0].Amount);
    return PriceA > PriceB; });

  if (PropItemListView)
  {
    PropItemListView->ClearListItems();
  }
  float floatValue = currentSelectedItems.Num();
  float contaientGridCount = floatValue / 4;
  int myCeilInt = FMath::CeilToInt(contaientGridCount);
  for (int i = 0; i < myCeilInt; i++)
  {
    UCustomizeListData *item = NewObject<UCustomizeListData>();
    item->StartIndex = 4 * i;
    item->TotalCount = currentSelectedItems.Num();
    item->currentSelectedItems = currentSelectedItems;
    PropItemListView->AddItem(item);
  }
  APIEvents->HideLoading();
  // CustomizeFullBodyPanel->SetVisibility(ESlateVisibility::Visible);
  SortPanel->SetVisibility(ESlateVisibility::Hidden);
}
void UCustomizeHeadAvatarPanel::SortLowToHigh()
{
  currentSelectedItems.Sort([](const FEconomyItems &A, const FEconomyItems &B)
                            {
    const float PriceA = FCString::Atof(*A.virtualCurrency.virtualCurrencys[0].Amount);
    const float PriceB = FCString::Atof(*B.virtualCurrency.virtualCurrencys[0].Amount);
    return PriceA < PriceB; });

  if (PropItemListView)
  {
    PropItemListView->ClearListItems();
  }
  float floatValue = currentSelectedItems.Num();
  float contaientGridCount = floatValue / 4;
  int myCeilInt = FMath::CeilToInt(contaientGridCount);
  for (int i = 0; i < myCeilInt; i++)
  {
    UCustomizeListData *item = NewObject<UCustomizeListData>();
    item->StartIndex = 4 * i;
    item->TotalCount = currentSelectedItems.Num();
    item->currentSelectedItems = currentSelectedItems;
    PropItemListView->AddItem(item);
  }
  APIEvents->HideLoading();
  // CustomizeFullBodyPanel->SetVisibility(ESlateVisibility::Visible);
  SortPanel->SetVisibility(ESlateVisibility::Hidden);
}
void UCustomizeHeadAvatarPanel::SortCancelButton()
{
  SortPanel->SetVisibility(ESlateVisibility::Hidden);
}
void UCustomizeHeadAvatarPanel::OnClickSubCategoryButton(FString category)
{

  UE_LOG(LogTemp, Display, TEXT("OnClickSubCategoryButton   %s"), *category);
  // if (CurrentSelectedSubCategory != category)
  // {
  if (CurrentSelectedMainCategory == "Accessories")
  {
    AllGraphicsHolder->GraphicsWithIDList.Empty();
    if (PropItemListView)
    {
      PropItemListView->ClearListItems();
    }
    APIEvents->ShowLoading();
    CurrentSelectedSubCategory = category;
    if (!EconomyItemHolder->IsCategoryEconomyItemAdded(CurrentSelectedSubCategory))
    {
      UE_LOG(LogTemp, Display, TEXT("IsCategoryEconomyItemAdded   %s"), *category);
      int gender = 3;
      APIEvents->ShowLoading();
      UEconomyHandler::GetEconomyItems(category, 1, gender, 0, 500, OnGetEconomyItemsResult, OnGetEconomyItemsError);
    }
    else
    {
      ShowPropItems(CurrentSelectedSubCategory);
    }
  }
  else if (CurrentSelectedMainCategory == "Inventory")
  {
    AllGraphicsHolder->GraphicsWithIDList.Empty();
    if (PropItemListView)
    {
      PropItemListView->ClearListItems();
    }
    APIEvents->ShowLoading();
    CurrentSelectedSubCategory = category;
    if (!EconomyItemHolder->IsCategoryEconomyItemAdded(CurrentSelectedSubCategory))
    {
      UE_LOG(LogTemp, Display, TEXT("IsCategoryEconomyItemAdded   %s"), *category);
      int gender = 3;
      APIEvents->ShowLoading();
      UEconomyHandler::GetEconomyItems(category, 1, gender, 0, 500, OnGetEconomyItemsResult, OnGetEconomyItemsError);
    }
    else
    {
      ShowPropItems(CurrentSelectedSubCategory);
    }
  }
  else
  {
    ShowInventoryPropItems(CurrentSelectedSubCategory);
  }

  //}
}
void UCustomizeHeadAvatarPanel::OnHeadDarkModeToggleStateChanged(bool bNewState)
{
    APIEvents->isDarkMode = bNewState;
  if (bNewState)
  {
    // Get the world
    UWorld* World = GetWorld();

    if (World)
    {
      // Iterate through all actors in the world
      for (TActorIterator<AExponentialHeightFog> ActorItr(World); ActorItr; ++ActorItr)
      {
        AExponentialHeightFog* FogActor = *ActorItr;
          
        // Check if the actor is an ExponentialHeightFog actor
        if (FogActor)
        {
          UActorComponent* FogComponentBase = FogActor->GetComponentByClass(UExponentialHeightFogComponent::StaticClass());

          // Check if the component is an ExponentialHeightFog component
          if (FogComponentBase)
          {
            UExponentialHeightFogComponent* FogComponent = Cast<UExponentialHeightFogComponent>(FogComponentBase);
            // Check if the cast is successful
              if (FogComponent)
            {
              // Set the fog color to black
              FogComponent->SetFogInscatteringColor(FLinearColor(0.0f, 0.003392f, 0.086039f));
            }
          }
        }
      }
    }
  
    UE_LOG(LogTemp, Display, TEXT("DARK Mode ------>>>"));

  }
  else
  {
    UWorld* World = GetWorld();

    if (World)
    {
      // Iterate through all actors in the world
      for (TActorIterator<AExponentialHeightFog> ActorItr(World); ActorItr; ++ActorItr)
      {
        AExponentialHeightFog* FogActor = *ActorItr;

        // Check if the actor is an ExponentialHeightFog actor
        if (FogActor)
        {
          UActorComponent* FogComponentBase = FogActor->GetComponentByClass(UExponentialHeightFogComponent::StaticClass());

          // Check if the component is an ExponentialHeightFog component
          if (FogComponentBase)
          {
            UExponentialHeightFogComponent* FogComponent = Cast<UExponentialHeightFogComponent>(FogComponentBase);

            // Check if the cast is successful
            if (FogComponent)
            {
              // Set the fog color to black
              FogComponent->SetFogInscatteringColor(FLinearColor::White);
            }
          }
        }
      }
    }
  }
}
void UCustomizeHeadAvatarPanel::BuildModelButton()
{
  APIEvents->ShowLoading();
  FClipExpressionData clipExpressionData;
  clipExpressionData.Style.ClipID = "61c43d03-f21c-4a7c-97fe-9665be6739a4";
  clipExpressionData.Style.ExpressionID = "";
  clipExpressionData.gender = UserDetailHolder->UserDetails.Gender == EGender::FEMALE ? 1 : 0;
  FString metaData;
  FJsonObjectConverter::UStructToJsonObjectString(clipExpressionData, metaData);

  FAvatarData avatarData;
  avatarData.AgeRange = "18-22";
  avatarData.Race = "Custom";
  avatarData.MetaData = metaData;
  avatarData.Gender = UserDetailHolder->UserDetails.Gender == EGender::FEMALE ? 1 : 0;
  avatarData.CustomMetaData = "";
  avatarData.ColorMeta = CurrentAvatarChanges->changePropColors;
  avatarData.ColorMeta.FaceColor = "#ffffff";
  avatarData.BucketData = CurrentAvatarChanges->changedProps.props;

  for (int i = 0; i < CurrentAvatarChanges->changeBlendShapes.Num(); i++)
  {
    FBlendShapeValue blendshape;
    blendshape.value = CurrentAvatarChanges->changeBlendShapes[i].value;
    blendshape.shapekeys = CurrentAvatarChanges->changeBlendShapes[i].shapekeys;
    avatarData.Blendshapes.Add(blendshape);
  }

  FGrantAvatarPresetItemsToUserRequest request;
  for (int i = 0; i < CurrentAvatarChanges->changedProps.props.Num(); i++)
  {
    FGrantAvatarPresetItemsToUserRequestItemIDsInner item;
    item.ItemID = CurrentAvatarChanges->changedProps.props[i].ID;
    request.ItemIDs.Add(item);
  }
  FString avatarDataStr;
  FJsonObjectConverter::UStructToJsonObjectString(avatarData, avatarDataStr);

  TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
  for (TFieldIterator<FProperty> It(FAvatarData::StaticStruct()); It; ++It)
  {
    FProperty *Property = *It;
    FString PropertyName = Property->GetName();
    TSharedPtr<FJsonValue> JsonValue = FJsonObjectConverter::UPropertyToJsonValue(Property, Property->ContainerPtrToValuePtr<void>(&avatarData, 0));
    JsonObject->SetField(PropertyName, JsonValue);
  }

  FString JsonString;
  TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&JsonString);
  FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);
  JsonString.ReplaceInline(TEXT("coreBucket"), TEXT("CoreBucket"));
  JsonString.ReplaceInline(TEXT("expressionId"), TEXT("ExpressionID"));
  JsonString.ReplaceInline(TEXT("clipId"), TEXT("ClipID"));
  JsonString.ReplaceInline(TEXT("hairColor"), TEXT("HairColor"));
  JsonString.ReplaceInline(TEXT("eyebrowColor"), TEXT("EyebrowColor"));
  JsonString.ReplaceInline(TEXT("facialHairColor"), TEXT("FacialHairColor"));
  JsonString.ReplaceInline(TEXT("lipColor"), TEXT("LipColor"));
  JsonString.ReplaceInline(TEXT("faceColor"), TEXT("FaceColor"));
  JsonString.ReplaceInline(TEXT("style"), TEXT("Style"));
  JsonString.ReplaceInline(TEXT("\\n"), TEXT(""));
  JsonString.ReplaceInline(TEXT("\\t"), TEXT(""));
  JsonString.ReplaceInline(TEXT("\"id\""), TEXT("\"ID\""));
  JsonString.ReplaceInline(TEXT(" "), TEXT(""));
  UE_LOG(LogTemp, Display, TEXT("============       %s"), *JsonString);

  if (DataHolder->isCustomizeAvatar)
  {

    if (AvatarHandler->TypeOfMontization == EMonitizeType::Monitize)
    {
      APIEvents->ShowLoading();
      UAvatarPresetsHandler::GrantAvatarPresetItemsToUser(
          request, [this, JsonString](FGrantAvatarPresetItemsToUserResponse result)
          {
    FGrantAvatarToUserRequest grantAvatarRequest;
    grantAvatarRequest.AvatarData = JsonString;
    UE_LOG(LogTemp, Display, TEXT("GrantAvatarPresetItemsToUser"));
    APIEvents->ShowLoading();
    UAvatarPresetsHandler::GrantAvatarPresetToUser(
        grantAvatarRequest, [this](FGrantAvatarToUserResponse gresult) {
           CommonFunctionHolder->UpdateDefaultAvatarID(gresult.Data.AvatarID, [this,gresult]
                                                                { 
      UE_LOG(LogTemp, Display, TEXT("GrantAvatarPresetToUser"));
      APIEvents->ShowLoading();
      CommonFunctionHolder->GetUserAllAvatars([this, gresult]() {
        
        UE_LOG(LogTemp, Display, TEXT("GetUserAllAvatars"));
        APIEvents->ShowLoading();
        CommonFunctionHolder->GenerateMesh(
            gresult.Data.AvatarID,
            [this, gresult](FGenerateAvatarMeshResponse resuleMesh) {
        UE_LOG(LogTemp, Display, TEXT("GenerateMesh"));
            APIEvents->ShowLoading();
            CommonFunctionHolder->RenderImage(gresult.Data.AvatarID, [this,resuleMesh](FRenderAvatarImageResponse resultImage)
            { 
              UE_LOG(LogTemp, Display, TEXT("RenderImage"));
              APIEvents->HideLoading();
              DataHolder->cameFromFirstAvatar = true;
              this->SetVisibility(ESlateVisibility::Hidden);
              CommonFunctionHolder->GetUserAllAvatars([this]() {
                APIEvents->ShowPanel(EUIPanels::HOME, true);
               });
            });
        }); 
      }); });
    },[this](FApiException errorz)
    {
          APIEvents->HideLoading();
          APIEvents->ShowErrorNotification(FString::FromInt(errorz.ErrorCode), errorz.ErrorMessage);
    }); },
          [this](FApiException error)
          {
            APIEvents->HideLoading();
            APIEvents->ShowErrorNotification(FString::FromInt(error.ErrorCode), error.ErrorMessage);
          });
    }
    else
    {
      APIEvents->ShowLoading();
      UAvatarPresetsHandler::GrantAvatarPresetItemsToUser(
          request, [this, JsonString](FGrantAvatarPresetItemsToUserResponse result)
          {
    FGrantAvatarToUserRequest grantAvatarRequest;
    grantAvatarRequest.AvatarData = JsonString;
    UE_LOG(LogTemp, Display, TEXT("GrantAvatarPresetItemsToUser"));
    APIEvents->ShowLoading();
    UAvatarPresetsHandler::GrantAvatarPresetToUser(grantAvatarRequest, [this](FGrantAvatarToUserResponse gresult)
    { 
      UE_LOG(LogTemp, Display, TEXT("GrantAvatarPresetToUser"));
      APIEvents->ShowLoading();
      CommonFunctionHolder->GetUserAllAvatars([this, gresult]() {
        
        UE_LOG(LogTemp, Display, TEXT("GetUserAllAvatars"));
        APIEvents->ShowLoading();
        CommonFunctionHolder->GenerateMesh(
            gresult.Data.AvatarID,
            [this, gresult](FGenerateAvatarMeshResponse resuleMesh) {
        UE_LOG(LogTemp, Display, TEXT("GenerateMesh"));
            APIEvents->ShowLoading();
            CommonFunctionHolder->RenderImage(gresult.Data.AvatarID, [this,resuleMesh](FRenderAvatarImageResponse resultImage)
            { 
              UE_LOG(LogTemp, Display, TEXT("RenderImage"));
              APIEvents->HideLoading();
            
              APIEvents->ShowGeneratedAvatar(resuleMesh.Data.MeshUrl,resultImage.Data.ImageURL); 
            });
        }); 
      }); 
    },[this](FApiException errorz)
    {
          APIEvents->HideLoading();
          APIEvents->ShowErrorNotification(FString::FromInt(errorz.ErrorCode), errorz.ErrorMessage);
    }); },
          [this](FApiException error)
          {
            APIEvents->HideLoading();
            APIEvents->ShowErrorNotification(FString::FromInt(error.ErrorCode), error.ErrorMessage);
          });
    }
  }
  else
  {
    APIEvents->ShowLoading();
    UAvatarPresetsHandler::GrantAvatarPresetItemsToUser(
        request, [this, JsonString](FGrantAvatarPresetItemsToUserResponse result)
        {
    FGrantAvatarToUserRequest grantAvatarRequest;
    grantAvatarRequest.AvatarData = JsonString;
    UE_LOG(LogTemp, Display, TEXT("GrantAvatarPresetItemsToUser"));
    APIEvents->ShowLoading();
    UAvatarPresetsHandler::GrantAvatarPresetToUser(grantAvatarRequest, [this](FGrantAvatarToUserResponse gresult)
    { 
      UE_LOG(LogTemp, Display, TEXT("GrantAvatarPresetToUser"));
      APIEvents->ShowLoading();
      CommonFunctionHolder->GetUserAllAvatars([this, gresult]() {
        
        UE_LOG(LogTemp, Display, TEXT("GetUserAllAvatars"));
        APIEvents->ShowLoading();
        CommonFunctionHolder->GenerateMesh(
            gresult.Data.AvatarID,
            [this, gresult](FGenerateAvatarMeshResponse resuleMesh) {
        UE_LOG(LogTemp, Display, TEXT("GenerateMesh"));
            APIEvents->ShowLoading();
            CommonFunctionHolder->RenderImage(gresult.Data.AvatarID, [this,resuleMesh](FRenderAvatarImageResponse resultImage)
            { 
              UE_LOG(LogTemp, Display, TEXT("RenderImage"));
              APIEvents->HideLoading();
              CommonFunctionHolder->GetUserAllAvatars([this]() {});
              APIEvents->ShowGeneratedAvatar(resuleMesh.Data.MeshUrl,resultImage.Data.ImageURL); 
            });
        }); 
      }); 
    },[this](FApiException errorz)
    {
          APIEvents->HideLoading();
          APIEvents->ShowErrorNotification(FString::FromInt(errorz.ErrorCode), errorz.ErrorMessage);
    }); },
        [this](FApiException error)
        {
          APIEvents->HideLoading();
          APIEvents->ShowErrorNotification(FString::FromInt(error.ErrorCode), error.ErrorMessage);
        });
  }
}
void UCustomizeHeadAvatarPanel::OnPropClickCallback(bool isSelect)
{
  if (isSelect)
  {
    InfoButton->SetVisibility(ESlateVisibility::Visible);
  }
  else
  {
    InfoButton->SetVisibility(ESlateVisibility::Hidden);
  }
}
void UCustomizeHeadAvatarPanel::ShowInventoryPropItems(FString categtory)
{
  currentSelectedItems = EconomyItemHolder->GetEconomysItemWithCat(categtory);
  TArray<FEconomyItems> TempItems;
  for (int i = 0; i < currentSelectedItems.Num(); i++)
  {
    if (UserInventoryHolder->IsPresentInventory(currentSelectedItems[i].iD))
    {
      TempItems.Add(currentSelectedItems[i]);
    }
  }
  AllGraphicsHolder->GraphicsWithIDList.Empty();
  if (PropItemListView)
  {
    PropItemListView->ClearListItems();
  }

  float floatValue = currentSelectedItems.Num();
  float contaientGridCount = floatValue / 4;
  int myCeilInt = FMath::CeilToInt(contaientGridCount);
  for (int i = 0; i < myCeilInt; i++)
  {
    UCustomizeListData *item = NewObject<UCustomizeListData>();
    item->StartIndex = 4 * i;
    item->TotalCount = TempItems.Num();
    item->currentSelectedItems = TempItems;
    PropItemListView->AddItem(item);
    PropItemListView->SetScrollbarVisibility(ESlateVisibility::Hidden);
  }
  APIEvents->HideLoading();
}

void UCustomizeHeadAvatarPanel::FaceScreenOrientation(bool isLandscape)
{
  if (isLandscape)
  {
    UVerticalBoxSlot *VerticalBoxSlot = Cast<UVerticalBoxSlot>(FaceButtonsTopPanel->Slot);
    VerticalBoxSlot->SetPadding(FMargin(0.0f, 0.0f, 980.0f, 0.0f));

    FWidgetTransform Transform;
    Transform.Translation.X = 0.0f;
    Transform.Translation.Y = -168.0f;
    Transform.Scale = FVector2D(1, 1);
    Transform.Angle = 0.0f;

    FaceButtonsTopPanel->SetRenderTransform(Transform);

    UVerticalBoxSlot *VerticalPropBoxSlot = Cast<UVerticalBoxSlot>(FacePropBottomPanel->Slot);
    VerticalPropBoxSlot->SetPadding(FMargin(950.0f, -1250.0f, 0.0f, 0.0f));

    USizeBoxSlot *FaceCoinBoxSlot = Cast<USizeBoxSlot>(FaceCoinTop_Panel->Slot);
    FaceCoinBoxSlot->SetPadding(FMargin(0, 0, 960, 0));

    UCanvasPanelSlot *Canvas = Cast<UCanvasPanelSlot>(UndoButton->Slot);
    Canvas->SetAnchors(FAnchors(0.5f, 0.5f, 0.5f, 0.5f));
    Canvas->SetOffsets(FMargin(54.0f, -0.34f, 100, 100));
  }
  else
  {
    USizeBoxSlot *FaceCoinBoxSlot = Cast<USizeBoxSlot>(FaceCoinTop_Panel->Slot);
    // FullBodyCoinBoxSlot->SetPadding(FMargin(0,0,960,0));
    FaceCoinBoxSlot->SetPadding(FMargin(0, 0, 0, 0));

    UVerticalBoxSlot *VerticalBoxSlot = Cast<UVerticalBoxSlot>(FaceButtonsTopPanel->Slot);
    VerticalBoxSlot->SetPadding(FMargin(0.0f, 0.0f, 0.0f, 0.0f));
    FWidgetTransform Transform;
    Transform.Translation.X = 0.0f;
    Transform.Translation.Y = 0.0f;
    Transform.Scale = FVector2D(1, 1);
    Transform.Angle = 0.0f;
    FaceButtonsTopPanel->SetRenderTransform(Transform);

    UVerticalBoxSlot *VerticalPropBoxSlots = Cast<UVerticalBoxSlot>(FacePropBottomPanel->Slot);
    VerticalPropBoxSlots->SetPadding(FMargin(0.0f, 0.0f, 0.0f, 0.0f));

    UCanvasPanelSlot *Canvas = Cast<UCanvasPanelSlot>(UndoButton->Slot);
    Canvas->SetAnchors(FAnchors(0.5f, 0.5f, 0.5f, 0.5f));
    Canvas->SetOffsets(FMargin(129.45f, -0.34f, 100, 100));
  }
}
void UCustomizeHeadAvatarPanel::OnItemSelected()
{
  UpdateBuySaveButtonAfterChanges();
}

void UCustomizeHeadAvatarPanel::UpdateBuySaveButtonAfterChanges()
{
  if (AvatarHandler->TypeOfMontization == EMonitizeType::Monitize)
  {
    BuySaveButton->OnClicked.RemoveDynamic(this, &UCustomizeHeadAvatarPanel::BuildModelButton);
    BuySaveButton->OnClicked.RemoveDynamic(this, &UCustomizeHeadAvatarPanel::OnClickBuySaveButton);

    BuySaveButton->SetVisibility(ESlateVisibility::Hidden);
    UCanvasPanelSlot *ButtonsScrollerSlot = Cast<UCanvasPanelSlot>(HeadResetBuyHoziBox->Slot);
    ButtonsScrollerSlot->SetAnchors(FAnchors(0, 0, 1, 1));
    ButtonsScrollerSlot->SetOffsets(FMargin(830.0f, 0.0f, 0.0f, 0.0f));
    int count = 0;
    TArray<FEconomyItems> currentSelectedBodyParts = DataHolder->currentSelectedBodyParts;
    for (int i = 0; i < currentSelectedBodyParts.Num(); i++)
    {
      if (!UserInventoryHolder->IsPresentInventory(currentSelectedBodyParts[i].iD))
      {
        count++;
      }
    }
    if (count > 0)
    {
      APIEvents->OnPropButtonClick(true);
      BuyTextHeadPanel->SetText(FText::FromString("Buy"));
      UCanvasPanelSlot *ButtonsScrollSlot = Cast<UCanvasPanelSlot>(HeadResetBuyHoziBox->Slot);
      ButtonsScrollSlot->SetAnchors(FAnchors(0, 0, 1, 1));
      ButtonsScrollSlot->SetOffsets(FMargin(600.0f, 0.0f, 0.0f, 0.0f));
      BuySaveButton->SetVisibility(ESlateVisibility::Visible);
      BuySaveButton->OnClicked.AddDynamic(this, &UCustomizeHeadAvatarPanel::OnClickBuySaveButton);
    }
    else
    {
      BuySaveButton->SetVisibility(ESlateVisibility::Visible);
      UCanvasPanelSlot *ButtonsScrollSlot = Cast<UCanvasPanelSlot>(HeadResetBuyHoziBox->Slot);
      ButtonsScrollSlot->SetAnchors(FAnchors(0, 0, 1, 1));
      ButtonsScrollSlot->SetOffsets(FMargin(600.0f, 0.0f, 0.0f, 0.0f));
      APIEvents->OnPropButtonClick(false);
      BuyTextHeadPanel->SetText(FText::FromString("Save"));
      BuySaveButton->OnClicked.AddDynamic(this, &UCustomizeHeadAvatarPanel::BuildModelButton);
    }
  }
  else
  {
    BuySaveButton->SetVisibility(ESlateVisibility::Visible);
    UCanvasPanelSlot *ButtonsScrollSlot = Cast<UCanvasPanelSlot>(HeadResetBuyHoziBox->Slot);
    ButtonsScrollSlot->SetAnchors(FAnchors(0, 0, 1, 1));
    ButtonsScrollSlot->SetOffsets(FMargin(600.0f, 0.0f, 0.0f, 0.0f));
    BuyTextHeadPanel->SetText(FText::FromString("Save"));
    BuySaveButton->OnClicked.RemoveDynamic(this, &UCustomizeHeadAvatarPanel::BuildModelButton);
    BuySaveButton->OnClicked.AddDynamic(this, &UCustomizeHeadAvatarPanel::BuildModelButton);
  }
}
