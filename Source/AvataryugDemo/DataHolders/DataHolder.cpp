// Fill out your copyright notice in the Description page of Project Settings.

#include "DataHolder.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
ADataHolder::ADataHolder()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADataHolder::BeginPlay()
{
    Super::BeginPlay();

    OnSyncAvatarsResponse.BindUFunction(this, "OnSyncAvatarResponseReceive");
    OnApiExceptionSync.BindUFunction(this, "OnSyncAvatarError");

    void OnSyncAvatarResponseReceive(FString resp);
    if (APIEvents == nullptr)
    {
        AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AAPIEvents::StaticClass());
        APIEvents = Cast<AAPIEvents>(FoundActor);
        if (APIEvents == nullptr)
        {
            APIEvents = GetWorld()->SpawnActor<AAPIEvents>();
        }
    }
      if (CurrentAvatarChanges == nullptr)
  {
    AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), ACurrentAvatarChanges::StaticClass());
    CurrentAvatarChanges = Cast<ACurrentAvatarChanges>(FoundActor);
    if (CurrentAvatarChanges == nullptr)
    {
      CurrentAvatarChanges = GetWorld()->SpawnActor<ACurrentAvatarChanges>();
    }
  }

}

void ADataHolder::AddCurrenBodyPart(FEconomyItems item)
{
    APIEvents->ShowLoading();
    int index = -1;
    for (int i = 0; i < currentSelectedBodyParts.Num(); i++)
    {
        if (currentSelectedBodyParts[i].itemCategory == item.itemCategory)
        {
            index = i;
            break;
        }
    }
    if (index > -1)
    {
        currentSelectedBodyParts.RemoveAt(index);
    }
    currentSelectedBodyParts.Add(item);
    OnItemAddedRemoved();
}

void ADataHolder::RemovepropItem(FEconomyItems item)
{
    int index = -1;
    for (int i = 0; i < currentSelectedBodyParts.Num(); i++)
    {
        if (currentSelectedBodyParts[i].iD == item.iD)
        {
            index = i;
            break;
        }
    }
    if (index > -1)
    {
        currentSelectedBodyParts.RemoveAt(index);
    }
    OnItemAddedRemoved();
}

void ADataHolder::RemovepropItemWithCat(FString category)
{
    int index = -1;
    for (int i = 0; i < currentSelectedBodyParts.Num(); i++)
    {
        if (currentSelectedBodyParts[i].itemCategory == category)
        {
            index = i;
            break;
        }
    }
    if (index > -1)
    {
        currentSelectedBodyParts.RemoveAt(index);
    }
    OnItemAddedRemoved();
}

void ADataHolder::SynAvatars()
{
    FSyncAvatarsRequest request;
    UDefaultHandler::SyncAvatar(request, OnSyncAvatarsResponse, OnApiExceptionSync);
}

void ADataHolder::OnSyncAvatarResponseReceive(FString resp)
{
}

void ADataHolder::OnSyncAvatarError(FApiException result)
{
}

void ADataHolder::OnItemAddedRemoved()
{
    APIEvents->UpdateUiAfterItemSelect();
    CurrentAvatarChanges->changedProps.props.Empty();
    for (int i = 0; i < currentSelectedBodyParts.Num(); i++)
    {
        FProp prop;
        prop.CoreBucket = currentSelectedBodyParts[i].coreBucket;
        prop.ID = currentSelectedBodyParts[i].iD;
        CurrentAvatarChanges->changedProps.props.Add(prop);
    }
}