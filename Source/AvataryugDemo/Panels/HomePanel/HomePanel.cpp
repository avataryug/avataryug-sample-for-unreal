// Fill out your copyright notice in the Description page of Project Settings.

#include "HomePanel.h"
#include "Components/Button.h"
#include "GameStructs.h"
#include "../../DataHolders/EconomyItemHolder.h"
#include "Kismet/GameplayStatics.h"
#include "AvatarPresetsAPI/AvatarPresetsHandler.h"
#include "AvatarPresetsAPI/AvatarPresetsModel.h"

void UHomePanel::NativeConstruct()
{
  Super::NativeConstruct();


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

  if (AvatarHandler == nullptr)
  {
    AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AAvatarHandler::StaticClass());
    AvatarHandler = Cast<AAvatarHandler>(FoundActor);
  }

  if (CurrentAvatarChangesHolder == nullptr)
  {
    AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), ACurrentAvatarChanges::StaticClass());
    CurrentAvatarChangesHolder = Cast<ACurrentAvatarChanges>(FoundActor);
  }

  AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), ACommonFunction::StaticClass());
  CommonFunctionHolder = Cast<ACommonFunction>(FoundActor);
  if (CommonFunctionHolder == nullptr)
  {
    CommonFunctionHolder = GetWorld()->SpawnActor<ACommonFunction>();
  }
  
  HP_SettingButton->OnClicked.RemoveDynamic(this, &UHomePanel::OnClickSettingButton);
  HP_SettingButton->OnClicked.AddDynamic(this, &UHomePanel::OnClickSettingButton);

  InventoryButton->OnClicked.RemoveDynamic(this, &UHomePanel::OnClickInventoryButton);
  InventoryButton->OnClicked.AddDynamic(this, &UHomePanel::OnClickInventoryButton);

  ContainersButton->OnClicked.RemoveDynamic(this, &UHomePanel::OnClickContainesButton);
  ContainersButton->OnClicked.AddDynamic(this, &UHomePanel::OnClickContainesButton);

  BundlesButton->OnClicked.RemoveDynamic(this, &UHomePanel::OnClickBundlesButton);
  BundlesButton->OnClicked.AddDynamic(this, &UHomePanel::OnClickBundlesButton);

  RewardButton->OnClicked.RemoveDynamic(this, &UHomePanel::OnClickRewardButton);
  RewardButton->OnClicked.AddDynamic(this, &UHomePanel::OnClickRewardButton);

  CustomizeAvatarButton->OnClicked.RemoveDynamic(this, &UHomePanel::OnClickCustomizeAvatarButton);
  CustomizeAvatarButton->OnClicked.AddDynamic(this, &UHomePanel::OnClickCustomizeAvatarButton);

  // LobbyCoinButton->OnClicked.RemoveDynamic(this, &UHomePanel::OnClickLobbyCoinButton);
  // LobbyCoinButton->OnClicked.AddDynamic(this, &UHomePanel::OnClickLobbyCoinButton);
}

void UHomePanel::OnClickSettingButton()
{
  if (APIEvents != nullptr)
  {
    APIEvents->ShowPanel(EUIPanels::SETTING, true);
  }
}

void UHomePanel::LoadHomePanelDetail() {
      APIEvents->OnChangeCamera.Broadcast(CameraPanels::Lobby);
    AvatarHandler->SetActorRotation(FRotator(0, 0, 0));
  CoinHeaderPanel->SetCoins();
  FString platfrom = "Android";
  FString modelurl = "";
  if (UserDetailHolder->tempmeshurl != "")
  {
    modelurl = UserDetailHolder->tempmeshurl;
  }
  else
  {
    for (auto &item : UserDetailHolder->UserDetails.currentUserSelectedAvatar.AvatarUrls)
    {
      if (item.Platform == platfrom) 
      {
        modelurl = item.MeshURL;
      }
    }
  }
  DataHolder->isCustomizeAvatar = false;
   UE_LOG(LogTemp, Display, TEXT(">>>>>>>>   %s"),*modelurl);
  AvatarHandler->LoadHomePanelModel(modelurl, [this]()
  { 
    CommonFunctionHolder->SetCurrentAvatarDetail();
    if(AvatarHandler->customizeAvatarLoader->spawnedHeadActor == nullptr)
    {
      AvatarHandler->customizeAvatarLoader->LoadHeadModel([this] {
        LoadCurrentAvatarData([this] {
         APIEvents->HideLoading(); 
          });
      });
    }
    else
    {
      if (DataHolder->cameFromFirstAvatar)
      {
        DataHolder->cameFromFirstAvatar= false;
        LoadCurrentAvatarData([this] {
          APIEvents->HideLoading();
          });
      }
    }
  });
}

void UHomePanel::OnClickInventoryButton()
{
  if (APIEvents != nullptr)
  {
    APIEvents->ShowPanel(EUIPanels::INVENTORY, true);
  }
}

void UHomePanel::OnClickContainesButton()
{
  if (APIEvents != nullptr)
  {
    APIEvents->ShowPanel(EUIPanels::CONTAINERS, true);
  }
}

void UHomePanel::OnClickBundlesButton()
{
  if (APIEvents != nullptr)
  {
    APIEvents->ShowPanel(EUIPanels::BUNDLES, true);
  }
}

void UHomePanel::OnClickRewardButton()
{
  if (APIEvents != nullptr)
  {
    APIEvents->ShowPanel(EUIPanels::REWARDEDADS, true);
  }
}

void UHomePanel::OnClickCustomizeAvatarButton()
{
  DataHolder->resetToCurrentModel =true;
  AvatarHandler->ForCustomizeAvatar = AvatarHandler->customizeAvatarLoader;
  this->SetVisibility(ESlateVisibility::Hidden);
  APIEvents->ShowPanel(EUIPanels::CUSTOMIZEFULL, true);
  APIEvents->OnChangeCamera.Broadcast(CameraPanels::CustomizeAvatar_FullBody);
}

void UHomePanel::OnClickLobbyCoinButton()
{
  if (APIEvents != nullptr)
  {
    this->SetVisibility(ESlateVisibility::Hidden);
    APIEvents->ShowPanel(EUIPanels::CURRENCYSTORE, true);
  }
}

void UHomePanel::LoadCustomizeAvatars()
{

}

void UHomePanel::LoadCurrentAvatarData(TFunction<void()> oncomplete) 
{
  FString avatarid = UserDetailHolder->UserDetails.currentUserSelectedAvatar.AvatarID;
  UAvatarPresetsHandler::GetUserAvatarAllData(avatarid,"Android", [this,oncomplete](FGetUserAvatarAllDataResponse result) 
  {
    AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AEconomyItemHolder::StaticClass());
    AEconomyItemHolder *EconomyItemHolder = Cast<AEconomyItemHolder>(FoundActor);
    EconomyItemHolder->AddEconomyItemDataFromAvatar(result);
    oncomplete();
  },
  [this](FApiException error)
  {
    UE_LOG(LogTemp, Display, TEXT("ON GETECONOMY ERROR--->>%s"),*error.ErrorMessage);
  });
}