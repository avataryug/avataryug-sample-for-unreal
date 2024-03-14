// Fill out your copyright notice in the Description page of Project Settings.


#include "UIHandler.h"

AUIHandler::AUIHandler()
{

}

void AUIHandler::BeginPlay()
{
    Super::BeginPlay();

    if (WBP_AvatarLoaderUI)
    {
        AvatarLoaderUI = CreateWidget<UAvatarLoaderUI>(GetWorld(), WBP_AvatarLoaderUI);
        AvatarLoaderUI->AddToViewport();
    }

}

void AUIHandler::DrawHUD()
{

}