// Fill out your copyright notice in the Description page of Project Settings.

#include "CustomizeFullAvatarPanel.h"
#include "Components/Button.h"
#include "CommonModels.h"
#include "PropItemGridPanel.h"
#include "CustomizeData.h"
#include "EconomyAPI/EconomyHandler.h"
#include "EconomyAPI/EconomyRequest.h"
#include "EconomyAPI/EconomyModel.h"
#include "Components/ListView.h"
#include "Widgets/SViewport.h"
#include "Kismet/GameplayStatics.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/SizeBoxSlot.h"
#include "Components/CanvasPanelSlot.h"
// #include "Engine/World.h"
#include "EngineUtils.h"
#include "Components/ExponentialHeightFogComponent.h"
#include "Engine/World.h"
#include "Engine/CanvasRenderTarget2D.h"
#include "CategoryButton.h"
#include "JsonObjectConverter.h"

void UCustomizeFullAvatarPanel::NativeConstruct()
{
  Super::NativeConstruct();

  GetReference();

  SetButtonEvents();

  SubscribeEvents();

  SetInitialDetails();
}

void UCustomizeFullAvatarPanel::GetReference()
{
  if (CurrentAvatarChanges == nullptr)
  {
    AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), ACurrentAvatarChanges::StaticClass());
    CurrentAvatarChanges = Cast<ACurrentAvatarChanges>(FoundActor);
    if (CurrentAvatarChanges == nullptr)
    {
      CurrentAvatarChanges = GetWorld()->SpawnActor<ACurrentAvatarChanges>();
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
  if (UndoHandler == nullptr)
  {
    AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AUndoHandler::StaticClass());
    UndoHandler = Cast<AUndoHandler>(FoundActor);
    if (UndoHandler == nullptr)
    {
      UndoHandler = GetWorld()->SpawnActor<AUndoHandler>();
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

  if (UserInventoryHolder == nullptr)
  {
    AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AUserInventoryHolder::StaticClass());
    UserInventoryHolder = Cast<AUserInventoryHolder>(FoundActor);
    if (UserInventoryHolder == nullptr)
    {
      UserInventoryHolder = GetWorld()->SpawnActor<AUserInventoryHolder>();
    }
  }

  if (AvatarHandler == nullptr)
  {
    AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AAvatarHandler::StaticClass());
    AvatarHandler = Cast<AAvatarHandler>(FoundActor);
  }
  if (AllGraphicsHolder == nullptr)
  {
    AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AAllGraphicsHolder::StaticClass());
    AllGraphicsHolder = Cast<AAllGraphicsHolder>(FoundActor);
  }
  if (UserDetailHolder == nullptr)
  {
    AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AUserDetailHolder::StaticClass());
    UserDetailHolder = Cast<AUserDetailHolder>(FoundActor);
    if (UserDetailHolder == nullptr)
    {
      UserDetailHolder = GetWorld()->SpawnActor<AUserDetailHolder>();
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
}

