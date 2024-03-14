// Fill out your copyright notice in the Description page of Project Settings.

#include "InAppHUD.h"
#include <components/Button.h>
#include <components/TextBlock.h>
#include "Kismet/GameplayStatics.h"
#include "GameEnums.h"
#include "Components/PanelWidget.h"

AInAppHUD::AInAppHUD()
{
}

void AInAppHUD::BeginPlay()
{
    Super::BeginPlay();

    if (APIEvents == nullptr)
    {
        AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AAPIEvents::StaticClass());
        APIEvents = Cast<AAPIEvents>(FoundActor);
        if (APIEvents == nullptr)
        {
            APIEvents = GetWorld()->SpawnActor<AAPIEvents>();
        }
    }
    APIEvents->OnShowLoadingPanel.RemoveDynamic(this, &AInAppHUD::ShowLoadingPanel);
    APIEvents->OnShowLoadingPanel.AddDynamic(this, &AInAppHUD::ShowLoadingPanel);

    APIEvents->OnShowSettingPanel.RemoveDynamic(this, &AInAppHUD::ShowSettingPanel);
    APIEvents->OnShowSettingPanel.AddDynamic(this, &AInAppHUD::ShowSettingPanel);

    APIEvents->OnShowNotiticationPanel.RemoveDynamic(this, &AInAppHUD::ShowNotificationPanel);
    APIEvents->OnShowNotiticationPanel.AddDynamic(this, &AInAppHUD::ShowNotificationPanel);

    APIEvents->OnShowHomePanel.RemoveDynamic(this, &AInAppHUD::ShowHomePanel);
    APIEvents->OnShowHomePanel.AddDynamic(this, &AInAppHUD::ShowHomePanel);

    APIEvents->OnShowPanel.RemoveDynamic(this, &AInAppHUD::ShowPanel);
    APIEvents->OnShowPanel.AddDynamic(this, &AInAppHUD::ShowPanel);

    APIEvents->OnHidePanel.RemoveDynamic(this, &AInAppHUD::HidePanel);
    APIEvents->OnHidePanel.AddDynamic(this, &AInAppHUD::HidePanel);

    APIEvents->OnShowErrorNotiticationPanel.RemoveDynamic(this, &AInAppHUD::ShowErrorNotificationPanel);
    APIEvents->OnShowErrorNotiticationPanel.AddDynamic(this, &AInAppHUD::ShowErrorNotificationPanel);

    APIEvents->OnShowGeneratedAvatar.RemoveDynamic(this, &AInAppHUD::ShowAvatarGeneratedPanel);
    APIEvents->OnShowGeneratedAvatar.AddDynamic(this, &AInAppHUD::ShowAvatarGeneratedPanel);

    if (BP_AuthenticationPanel)
    {
        AuthenticationPanel = CreateWidget<UAuthenticationPanel>(GetWorld(), BP_AuthenticationPanel);
        AuthenticationPanel->AddToViewport();
        AuthenticationPanel->SetVisibility(ESlateVisibility::Visible);
    }

    if (BP_LoadingPanel)
    {
        LoadingPanel = CreateWidget<ULoadingPanel>(GetWorld(), BP_LoadingPanel);
        LoadingPanel->AddToViewport(999);
        LoadingPanel->SetVisibility(ESlateVisibility::Hidden);
    }

    if (BP_NotificationPanel)
    {
        NotificationPanel = CreateWidget<UNotificationPanel>(GetWorld(), BP_NotificationPanel);
        NotificationPanel->AddToViewport(999);
        NotificationPanel->SetVisibility(ESlateVisibility::Hidden);
    }

    if (BP_ErrorNotificationPanel)
    {
        ErrorNotificationPanel = CreateWidget<UErrorNotificationPanel>(GetWorld(), BP_ErrorNotificationPanel);
        ErrorNotificationPanel->AddToViewport(1000);
        ErrorNotificationPanel->SetVisibility(ESlateVisibility::Hidden);
    }

    if (BP_HomePanel)
    {
        HomePanel = CreateWidget<UHomePanel>(GetWorld(), BP_HomePanel);
        HomePanel->AddToViewport();
        HomePanel->SetVisibility(ESlateVisibility::Hidden);
    }
    if (BP_StorePanel)
    {
        StorePanel = CreateWidget<UStorePanel>(GetWorld(), BP_StorePanel);
        StorePanel->AddToViewport(10);
        StorePanel->SetVisibility(ESlateVisibility::Hidden);
    }

    if (BP_OnBoardingPanel)
    {
        OnBoardingPanel = CreateWidget<UOnBoardingPanel>(GetWorld(), BP_OnBoardingPanel);
        OnBoardingPanel->AddToViewport();
        OnBoardingPanel->SetVisibility(ESlateVisibility::Hidden);
    }

    if (BP_OnBoardingTwoPanel)
    {
        OnBoardingTwoPanel = CreateWidget<UOnBoardingTwoPanel>(GetWorld(), BP_OnBoardingTwoPanel);
        OnBoardingTwoPanel->AddToViewport();
        OnBoardingTwoPanel->SetVisibility(ESlateVisibility::Hidden);
    }

    if (BP_OnBoardingThreePanel)
    {
        OnBoardingThreePanel = CreateWidget<UOnBoardingThree>(GetWorld(), BP_OnBoardingThreePanel);
        OnBoardingThreePanel->AddToViewport();
        OnBoardingThreePanel->SetVisibility(ESlateVisibility::Hidden);
    }

    if (BP_SettingPanel)
    {
        SettingPanel = CreateWidget<USettingPanel>(GetWorld(), BP_SettingPanel);
        SettingPanel->AddToViewport();
        SettingPanel->SetVisibility(ESlateVisibility::Hidden);
    }
    if (BP_AdsPanel)
    {
        AdsPanel = CreateWidget<UAdsPanel>(GetWorld(), BP_AdsPanel);
        AdsPanel->AddToViewport();
        AdsPanel->SetVisibility(ESlateVisibility::Hidden);
    }
    if (BP_InventoryPanel)
    {
        InventoryPanel = CreateWidget<UInventoryPanel>(GetWorld(), BP_InventoryPanel);
        InventoryPanel->AddToViewport();
        InventoryPanel->SetVisibility(ESlateVisibility::Hidden);
    }
    if (BP_BundlesPanel)
    {
        BundlesPanel = CreateWidget<UBundlesPanel>(GetWorld(), BP_BundlesPanel);
        BundlesPanel->AddToViewport();
        BundlesPanel->SetVisibility(ESlateVisibility::Hidden);
    }
    if (BP_ContainersPanel)
    {
        ContainersPanel = CreateWidget<UContainersPanel>(GetWorld(), BP_ContainersPanel);
        ContainersPanel->AddToViewport();
        ContainersPanel->SetVisibility(ESlateVisibility::Hidden);
    }
    // if(BP_ContainersPanel)
    // {
    //     ContainersPanel = CreateWidget<UContainersPanel>(GetWorld(), BP_ContainersPanel);
    //     ContainersPanel->AddToViewport();
    //     ContainersPanel->SetVisibility(ESlateVisibility::Hidden);
    // }
    if (BP_ContainerDetailPanel)
    {
        ContainerDetailPanel = CreateWidget<UContainerDetailPanel>(GetWorld(), BP_ContainerDetailPanel);
        ContainerDetailPanel->AddToViewport();
        ContainerDetailPanel->SetVisibility(ESlateVisibility::Hidden);
    }

    if (BP_CustomizeFullAvatarPanel)
    {
        CustomizeFullAvatarPanel = CreateWidget<UCustomizeFullAvatarPanel>(GetWorld(), BP_CustomizeFullAvatarPanel);
        CustomizeFullAvatarPanel->AddToViewport();
        CustomizeFullAvatarPanel->SetVisibility(ESlateVisibility::Hidden);
    }

    if (BP_CustomizeHeadAvatarPanel)
    {
        CustomizeHeadAvatarPanel = CreateWidget<UCustomizeHeadAvatarPanel>(GetWorld(), BP_CustomizeHeadAvatarPanel);
        CustomizeHeadAvatarPanel->AddToViewport();
        CustomizeHeadAvatarPanel->SetVisibility(ESlateVisibility::Hidden);
    }

    if (BP_ClipAndExpressionPanel)
    {
        ClipAndExpressionPanel = CreateWidget<UClipAndExpressionPanel>(GetWorld(), BP_ClipAndExpressionPanel);
        ClipAndExpressionPanel->AddToViewport();
        ClipAndExpressionPanel->SetVisibility(ESlateVisibility::Hidden);
    }

    if (WBP_CustomizeBlendshapePanel)
    {
        CustomizeBlendshapePanel = CreateWidget<UCustomizeBlendshapePanel>(GetWorld(), WBP_CustomizeBlendshapePanel);
        CustomizeBlendshapePanel->AddToViewport();
        CustomizeBlendshapePanel->SetVisibility(ESlateVisibility::Hidden);
    }

    if (WBP_ClientSettingPanel)
    {
        ClientSettingPanel = CreateWidget<UClientSettingPanel>(GetWorld(), WBP_ClientSettingPanel);
        ClientSettingPanel->AddToViewport();
        ClientSettingPanel->SetVisibility(ESlateVisibility::Hidden);
    }

    if (WBP_DetailPanel)
    {
        DetailPanel = CreateWidget<UDetailPanel>(GetWorld(), WBP_DetailPanel);
        DetailPanel->AddToViewport();
        DetailPanel->SetVisibility(ESlateVisibility::Hidden);
    }
    if (WBP_BuyItemPanel)
    {
        BuyItemPanel = CreateWidget<UBuyItemPanel>(GetWorld(), WBP_BuyItemPanel);
        BuyItemPanel->AddToViewport();
        BuyItemPanel->SetVisibility(ESlateVisibility::Hidden);
    }
    if (WBP_AvatarGeneratedPopup)
    {
        AvatarGeneratedPopup = CreateWidget<UAvatarGeneratedPopup>(GetWorld(), WBP_AvatarGeneratedPopup);
        AvatarGeneratedPopup->AddToViewport();
        AvatarGeneratedPopup->SetVisibility(ESlateVisibility::Hidden);
    }
}
void AInAppHUD::ShowAvatarGeneratedPanel(FString meshurl, FString imageurl)
{
    AvatarGeneratedPopup->SetVisibility(ESlateVisibility::Visible);
    AvatarGeneratedPopup->LoadAvatarGeneratedPanelData(meshurl, imageurl);
}

