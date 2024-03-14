// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomizeAvatarLoader.h"

ACustomizeAvatarLoader* ACustomizeAvatarLoader::Instance = nullptr;

ACustomizeAvatarLoader::ACustomizeAvatarLoader()
{
    Instance = this;

    // OnLoadNetworkModelDelegate.BindUObject(this, &ACustomizeAvatarLoader::EventLoadNetworkModel);
    // LoadNetworkModelDelegate.BindUFunction(this, "EventLoadNetworkModel");
    // APIEvents->OnLoadNetworkModelDelegate.BindUFunction(this, FName("EventLoadNetworkModel"));


    PrimaryActorTick.bCanEverTick = true;
}

ACustomizeAvatarLoader *ACustomizeAvatarLoader::GetInstance()
{
    if (!Instance)
    {
        // Create a new instance if it doesn't exist
        Instance = NewObject<ACustomizeAvatarLoader>(GetTransientPackage(), ACustomizeAvatarLoader::StaticClass());
        Instance->AddToRoot(); // Ensure it's not garbage collected
    }
    return Instance;
}

void ACustomizeAvatarLoader::BeginPlay()
{
   	Super::BeginPlay();

    // APIEvents->OnLoadNetworkModelDelegate.RemoveDynamic(this,  &ACustomizeAvatarLoader::EventLoadNetworkModel);
    // APIEvents->OnLoadNetworkModelDelegate.AddDynamic(this, &ACustomizeAvatarLoader::EventLoadNetworkModel);
    LoadNetworkModelDelegate.RemoveDynamic(this, &ACustomizeAvatarLoader::EventLoadNetworkModel);
    LoadNetworkModelDelegate.AddDynamic(this, &ACustomizeAvatarLoader::EventLoadNetworkModel);
    // LoadNetworkModelDelegate.BindUFunction(this, "EventLoadNetworkModel");
    LoadStartData();
}

void ACustomizeAvatarLoader::LoadDefaultModel()
{
    // LoadHeadModel();
    // LoadCustomizeModel();
    //Create this functiom in avatarloaderBase..
    // LoadDefaultModel();
    // LoadDefaultModels();
  
}

void ACustomizeAvatarLoader::DownloadModelfromData(FEconomyItems itemdata)
{
    LoadNetworkModel(itemdata);
}

void ACustomizeAvatarLoader::EventLoadNetworkModel(bool sender, FEconomyItems e)
{
   if(sender)
   {
    LoadNetworkModel(e);
   }
   else
   {
     LoadNetworkModel(e);
   }
   
}