void UCustomizeFullAvatarPanel::SetButtonEvents()
{
  InfoButton->OnClicked.RemoveDynamic(this, &UCustomizeFullAvatarPanel::OnClickInfoButton);
  InfoButton->OnClicked.AddDynamic(this, &UCustomizeFullAvatarPanel::OnClickInfoButton);

  UndoButton->OnClicked.RemoveDynamic(this, &UCustomizeFullAvatarPanel::OnClickUndoButton);
  UndoButton->OnClicked.AddDynamic(this, &UCustomizeFullAvatarPanel::OnClickUndoButton);

  ResetButton->OnClicked.RemoveDynamic(this, &UCustomizeFullAvatarPanel::OnClickResetButton);
  ResetButton->OnClicked.AddDynamic(this, &UCustomizeFullAvatarPanel::OnClickResetButton);

  SortButton->OnClicked.RemoveDynamic(this, &UCustomizeFullAvatarPanel::OnClickSortButton);
  SortButton->OnClicked.AddDynamic(this, &UCustomizeFullAvatarPanel::OnClickSortButton);

  hightolowButton->OnClicked.RemoveDynamic(this, &UCustomizeFullAvatarPanel::SortHightoLow);
  hightolowButton->OnClicked.AddDynamic(this, &UCustomizeFullAvatarPanel::SortHightoLow);

  lowtohighButton->OnClicked.RemoveDynamic(this, &UCustomizeFullAvatarPanel::SortLowToHigh);
  lowtohighButton->OnClicked.AddDynamic(this, &UCustomizeFullAvatarPanel::SortLowToHigh);

  CancelSortButton->OnClicked.RemoveDynamic(this, &UCustomizeFullAvatarPanel::CloseSortPanel);
  CancelSortButton->OnClicked.AddDynamic(this, &UCustomizeFullAvatarPanel::CloseSortPanel);

  BackButton->OnClicked.RemoveDynamic(this, &UCustomizeFullAvatarPanel::OnClickBackButton);
  BackButton->OnClicked.AddDynamic(this, &UCustomizeFullAvatarPanel::OnClickBackButton);

  ZoomButton->OnClicked.RemoveDynamic(this, &UCustomizeFullAvatarPanel::OnClickZoomButton);
  ZoomButton->OnClicked.AddDynamic(this, &UCustomizeFullAvatarPanel::OnClickZoomButton);

  ZoomOutButton->OnClicked.RemoveDynamic(this, &UCustomizeFullAvatarPanel::OnClickZoomoutButton);
  ZoomOutButton->OnClicked.AddDynamic(this, &UCustomizeFullAvatarPanel::OnClickZoomoutButton);

  HeadCustomizeButton->OnClicked.RemoveDynamic(this, &UCustomizeFullAvatarPanel::OnClickHeadCustomizeButton);
  HeadCustomizeButton->OnClicked.AddDynamic(this, &UCustomizeFullAvatarPanel::OnClickHeadCustomizeButton);

  ExpressionClipButton->OnClicked.RemoveDynamic(this, &UCustomizeFullAvatarPanel::OnClickExpressionClipButton);
  ExpressionClipButton->OnClicked.AddDynamic(this, &UCustomizeFullAvatarPanel::OnClickExpressionClipButton);

  DarkModeToggle->OnCheckStateChanged.RemoveDynamic(this, &UCustomizeFullAvatarPanel::OnDarkModeToggleStateChanged);
  DarkModeToggle->OnCheckStateChanged.AddDynamic(this, &UCustomizeFullAvatarPanel::OnDarkModeToggleStateChanged);
}

void UCustomizeFullAvatarPanel::SubscribeEvents()
{

  OnClickSubCategory.BindUFunction(this, "OnClickSubCategoryButton");

  APIEvents->OnUpdateUiAfterItemSelect.RemoveDynamic(this, &UCustomizeFullAvatarPanel::OnItemSelected);
  APIEvents->OnUpdateUiAfterItemSelect.AddDynamic(this, &UCustomizeFullAvatarPanel::OnItemSelected);

  APIEvents->OnUpdateUiAfterPurchase.RemoveDynamic(this, &UCustomizeFullAvatarPanel::UpdateUIAfterPurchase);
  APIEvents->OnUpdateUiAfterPurchase.AddDynamic(this, &UCustomizeFullAvatarPanel::UpdateUIAfterPurchase);

  OnClickMainCategory.RemoveDynamic(this, &UCustomizeFullAvatarPanel::OnClickMainCategoryButton);
  OnClickMainCategory.AddDynamic(this, &UCustomizeFullAvatarPanel::OnClickMainCategoryButton);

  APIEvents->OnScreenOrientation.AddDynamic(this, &UCustomizeFullAvatarPanel::FullBodyScreenOrientation);
}

void UCustomizeFullAvatarPanel::SetInitialDetails()
{
  UndoButton->SetVisibility(ESlateVisibility::Hidden);
}

void UCustomizeFullAvatarPanel::OnClickBackButton()
{
  this->SetVisibility(ESlateVisibility::Hidden);
  if (APIEvents != nullptr)
  {
    APIEvents->ShowPanel(EUIPanels::HOME, true);
    APIEvents->OnChangeCamera.Broadcast(CameraPanels::Lobby);
  }
}