void AInAppHUD::ShowPanel(EUIPanels panels, bool Loaddata)
{
    switch (panels)
    {
    case EUIPanels::HOME:
      HomePanel->SetVisibility(ESlateVisibility::Visible);
    
      //HomePanel->CoinHeaderPanel->SetCoins();
        APIEvents->OnSetModelParentDelegate.Broadcast(EModelParent::HOME);
        if (Loaddata)
        {
            HomePanel->LoadHomePanelDetail();
        }
        break;
    case EUIPanels::CURRENCYSTORE:
        StorePanel->SetVisibility(ESlateVisibility::Visible);
        if (Loaddata)
        {
            StorePanel->StorePanelData();
        }
        break;
    case EUIPanels::INVENTORY:
        InventoryPanel->SetVisibility(ESlateVisibility::Visible);
        if (Loaddata)
        {
            InventoryPanel->LoadInventoryData();
        }
        break;
    case EUIPanels::CONTAINERS:
        ContainersPanel->SetVisibility(ESlateVisibility::Visible);
        if (Loaddata)
        {
            ContainersPanel->LoadContainerPanelData();
        }
        break;
    case EUIPanels::REWARDEDADS:
        AdsPanel->SetVisibility(ESlateVisibility::Visible);
        if (Loaddata)
        {
            AdsPanel->LoadRewardedData();
        }
        break;
    case EUIPanels::BUNDLES:
        BundlesPanel->SetVisibility(ESlateVisibility::Visible);
        if (Loaddata)
        {
            UE_LOG(LogTemp, Display, TEXT("On--Loading --->Onboiarding------>"));
            BundlesPanel->LoadBundlePanelData();
        }
        break;
    case EUIPanels::AUTHENTICATION:
        break;
    case EUIPanels::ONBOARDING:
        OnBoardingPanel->SetVisibility(ESlateVisibility::Visible);
        if (Loaddata)
        {
            OnBoardingPanel->LoadOnBoardingPanelDetail();
        }
        break;
    case EUIPanels::ONBOARDING2:
        if (BP_OnBoardingTwoPanel == nullptr)
        {
            UE_LOG(LogTemp, Display, TEXT("ONBOARDING2--NULL--->>>>"));
        }
        else
        {
            OnBoardingTwoPanel->SetVisibility(ESlateVisibility::Visible);
            if (Loaddata)
            {
                OnBoardingTwoPanel->LoadOnBoardingPanelDetail();
            }
        }
        break;
    case EUIPanels::ONBOARDING3:
        if (OnBoardingThreePanel == nullptr)
        {

            UE_LOG(LogTemp, Display, TEXT("ONBOARDING3--NULL--->>>>"));
        }
        else
        {
            OnBoardingThreePanel->SetVisibility(ESlateVisibility::Visible);
            if (Loaddata)
            {
                OnBoardingThreePanel->LoadOnBoardingPanelDetail();
            }
        }
        break;
    case EUIPanels::CUSTOMAVATAR3:
        // OnBoardingThreePanel->SetVisibility(ESlateVisibility::Visible);
        if (Loaddata)
        {
            OnBoardingThreePanel->CreateCustomAvatar();
        }
        break;
    case EUIPanels::CUSTOMIZEFULL:
        CustomizeFullAvatarPanel->SetVisibility(ESlateVisibility::Visible);
        if (Loaddata)
        {
            CustomizeFullAvatarPanel->LoadCustomizeAvatarPanelData();
        }
        break;
    case EUIPanels::CUSTOMIZEHEAD:
        CustomizeHeadAvatarPanel->SetVisibility(ESlateVisibility::Visible);
        if (Loaddata)
        {
            CustomizeHeadAvatarPanel->LoadCustomizeAvatarHeadPanelData();
        }
        break;
    case EUIPanels::EXPRESSIONCLIP:
        ClipAndExpressionPanel->SetVisibility(ESlateVisibility::Visible);
        if (Loaddata)
        {
            ClipAndExpressionPanel->LoadExpressionClipPanelData();
        }
        break;
    case EUIPanels::CUSTOMIZEBLENDSHAPE:
        CustomizeBlendshapePanel->SetVisibility(ESlateVisibility::Visible);
        if (Loaddata)
        {
            UE_LOG(LogTemp, Display, TEXT("LoadBlendDAta----->>>>"));
            CustomizeBlendshapePanel->LoadBlendPanel();
        }
        break;
    case EUIPanels::SETTING:
        SettingPanel->SetVisibility(ESlateVisibility::Visible);
        SettingPanel->LoadSettingPanelData();
        break;
    case EUIPanels::CLIENTSETTING:
        ClientSettingPanel->SetVisibility(ESlateVisibility::Visible);
        ClientSettingPanel->LoadClientSettingPanelData();
        break;
    case EUIPanels::DETAILS:
        DetailPanel->SetVisibility(ESlateVisibility::Visible);
        DetailPanel->LoadDetailPanelData();
        break;
    case EUIPanels::BUYITEMS:

        if (BuyItemPanel == nullptr)
        {
            UE_LOG(LogTemp, Display, TEXT("WBP_BuyItemPanel--NULL--->>>>"));
        }
        else
        {
            UE_LOG(LogTemp, Display, TEXT("WBP_BuyItemPanel----->>>>"));
            BuyItemPanel->SetVisibility(ESlateVisibility::Visible);
            if (Loaddata)
            {
                BuyItemPanel->LoadBuyPanelData();
            }
        }
        break;
    }
}

