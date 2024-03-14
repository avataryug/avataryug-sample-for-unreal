// Fill out your copyright notice in the Description page of Project Settings.

#include "APIEvents.h"
#include "GameEnums.h"
#include "GameFramework/GameUserSettings.h"

// Sets default values
AAPIEvents::AAPIEvents()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAPIEvents::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAPIEvents::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAPIEvents::ShowLoading()
{
	OnShowLoadingPanel.Broadcast(true);
}

void AAPIEvents::UpdatesUI()
{
	OnUpdateUI.Broadcast(true);
}
void AAPIEvents::UpdatesHeadUI()
{
	OnUpdateHeadUI.Broadcast(true);
}

void AAPIEvents::UpdatesExpUI()
{
	OnUpdatexpPanelUI.Broadcast(true);
}

void AAPIEvents::UpdatesClipUI()
{
	OnUpdateClipPanelUI.Broadcast(true);
}

void AAPIEvents::UpdatesBuyButtonUI()
{
	OnUpdateBuyButtonUI.Broadcast(true);
}
void AAPIEvents::HideLoading()
{
	OnShowLoadingPanel.Broadcast(false);
}

void AAPIEvents::ShowSettingPanel()
{
	OnShowSettingPanel.Broadcast(true);
}

void AAPIEvents::HideSettingPanel()
{
	OnShowSettingPanel.Broadcast(false);
}

void AAPIEvents::ShowHomePanel()
{
	OnShowHomePanel.Broadcast(true);
}
void AAPIEvents::HideHomePanel()
{
	OnShowHomePanel.Broadcast(false);
}

void AAPIEvents::ShowNotification(FString title, FString message)
{
	OnShowNotiticationPanel.Broadcast(title, message);
}

void AAPIEvents::ShowErrorNotification(FString code, FString message)
{
	OnShowErrorNotiticationPanel.Broadcast(code, message);
}

void AAPIEvents::LoadNetworkModelDelegate(bool sender, FEconomyItems e)
{
	OnLoadNetworkModelDelegate.Broadcast(sender, e);
}

void AAPIEvents::SetModelparent(EModelParent panels)
{
	OnSetModelParentDelegate.Broadcast(panels);
}

void AAPIEvents::ShowPanel(EUIPanels panels, bool Loaddata)
{
	OnShowPanel.Broadcast(panels, Loaddata);
}

void AAPIEvents::ShowInventoryPanel(bool LoadData)
{
}

void AAPIEvents::HidePanel(EUIPanels panels)
{
	OnHidePanel.Broadcast(panels);
}

void AAPIEvents::OnPropButtonClick(bool isSelect)
{
	OnPropClick.Broadcast(isSelect);
}
void AAPIEvents::OnItemClick()
{
	ShowLoading();
	OnUpdateUI.Broadcast(true);
	OnUpdateHeadUI.Broadcast(true);
	OnUpdatexpPanelUI.Broadcast(true);
}
void AAPIEvents::SetResolution(bool isLandscape)
{
	OnScreenOrientation.Broadcast(isLandscape);
	isRotated = isLandscape;
	if (isLandscape)
	{
		UGameUserSettings *GameUserSettings = UGameUserSettings::GetGameUserSettings();
		if (GameUserSettings != nullptr)
		{
			GameUserSettings->SetScreenResolution(FIntPoint(1280, 720));

			// Set the fullscreen mode
			// GameUserSettings->SetFullscreenMode(Fullscreen ? EWindowMode::Fullscreen : EWindowMode::Windowed);
			GameUserSettings->SetFullscreenMode(EWindowMode::Windowed);
			// Apply the changes
			GameUserSettings->ApplySettings(false);
		}
	}
	else
	{

		UGameUserSettings *GameUserSettings = UGameUserSettings::GetGameUserSettings();
		if (GameUserSettings != nullptr)
		{
			GameUserSettings->SetScreenResolution(FIntPoint(720, 1280));

			// Set the fullscreen mode
			GameUserSettings->SetFullscreenMode(EWindowMode::Windowed);

			// Apply the changes
			GameUserSettings->ApplySettings(false);
		}
	}
}
void AAPIEvents::UpdateUiAfterItemSelect()
{
	OnUpdateUiAfterItemSelect.Broadcast();
}

void AAPIEvents::UpdateUiAfterPurchase()
{
	OnUpdateUiAfterPurchase.Broadcast();
}
void AAPIEvents:: ShowGeneratedAvatar(FString meshurl, FString imageurl )
{
		OnShowGeneratedAvatar.Broadcast(meshurl,imageurl);
}
