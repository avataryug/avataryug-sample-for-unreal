// Fill out your copyright notice in the Description page of Project Settings.


#include "Utilitys.h"

FString UUtilitys::GetPlatform()
{

    EPlatform Platform = EPlatform::Android;
    FString PlatformString;
    #if PLATFORM_ANDROID
        PlatformString =  UEnum::GetValueAsString(EPlatform::Android);
    #endif

    #if PLATFORM_IOS
        PlatformString = UEnum::GetValueAsString(EPlatform::iOS);
    #endif

    switch (Platform)
    {
    case EPlatform::Android:
        PlatformString = "Android";
        break;
    case EPlatform::iOS:
        PlatformString = "IOS";
        break;
    case EPlatform::Web:
        PlatformString = "Web";
        break;
    case EPlatform::Steam:
        PlatformString = "Steam";
        break;
    case EPlatform::Meta:
        PlatformString = "Meta";
        break;
    case EPlatform::Xbox:
        PlatformString = "Xbox";
        break;
    case EPlatform::Playstation:
        PlatformString = "Playstation";
        break;
    case EPlatform::Custom:
        PlatformString = "Custom";
        break;
    }
    return PlatformString;
}