void AInAppHUD::DrawHUD()
{
}

void AInAppHUD::Tick(float DeltaSeconds)
{
}

void AInAppHUD::ShowOnBoardingPannel()
{
}

void AInAppHUD::ShowLoadingPanel(bool show)
{
    if (show)
    {
        LoadingPanel->SetVisibility(ESlateVisibility::Visible);
    }
    else
    {
        LoadingPanel->SetVisibility(ESlateVisibility::Hidden);
    }
}

void AInAppHUD::ShowNotificationPanel(FString title, FString message)
{
    NotificationPanel->SetVisibility(ESlateVisibility::Visible);
    NotificationPanel->ShowNotification(title, message);
}

void AInAppHUD::ShowErrorNotificationPanel(FString code, FString message)
{
    ErrorNotificationPanel->SetVisibility(ESlateVisibility::Visible);
    ErrorNotificationPanel->ShowErrorNotification(code, message);
}

void AInAppHUD::ShowHomePanel(bool show)
{
    if (show)
    {
        HomePanel->SetVisibility(ESlateVisibility::Visible);
    }
    else
    {
        HomePanel->SetVisibility(ESlateVisibility::Hidden);
    }
}

void AInAppHUD::ShowSettingPanel(bool show)
{
    if (show)
    {
        SettingPanel->SetVisibility(ESlateVisibility::Visible);
    }
    else
    {
        SettingPanel->SetVisibility(ESlateVisibility::Hidden);
    }
}