void UCustomizeFullAvatarPanel::OnClickExpressionClipButton()
{
  this->SetVisibility(ESlateVisibility::Hidden);
  APIEvents->ShowPanel(EUIPanels::EXPRESSIONCLIP, true);
}

void UCustomizeFullAvatarPanel::OnClickZoomButton()
{
  CustomizeFullBodyPanel->SetVisibility(ESlateVisibility::Hidden);
  ZoomInPanel->SetVisibility(ESlateVisibility::Visible);
  APIEvents->OnChangeCamera.Broadcast(CameraPanels::CustomizeAvatar_Zoom);
}

void UCustomizeFullAvatarPanel::OnClickZoomoutButton()
{
  CustomizeFullBodyPanel->SetVisibility(ESlateVisibility::Visible);
  ZoomInPanel->SetVisibility(ESlateVisibility::Hidden);
  APIEvents->OnChangeCamera.Broadcast(CameraPanels::CustomizeAvatar_FullBody);
}

void UCustomizeFullAvatarPanel::OnClickInfoButton()
{
  APIEvents->ShowPanel(EUIPanels::DETAILS, true);
}

void UCustomizeFullAvatarPanel::OnClickUndoButton()
{
  UndoHandler->OnClickUndo();
}

void UCustomizeFullAvatarPanel::OnClickResetButton()
{
  ResetFullAvatarPanel->SetVisibility(ESlateVisibility::Visible);
}

void UCustomizeFullAvatarPanel::OnClickSortButton()
{
  SortPanel->SetVisibility(ESlateVisibility::Visible);
}
void UCustomizeFullAvatarPanel::CloseSortPanel()
{
  SortPanel->SetVisibility(ESlateVisibility::Hidden);
}

void UCustomizeFullAvatarPanel::LoadCustomizeAvatarPanelData() {
  AvatarHandler->ForCustomizeAvatar = AvatarHandler->customizeAvatarLoader;
    APIEvents->OnChangeCamera.Broadcast(CameraPanels::CustomizeAvatar_FullBody);
    if (APIEvents->isDarkMode)
    {
      DarkModeToggle->SetCheckedState(ECheckBoxState::Checked);
       OnDarkModeToggleStateChanged(APIEvents->isDarkMode);
    }
    else
    {
      DarkModeToggle->SetCheckedState(ECheckBoxState::Unchecked);
      OnDarkModeToggleStateChanged(APIEvents->isDarkMode);
    }
 
  if(AvatarHandler->TypeOfMontization == EMonitizeType::NonMonitize)
  {
     UE_LOG(LogTemp, Display, TEXT("TypeOfMontization->--NonMonitize-->> "));
    FullBodyCoinTop_Panel->SetVisibility(ESlateVisibility::Hidden);
    SortButtonBox->SetVisibility(ESlateVisibility::Collapsed);
  }
  else
  {
     UE_LOG(LogTemp, Display, TEXT("TypeOfMontization->--Monitize-->> "));
    FullBodyCoinTop_Panel->SetVisibility(ESlateVisibility::Visible);
      SortButtonBox->SetVisibility(ESlateVisibility::Visible);
  }

  InfoButton->SetVisibility(ESlateVisibility::Hidden);
  AvatarHandler->SetActorRotation(FRotator(0, 0, 0));
  // AvatarLoader->SetParentVisibility(false, false, true);

  AvatarHandler->ForCustomizeAvatar->SetParentVisibility(false, false, true);
  if (MainCategoryButton.Num() <= 0)
  {
    MainCategoryButton.Add(AvatarButton);
    MainCategoryButton.Add(InventoryButton);
    MainCategoryButton.Add(TopButton);
    MainCategoryButton.Add(BottomButton);
    MainCategoryButton.Add(OutfitButton);
    MainCategoryButton.Add(HandwearButton);
    MainCategoryButton.Add(WristwearButton);
    MainCategoryButton.Add(FootwearButton);
    MainCategoryButton.Add(TattooButton);
  }

  for (int i = 0; i < MainCategoryButton.Num(); i++)
  {
    MainCategoryButton[i]->SetButton(i, MainCategorys[i], OnClickMainCategory);
  }

  APIEvents->OnSetModelParentDelegate.Broadcast(EModelParent::CUSTOMIZE);
  OnClickMainCategoryButton("Top");
   if(AvatarHandler->TypeOfMontization == EMonitizeType::NonMonitize)
  {
    
  }
  else
  {
  CoinHeaderPanel->SetCoins();
  }
 
  ResetFullAvatarPanel->SetVisibility(ESlateVisibility::Hidden);
  OnItemSelected();

  if (DataHolder->resetToCurrentModel)
  {
    DataHolder->resetToCurrentModel = false;
    CommonFunctionHolder->SetCurrentAvatarDetail();
    AvatarHandler->customizeAvatarLoader->ResetData();
    AvatarHandler->customizeAvatarLoader->ResetToCurrentSelectedModel([this] {});
  }
}

