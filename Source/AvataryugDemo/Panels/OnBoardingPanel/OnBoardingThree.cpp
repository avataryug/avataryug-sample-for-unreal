// Fill out your copyright notice in the Description page of Project Settings.
#include "OnBoardingThree.h"
#include "AvatarPresetsAPI/AvatarPresetsHandler.h"
#include "OnBoardingThreeButtonGridPanel.h"

void UOnBoardingThree::NativeConstruct()
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
    if (UserInventoryHolder == nullptr)
    {
        AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AUserInventoryHolder::StaticClass());
        UserInventoryHolder = Cast<AUserInventoryHolder>(FoundActor);
        if (UserInventoryHolder == nullptr)
        {
            UserInventoryHolder = GetWorld()->SpawnActor<AUserInventoryHolder>();
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
    if (APIEvents == nullptr)
    {
        AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AAPIEvents::StaticClass());
        APIEvents = Cast<AAPIEvents>(FoundActor);
        if (APIEvents == nullptr)
        {
            APIEvents = GetWorld()->SpawnActor<AAPIEvents>();
        }
    }
    if (CurrentAvatarChangesHolder == nullptr)
    {
        AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), ACurrentAvatarChanges::StaticClass());
        CurrentAvatarChangesHolder = Cast<ACurrentAvatarChanges>(FoundActor);
        // CurrentAvatarChangesHolder->SetActorLabel(FString("CurrentAvatarChangesHolder"));
    }
    if (AvatarHandler == nullptr)
    {
        AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AAvatarHandler::StaticClass());
        AvatarHandler = Cast<AAvatarHandler>(FoundActor);
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
    LetsBeginWithAvatarButton->OnClicked.RemoveDynamic(this, &UOnBoardingThree::LoadArtifact);
    LetsBeginWithAvatarButton->OnClicked.AddDynamic(this, &UOnBoardingThree::LoadArtifact);

    SelectGenderCloseButton->OnClicked.RemoveDynamic(this, &UOnBoardingThree::CloseGenderPanel);
    SelectGenderCloseButton->OnClicked.AddDynamic(this, &UOnBoardingThree::CloseGenderPanel);

    MaleButton->OnClicked.RemoveDynamic(this, &UOnBoardingThree::MaleGenderSelected);
    MaleButton->OnClicked.AddDynamic(this, &UOnBoardingThree::MaleGenderSelected);

    FemaleButton->OnClicked.RemoveDynamic(this, &UOnBoardingThree::FemaleGenderSelected);
    FemaleButton->OnClicked.AddDynamic(this, &UOnBoardingThree::FemaleGenderSelected);

    GetAvatarPresetsResult.BindUFunction(this, "OnGetAvatarPresetsResult");
    GetAvatarPresetsError.BindUFunction(this, "OnGetAvatarPresetsError");
}

void UOnBoardingThree::LoadArtifact()
{
    APIEvents->isCustomize = false;
    APIEvents->isMale = false;
    FString artifactString = "{";
    artifactString.Append("\"artifacts\":");
    artifactString.Append(SelectedPreset.MeshArtifacts);
    artifactString.Append("}");
    FAvatarPresetArtifacts artifactlist;
    FJsonObjectConverter::JsonObjectStringToUStruct(artifactString, &artifactlist,0,0);
    if (artifactlist.artifacts.Num() > 0)
    {
        UserDetailHolder->tempmeshurl = artifactlist.artifacts[0].url;
    }
    LetsBeginWithAvatar();
}