void AInAppHUD::ShowOnboardingPanel()
{
    OnBoardingPanel->SetVisibility(ESlateVisibility::Visible);
}

void AInAppHUD::HidePanel(EUIPanels panels)
{
    switch (panels)
    {
    case EUIPanels::HOME:
        HomePanel->SetVisibility(ESlateVisibility::Hidden);
        break;

    case EUIPanels::CURRENCYSTORE:
        StorePanel->SetVisibility(ESlateVisibility::Hidden);
        break;

    case EUIPanels::INVENTORY:
        InventoryPanel->SetVisibility(ESlateVisibility::Hidden);
        break;

    case EUIPanels::CONTAINERS:
        ContainersPanel->SetVisibility(ESlateVisibility::Hidden);
        break;

    case EUIPanels::REWARDEDADS:
        AdsPanel->SetVisibility(ESlateVisibility::Hidden);
        break;

    case EUIPanels::BUNDLES:
        BundlesPanel->SetVisibility(ESlateVisibility::Hidden);
        break;
    case EUIPanels::AUTHENTICATION:
        break;
    case EUIPanels::ONBOARDING:
        OnBoardingPanel->SetVisibility(ESlateVisibility::Hidden);
        break;
    case EUIPanels::ONBOARDING2:
        OnBoardingPanel->SetVisibility(ESlateVisibility::Hidden);
        break;
    case EUIPanels::ONBOARDING3:
        OnBoardingPanel->SetVisibility(ESlateVisibility::Hidden);
        break;
    case EUIPanels::CUSTOMIZEFULL:
        CustomizeFullAvatarPanel->SetVisibility(ESlateVisibility::Hidden);

        break;
    case EUIPanels::CUSTOMIZEHEAD:
        CustomizeHeadAvatarPanel->SetVisibility(ESlateVisibility::Hidden);

        break;
    case EUIPanels::EXPRESSIONCLIP:
        ClipAndExpressionPanel->SetVisibility(ESlateVisibility::Hidden);

        break;
    case EUIPanels::CUSTOMIZEBLENDSHAPE:
        CustomizeBlendshapePanel->SetVisibility(ESlateVisibility::Hidden);

        break;
    case EUIPanels::SETTING:
        SettingPanel->SetVisibility(ESlateVisibility::Hidden);

        break;
    case EUIPanels::CLIENTSETTING:
        ClientSettingPanel->SetVisibility(ESlateVisibility::Hidden);
        break;
    case EUIPanels::DETAILS:
        DetailPanel->SetVisibility(ESlateVisibility::Hidden);
        break;
    case EUIPanels::BUYITEMS:

        BuyItemPanel->SetVisibility(ESlateVisibility::Hidden);

        break;
    }
}