void UCustomizeFullAvatarPanel::OnClickMainCategoryButton(FString category)
{
  // if (CurrentSelectedMainCategory != category)
  // {
  CurrentSelectedMainCategory = category;
  if (category == "Inventory")
  {
    SubCategorySizeBox->bOverride_MinDesiredHeight = true;
    SubCategorySizeBox->SetMinDesiredHeight(100.0f);
    SubCategorySizeBox->SetVisibility(ESlateVisibility::Visible);
    if (SubCatListView)
    {
      SubCatListView->ClearListItems();
    }
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
  else if (category == "Tatto")
  {
    SubCategorySizeBox->bOverride_MinDesiredHeight = true;
    SubCategorySizeBox->SetMinDesiredHeight(100.0f);
    SubCategorySizeBox->SetVisibility(ESlateVisibility::Visible);
    if (SubCatListView)
    {
      SubCatListView->ClearListItems();
    }
    for (int i = 0; i < TattooCategorys.Num(); i++)
    {
      UCustomizeSubCatListData *item = NewObject<UCustomizeSubCatListData>();
      item->Index = i;
      item->Category = TattooCategorys[i];
      item->ClickSubCategory = OnClickSubCategory;
      SubCatListView->AddItem(item);
      SubCatListView->SetScrollbarVisibility(ESlateVisibility::Collapsed);
    }
  }
  else if (category == "Avatars")
  {

    if (PropItemListView)
    {
      PropItemListView->ClearListItems();
    }
    float floatValue = UserDetailHolder->UserDetails.userAvatars.Num();
    float contaientGridCount = floatValue / 4;
    int myCeilInt = FMath::CeilToInt(contaientGridCount);
    for (int i = 0; i < myCeilInt; i++)
    {
      UCustomizeListData *item = NewObject<UCustomizeListData>();
      item->StartIndex = 4 * i;
      item->dataType = "AVATAR";
      item->TotalCount = UserDetailHolder->UserDetails.userAvatars.Num();
      item->userAvatars = UserDetailHolder->UserDetails.userAvatars;
      PropItemListView->AddItem(item);
      PropItemListView->SetScrollbarVisibility(ESlateVisibility::Hidden);
    }
    APIEvents->HideLoading();

    UE_LOG(LogTemp, Display, TEXT("Avatars--Category--->>>  %s"), *category);
  }
  else
  {
    SubCategorySizeBox->bOverride_MinDesiredHeight = true;
    SubCategorySizeBox->SetMinDesiredHeight(0.0f);
    SubCategorySizeBox->SetVisibility(ESlateVisibility::Hidden);
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
      int gender = GetGender(category);
      UEconomyHandler::GetEconomyItems(
          category, 1, gender, 0, 500, [this](FGetEconomyItemsResult result)
          {
              EconomyItemHolder->AddEconomyItemData(result);
                ShowPropItems(CurrentSelectedMainCategory); },
          [this](FApiException error) {

          });
    }
    else
    {
      ShowPropItems(CurrentSelectedMainCategory);
    }
  }
  // }
}