void UOnBoardingThree::LetsBeginWithAvatar()
{
    APIEvents->ShowLoading();
    FClipExpressionData clipExpressionData;
    clipExpressionData.Style.ClipID = "standard_clip";
    clipExpressionData.Style.ExpressionID = "";
    UserDetailHolder->UserDetails.Gender = SelectedPreset.Gender == 2 ? EGender::FEMALE : EGender::MALE;
    if (UserDetailHolder->UserDetails.Gender == EGender::MALE)
    {
        clipExpressionData.gender = 0;
    }
    else if (UserDetailHolder->UserDetails.Gender == EGender::FEMALE)
    {
        clipExpressionData.gender = 1;
    }
    FString metaData;
    FJsonObjectConverter::UStructToJsonObjectString(clipExpressionData, metaData);

    FAvatarData avatarData;
    avatarData.AgeRange = SelectedPreset.AgeRange;
    avatarData.Race = SelectedPreset.Race;
    avatarData.Gender = UserDetailHolder->UserDetails.Gender == EGender::FEMALE ? 1 : 0;
    avatarData.CustomMetaData = SelectedPreset.CustomMetaData;

    FPropColors propcolors;
    FJsonObjectConverter::JsonObjectStringToUStruct(SelectedPreset.Color, &propcolors,0,0);
    avatarData.ColorMeta = propcolors;

    FProps props;
    FString propString = "{";
    propString.Append("\"props\":");
    propString.Append(SelectedPreset.Props);
    propString.Append("}");
    FJsonObjectConverter::JsonObjectStringToUStruct(propString, &props,0,0);
    avatarData.BucketData = props.props;

    FBlendShapes blendshapes;
    FString blendString = "{";
    blendString.Append("\"blendShapes\":");
    blendString.Append(SelectedPreset.BlendshapeKeys);
    blendString.Append("}");
    FJsonObjectConverter::JsonObjectStringToUStruct(blendString, &blendshapes,0,0);

    for (int i = 0; i < blendshapes.blendShapes.Num(); i++)
    {
        FBlendShapeValue blendshape;
        blendshape.value = blendshapes.blendShapes[i].value;
        blendshape.shapekeys = blendshapes.blendShapes[i].shapekeys;
        avatarData.Blendshapes.Add(blendshape);
    }

    avatarData.MetaData = metaData;

    FGrantAvatarPresetItemsToUserRequest request;

    for (int i = 0; i < props.props.Num(); i++)
    {
        FGrantAvatarPresetItemsToUserRequestItemIDsInner item;
        item.ItemID = props.props[i].ID;
        request.ItemIDs.Add(item);
    }
    FJsonObjectConverter::UStructToJsonObjectString(avatarData, avatarDataStr);

    UAvatarPresetsHandler::GrantAvatarPresetItemsToUser(
        request, [this](FGrantAvatarPresetItemsToUserResponse result)
        {
        FGrantAvatarToUserRequest grantAvatarRequest;
        grantAvatarRequest.AvatarData = avatarDataStr;
        UAvatarPresetsHandler::GrantAvatarPresetToUser(
            grantAvatarRequest, [this](FGrantAvatarToUserResponse gresult)
            {
                    CommonFunctionHolder->UpdateDefaultAvatarID(gresult.Data.AvatarID, [this,gresult]
                                                                { 
                                                                    UserDetailHolder->UserDetails.DefaultAvatarID = gresult.Data.AvatarID;
                                                                    CommonFunctionHolder
                                                                        ->GetCommonUserInventory(
                                                                            [this] {
                                                                              CommonFunctionHolder
                                                                                  ->GetUserAllAvatars(
                                                                                      [this]() {
                                                                                        this->SetVisibility(
                                                                                            ESlateVisibility::
                                                                                                Hidden);
                                                                                        DataHolder->cameFromFirstAvatar =true;
     if (AvatarHandler->TypeOfMontization ==
                                        EMonitizeType::Monitize) {
               APIEvents->ShowPanel(EUIPanels::HOME, true);
                                } else {
                                       if(AvatarHandler->customizeAvatarLoader->spawnedHeadActor == nullptr)
    {
                                         AvatarHandler->customizeAvatarLoader
                                             ->LoadHeadModel([this] {
                                               LoadCurrentAvatarData([this] {
                                                  DataHolder->resetToCurrentModel =true;
                                                   APIEvents->ShowPanel(EUIPanels::CUSTOMIZEFULL, true);
          });
      });
    }
    else
    {
      LoadCurrentAvatarData([this] {
         DataHolder->resetToCurrentModel =true;
          APIEvents->ShowPanel(EUIPanels::CUSTOMIZEFULL, true);
          });
    }
                                  }}); }); }); },
            [this](FApiException errorz)
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

void UOnBoardingThree::LoadOnBoardingPanelDetail()
{
    APIEvents->ShowLoading();
    UAvatarPresetsHandler::GetAvatarPresets(3, 1, GetAvatarPresetsResult, GetAvatarPresetsError);
}

void UOnBoardingThree::CreateCustomAvatar()
{
    DataHolder->isCustomizeAvatar = true;
    SelectGenderPanel->SetVisibility(ESlateVisibility::Visible);
}

void UOnBoardingThree::MaleGenderSelected()
{
    OnClickMaleFemaleButton(EGender::MALE);
}
void UOnBoardingThree::FemaleGenderSelected()
{
    OnClickMaleFemaleButton(EGender::FEMALE);
}

void UOnBoardingThree::CloseGenderPanel()
{
    SelectGenderPanel->SetVisibility(ESlateVisibility::Hidden);
}

void UOnBoardingThree::OnClickMaleFemaleButton(EGender gender)
{
    CurrentAvatarChangesHolder->changePropColors.EyebrowColor = AvatarHandler->CustomizeDefaultAvatarLoader->DefaultEyebrowColor;
    CurrentAvatarChangesHolder->changePropColors.HairColor = AvatarHandler->CustomizeDefaultAvatarLoader->DefaultHairColor;
    CurrentAvatarChangesHolder->changePropColors.FacialHairColor = AvatarHandler->CustomizeDefaultAvatarLoader->DefaultFacialHairColor;
    if (gender == EGender::FEMALE)
    {
        CurrentAvatarChangesHolder->changePropColors.LipColor = AvatarHandler->CustomizeDefaultAvatarLoader->DefaultLipColor;
        APIEvents->isMale = false;
    }
    if (gender == EGender::MALE)
    {
        CurrentAvatarChangesHolder->changePropColors.LipColor = AvatarHandler->CustomizeDefaultAvatarLoader->DefaultMaleLipColor;
        APIEvents->isMale = true;
    }

    TArray<AActor *> AttachedChildActors;
    AvatarHandler->SpawnedOnBoardingParent->GetAttachedActors(AttachedChildActors);
    for (AActor *AttachedActor : AttachedChildActors)
    {
        if (AttachedActor)
        {
            AttachedActor->Destroy();
        }
    }
    APIEvents->isCustomize = true;
    UserDetailHolder->UserDetails.Gender = gender;

    APIEvents->OnChangeCamera.Broadcast(CameraPanels::CustomizeAvatar_Head);
    AvatarHandler->customizeAvatarLoader->ResetData();
    if (AvatarHandler->customizeAvatarLoader->spawnedHeadActor == nullptr)
    {
        AvatarHandler->customizeAvatarLoader->LoadHeadModel([this]
                                                            {
            APIEvents->HideLoading();
            APIEvents->ShowLoading();
            APIEvents->HideLoading();
            ResetData();
            AvatarHandler->customizeAvatarLoader->ResetToDefault([this]
                                                                 {
                                                                     AvatarHandler->ForCustomizeAvatar = AvatarHandler->customizeAvatarLoader;
                                                                     SelectGenderPanel->SetVisibility(ESlateVisibility::Hidden);
                                                                     APIEvents->ShowPanel(EUIPanels::CUSTOMIZEHEAD, true);
                                                                     // AvatarHandler->CustomizeDefaultAvatarLoader->LoadDefaultModels();
                                                                 }); });
    }
    else
    {
        APIEvents->ShowLoading();
        APIEvents->HideLoading();
        ResetData();
        AvatarHandler->customizeAvatarLoader->ResetToDefault([this]
                                                             {
                                                                 // if(AvatarHandler->CustomizeDefaultAvatarLoader->count >= 4)
                                                                 // {
                                                                 //     APIEvents->OnResetToDefault.ExecuteIfBound([this]{
                                                                 //     UE_LOG(LogTemp, Display, TEXT("On--OnResetToDefault--->EXECUTED---spawnedHeadActor--PRESENT->"));
                                                                 //     });
                                                                 // }
                                                                 AvatarHandler->ForCustomizeAvatar = AvatarHandler->customizeAvatarLoader;
                                                                 SelectGenderPanel->SetVisibility(ESlateVisibility::Hidden);
                                                                 APIEvents->ShowPanel(EUIPanels::CUSTOMIZEHEAD, true); });
        // AvatarHandler->ForCustomizeAvatar->ResetToDefault([this]
        //                                 { UE_LOG(LogTemp, Display, TEXT("On--OnResetToDefault--->EXECUTED---ForCustomizeAvatar--PRESENT->")); });
    }
    this->SetVisibility(ESlateVisibility::Hidden);
}

void UOnBoardingThree::OnGetAvatarPresetsResult(FGetAvatarPresetsResult result)
{
    ArtifactList.Empty();
    for (int i = 0; i < result.Data.Num(); i++)
    {
        ArtifactList.Add(result.Data[i]);
    }
    ShowPropItems();
}
void UOnBoardingThree::OnGetAvatarPresetsError(FApiException error)
{
}
void UOnBoardingThree::ShowPropItems()
{
    if (OnBoardingThreeListView)
    {
        OnBoardingThreeListView->ClearListItems();
    }
    FGetAvatarPresetsResultDataInner newItem;
    newItem.DisplayName = "Custom";
    ArtifactList.Insert(newItem, 0);
    float floatValue = ArtifactList.Num();
    float contaientGridCount = floatValue / 3;
    int myCeilInt = FMath::CeilToInt(contaientGridCount);
    for (int i = 0; i < myCeilInt; i++)
    {
        UListNewItemData *item = NewObject<UListNewItemData>();
        item->StartIndex = 3 * i;
        item->TotalCount = ArtifactList.Num();
        item->presetLists = ArtifactList;
        item->OnBoardingThree = this;
        item->OnClickButton = [this](FGetAvatarPresetsResultDataInner item)
        {
            SelectedPreset = item;
        };
        OnBoardingThreeListView->AddItem(item);
    }
    APIEvents->HideLoading();
}

void UOnBoardingThree::ResetData()
{
    CurrentAvatarChangesHolder->changedProps = FProps();
    for (int i = 0; i < CurrentAvatarChangesHolder->currentProps.props.Num(); i++)
    {
        FProp tempItem = CurrentAvatarChangesHolder->currentProps.props[i];
        CurrentAvatarChangesHolder->changedProps.props.Add(tempItem);
    }
    CurrentAvatarChangesHolder->changeBlendShapes = TArray<FBlendShapeValue>();
    for (int i = 0; i < CurrentAvatarChangesHolder->currentBlendShapes.Num(); i++)
    {
        CurrentAvatarChangesHolder->changeBlendShapes.Add(CurrentAvatarChangesHolder->currentBlendShapes[i]);
    }
    FString col = CurrentAvatarChangesHolder->currentpropColors.HairColor;
    CurrentAvatarChangesHolder->changePropColors.HairColor = col;

    col = CurrentAvatarChangesHolder->currentpropColors.FacialHairColor;
    CurrentAvatarChangesHolder->changePropColors.FacialHairColor = col;

    col = CurrentAvatarChangesHolder->currentpropColors.LipColor;
    CurrentAvatarChangesHolder->changePropColors.LipColor = col;

    col = CurrentAvatarChangesHolder->currentpropColors.EyebrowColor = col;
    CurrentAvatarChangesHolder->changePropColors.EyebrowColor = col;

    AvatarHandler->customizeAvatarLoader->ClearCurrent();
}
void UOnBoardingThree::LoadCurrentAvatarData(TFunction<void()> oncomplete) 
{
  FString avatari = UserDetailHolder->UserDetails.currentUserSelectedAvatar.AvatarID;
  UAvatarPresetsHandler::GetUserAvatarAllData(avatari,"Android", [this,oncomplete](FGetUserAvatarAllDataResponse result) 
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