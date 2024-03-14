// Fill out your copyright notice in the Description page of Project Settings.


#include "LoadingPanel.h"

void ULoadingPanel::NativeConstruct()
{
    Super::NativeConstruct();

    LoadingButton->OnClicked.RemoveDynamic(this, &ULoadingPanel::OnLoadingClick);
    LoadingButton->OnClicked.AddDynamic(this, &ULoadingPanel::OnLoadingClick);
}

void ULoadingPanel::OnLoadingClick()
{
    UE_LOG(LogTemp, Display, TEXT("ON OnLoadingClick"));
}