void UCustomizeFullAvatarPanel::OnClickSubCategoryButton(FString category)
{
  // if (CurrentSelectedSubCategory != category)
  //{

  CurrentSelectedSubCategory = category;
  if (CurrentSelectedMainCategory == "Tatto")
  {
    if (!EconomyItemHolder->IsCategoryEconomyItemAdded(CurrentSelectedSubCategory))
    {
      UE_LOG(LogTemp, Display, TEXT("IsCategoryEconomyItemAdded   %s"), *category);
      int gender = GetGender(category);
      APIEvents->ShowLoading();
      UEconomyHandler::GetEconomyItems(
          category, 1, gender, 0, 500,
          [this](FGetEconomyItemsResult result)
          {
            EconomyItemHolder->AddEconomyItemData(result);
            if (CurrentSelectedMainCategory == "Inventory")
            {
              ShowInventoryPropItems(CurrentSelectedSubCategory);
            }
            else
            {
              ShowPropItems(CurrentSelectedSubCategory);
            }
          },
          [this](FApiException error) {});
    }
    else
    {
      ShowPropItems(CurrentSelectedSubCategory);
    }
  }
  else if (CurrentSelectedMainCategory == "Inventory")
  {
    if (!EconomyItemHolder->IsCategoryEconomyItemAdded(CurrentSelectedSubCategory))
    {
      UE_LOG(LogTemp, Display, TEXT("IsCategoryEconomyItemAdded   %s"), *category);
      int gender = GetGender(category);
      APIEvents->ShowLoading();
      UEconomyHandler::GetEconomyItems(
          category, 1, gender, 0, 500,
          [this](FGetEconomyItemsResult result)
          {
            EconomyItemHolder->AddEconomyItemData(result);
            if (CurrentSelectedMainCategory == "Inventory")
            {
              ShowInventoryPropItems(CurrentSelectedSubCategory);
            }
            else
            {
              ShowPropItems(CurrentSelectedSubCategory);
            }
          },
          [this](FApiException error) {});
    }
    else
    {
      ShowPropItems(CurrentSelectedSubCategory);
    }
  }
  else
  {
    if (!EconomyItemHolder->IsCategoryEconomyItemAdded(CurrentSelectedSubCategory))
    {
      UE_LOG(LogTemp, Display, TEXT("IsCategoryEconomyItemAdded   %s"), *category);
      int gender = GetGender(category);
      APIEvents->ShowLoading();
      UEconomyHandler::GetEconomyItems(
          category, 1, gender, 0, 500,
          [this](FGetEconomyItemsResult result)
          {
            EconomyItemHolder->AddEconomyItemData(result);
            if (CurrentSelectedMainCategory == "Inventory")
            {
              ShowInventoryPropItems(CurrentSelectedSubCategory);
            }
            else
            {
              ShowPropItems(CurrentSelectedSubCategory);
            }
          },
          [this](FApiException error) {});
    }
    else
    {
      ShowPropItems(CurrentSelectedSubCategory);
    }
  }

  //}
}

void UCustomizeFullAvatarPanel::ShowPropItems(FString categtory)
{
  currentSelectedItems = EconomyItemHolder->GetEconomysItemWithCat(categtory);
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
  APIEvents->HideLoading();
}

void UCustomizeFullAvatarPanel::ShowInventoryPropItems(FString categtory)
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
void UCustomizeFullAvatarPanel::SortHightoLow()
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
    PropItemListView->SetScrollbarVisibility(ESlateVisibility::Hidden);
  }
  APIEvents->HideLoading();
  CustomizeFullBodyPanel->SetVisibility(ESlateVisibility::Visible);
  SortPanel->SetVisibility(ESlateVisibility::Hidden);
  // for(const FEconomyItems& Item: currentSelectedItems)
  // {

  // }
}

void UCustomizeFullAvatarPanel::SortLowToHigh()
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
    PropItemListView->SetScrollbarVisibility(ESlateVisibility::Hidden);
  }
  APIEvents->HideLoading();
  // for(const FEconomyItems& Item: currentSelectedItems)
  // {

  // }
  CustomizeFullBodyPanel->SetVisibility(ESlateVisibility::Visible);
  SortPanel->SetVisibility(ESlateVisibility::Hidden);
}

void UCustomizeFullAvatarPanel::OnClickHeadCustomizeButton()
{
  this->SetVisibility(ESlateVisibility::Hidden);
  APIEvents->ShowPanel(EUIPanels::CUSTOMIZEHEAD, true);
  APIEvents->OnChangeCamera.Broadcast(CameraPanels::CustomizeAvatar_Head);
}

void UCustomizeFullAvatarPanel::OnPropClickCallback(bool isSelect)
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

void UCustomizeFullAvatarPanel::OnItemSelected()
{
  UpdateBuySaveButtonAfterChanges();
}

void UCustomizeFullAvatarPanel::OnDarkModeToggleStateChanged(bool bNewState)
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

void UCustomizeFullAvatarPanel::FullBodyScreenOrientation(bool isLandscape)
{
  if (isLandscape)
  {
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, "FullBody isLandscape------>>");
    UVerticalBoxSlot *VerticalBoxSlot = Cast<UVerticalBoxSlot>(FullBodyButtonsTopPanel->Slot);
    VerticalBoxSlot->SetPadding(FMargin(0.0f, 0.0f, 980.0f, 0.0f));

    FWidgetTransform Transform;
    Transform.Translation.X = 0.0f;
    Transform.Translation.Y = -168.0f;
    Transform.Scale = FVector2D(1, 1);
    Transform.Angle = 0.0f;

    FullBodyButtonsTopPanel->SetRenderTransform(Transform);
    // FullBodyButtonsTopPanel->RenderTransform
    // TOP SBoxPanel
    // FMargin(0.0f,0.0f,980.0f,0.0f);
    // Render transfrom (0,-168)
    // Bottom PAnel
    // slot padding (950,-1250,0,0)
    // UndoButton Position x = 54
    UVerticalBoxSlot *VerticalPropBoxSlot = Cast<UVerticalBoxSlot>(FullBodyPropBottomPanel->Slot);
    VerticalPropBoxSlot->SetPadding(FMargin(950.0f, -1250.0f, 0.0f, 0.0f));

    USizeBoxSlot *FullBodyCoinBoxSlot = Cast<USizeBoxSlot>(FullBodyCoinTop_Panel->Slot);
    FullBodyCoinBoxSlot->SetPadding(FMargin(0, 0, 960, 0));

    UCanvasPanelSlot *Canvas = Cast<UCanvasPanelSlot>(UndoButton->Slot);
    Canvas->SetAnchors(FAnchors(0.5f, 0.5f, 0.5f, 0.5f));
    Canvas->SetOffsets(FMargin(54.0f, -0.34f, 100, 100));
  }
  else
  {
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, "FullBody Potrait------>>");

    USizeBoxSlot *FullBodyCoinBoxSlot = Cast<USizeBoxSlot>(FullBodyCoinTop_Panel->Slot);
    // FullBodyCoinBoxSlot->SetPadding(FMargin(0,0,960,0));
    FullBodyCoinBoxSlot->SetPadding(FMargin(0, 0, 0, 0));

    UVerticalBoxSlot *VerticalBoxSlot = Cast<UVerticalBoxSlot>(FullBodyButtonsTopPanel->Slot);
    VerticalBoxSlot->SetPadding(FMargin(0.0f, 0.0f, 0.0f, 0.0f));
    FWidgetTransform Transform;
    Transform.Translation.X = 0.0f;
    Transform.Translation.Y = 0.0f;
    Transform.Scale = FVector2D(1, 1);
    Transform.Angle = 0.0f;
    FullBodyButtonsTopPanel->SetRenderTransform(Transform);

    UVerticalBoxSlot *VerticalPropBoxSlots = Cast<UVerticalBoxSlot>(FullBodyPropBottomPanel->Slot);
    VerticalPropBoxSlots->SetPadding(FMargin(0.0f, 0.0f, 0.0f, 0.0f));

    UCanvasPanelSlot *Canvas = Cast<UCanvasPanelSlot>(UndoButton->Slot);
    Canvas->SetAnchors(FAnchors(0.5f, 0.5f, 0.5f, 0.5f));
    Canvas->SetOffsets(FMargin(129.45f, -0.34f, 100, 100));
  }
}

void UCustomizeFullAvatarPanel::UpdateBuySaveButtonAfterChanges()
{
  BuySaveButton->OnClicked.RemoveDynamic(this, &UCustomizeFullAvatarPanel::BuildModelButton);
  BuySaveButton->OnClicked.RemoveDynamic(this, &UCustomizeFullAvatarPanel::OnClickBuySaveButton);
  if (AvatarHandler->TypeOfMontization == EMonitizeType::Monitize)
  {
    BuySaveButton->SetVisibility(ESlateVisibility::Hidden);

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
      BuyText->SetText(FText::FromString("Buy"));
      UCanvasPanelSlot *ButtonsScrollSlot = Cast<UCanvasPanelSlot>(ResetBuyHorizontalBox->Slot);
      ButtonsScrollSlot->SetAnchors(FAnchors(0, 0, 1, 1));
      ButtonsScrollSlot->SetOffsets(FMargin(600.0f, 0.0f, 0.0f, 0.0f));
      BuySaveButton->SetVisibility(ESlateVisibility::Visible);
      BuySaveButton->OnClicked.AddDynamic(this, &UCustomizeFullAvatarPanel::OnClickBuySaveButton);
    }
    else
    {
      BuyText->SetText(FText::FromString("Save"));
      BuySaveButton->SetVisibility(ESlateVisibility::Visible);
      UCanvasPanelSlot *ButtonsScrollSlot = Cast<UCanvasPanelSlot>(ResetBuyHorizontalBox->Slot);
      ButtonsScrollSlot->SetAnchors(FAnchors(0, 0, 1, 1));
      ButtonsScrollSlot->SetOffsets(FMargin(600.0f, 0.0f, 0.0f, 0.0f));
      BuySaveButton->OnClicked.AddDynamic(this, &UCustomizeFullAvatarPanel::BuildModelButton);
    }
  }
  else
  {
    BuySaveButton->SetVisibility(ESlateVisibility::Visible);
    UCanvasPanelSlot *ButtonsScrollSlot = Cast<UCanvasPanelSlot>(ResetBuyHorizontalBox->Slot);
    ButtonsScrollSlot->SetAnchors(FAnchors(0, 0, 1, 1));
    ButtonsScrollSlot->SetOffsets(FMargin(600.0f, 0.0f, 0.0f, 0.0f));
    BuyText->SetText(FText::FromString("Save"));
    BuySaveButton->OnClicked.AddDynamic(this, &UCustomizeFullAvatarPanel::BuildModelButton);
  }
}

void UCustomizeFullAvatarPanel::BuildModelButton()
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
             DataHolder->cameFromFirstAvatar =true;
     
                 CommonFunctionHolder->GetUserAllAvatars([this]() {
                               this->SetVisibility(ESlateVisibility::Hidden);
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

              APIEvents->ShowGeneratedAvatar(resuleMesh.Data.MeshUrl,
                                             resultImage.Data.ImageURL);
                    CommonFunctionHolder->GetUserAllAvatars([this]() {});
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

void UCustomizeFullAvatarPanel::OnClickBuySaveButton()
{
  APIEvents->ShowPanel(EUIPanels::BUYITEMS, true);
}

int UCustomizeFullAvatarPanel::GetGender(FString category)
{
  int gender = 3;
  if (category == "Top" || category == "Bottom" || category == "Outfit")
  {
    switch (UserDetailHolder->UserDetails.Gender)
    {
    case EGender::MALE:
      gender = 1;
      break;
    case EGender::FEMALE:
      gender = 2;
      break;
    }
  }
  return gender;
}

void UCustomizeFullAvatarPanel::UpdateUIAfterPurchase()
{
  UpdateBuySaveButtonAfterChanges();
}