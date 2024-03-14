// Fill out your copyright notice in the Description page of Project Settings.

#include "OnBoardingThreeAvatarButton.h"

void UOnBoardingThreeAvatarButton::NativeConstruct()
{
    Super::NativeConstruct();

    if (AllGraphicsHolder == nullptr)
    {
        AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AAllGraphicsHolder::StaticClass());
        AllGraphicsHolder = Cast<AAllGraphicsHolder>(FoundActor);
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

    ItemButton->OnClicked.RemoveDynamic(this, &UOnBoardingThreeAvatarButton::OnClickButton);
    ItemButton->OnClicked.AddDynamic(
        this, &UOnBoardingThreeAvatarButton::OnClickButton);

    SelectedImage->SetVisibility(ESlateVisibility::Hidden);


     
      
    
}
void UOnBoardingThreeAvatarButton:: OnSelectAvatarPreset(FGetAvatarPresetsResultDataInner data) 
{
  SelectedImage->SetVisibility(ESlateVisibility::Hidden);
  
}
void UOnBoardingThreeAvatarButton::OnClickButton()
{
    if (onboardingThreeItem.DisplayName == "Custom")
    {
        APIEvents->ShowPanel(EUIPanels::CUSTOMAVATAR3, true);
    }
    else
    {
      OnClickButtons(onboardingThreeItem);
          
    }
OnBoardingThreeRe->OnSelectAvatarPreset.Broadcast(onboardingThreeItem);
    SelectedImage->SetVisibility(ESlateVisibility::Visible);
}

void UOnBoardingThreeAvatarButton::SetOnBoardThreeButton(
    UOnBoardingThree *OnBoardingThreeRef, FGetAvatarPresetsResultDataInner item,
    TFunction<void(FGetAvatarPresetsResultDataInner)> OnClickButton) {

  OnBoardingThreeRe = OnBoardingThreeRef;
     OnBoardingThreeRe->OnSelectAvatarPreset.RemoveDynamic(this, &UOnBoardingThreeAvatarButton::OnSelectAvatarPreset);
      OnBoardingThreeRe->OnSelectAvatarPreset.AddDynamic(this, &UOnBoardingThreeAvatarButton::OnSelectAvatarPreset);
    OnClickButtons = OnClickButton;
    LoadingPanel->SetVisibility(ESlateVisibility::Visible);
    onboardingThreeItem = item;
    Id = onboardingThreeItem.ID;
    if (item.DisplayName == "Custom")
    {
        LoadingPanel->SetVisibility(ESlateVisibility::Hidden);
    }
    else
    {
        UpdateOnBoardThreeButtonData();
    }
}

void UOnBoardingThreeAvatarButton::UpdateOnBoardThreeButtonData()
{
    FString artifactString = "{";
    artifactString.Append("\"ImageArtifacts\":");
    artifactString.Append(onboardingThreeItem.ImageArtifacts);
    artifactString.Append("}");
    FAvatarPresetImageArtifacts artifactlist;
    FJsonObjectConverter::JsonObjectStringToUStruct(artifactString, &artifactlist,0,0);
    TSharedPtr<FJsonObject> JsonObject;
    TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(artifactString);
    if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
    {
        if (JsonObject->HasField(TEXT("ImageArtifacts")))
        {
            TArray<TSharedPtr<FJsonValue>> ArtifactArray = JsonObject->GetArrayField(TEXT("ImageArtifacts"));
            if (ArtifactArray.Num() > 0)
            {
                TSharedPtr<FJsonObject> FirstArtifactObject = ArtifactArray[0]->AsObject();
                if (FirstArtifactObject.IsValid() && FirstArtifactObject->HasField(TEXT("thumbnail_url")))
                {
                    FString Url = FirstArtifactObject->GetStringField(TEXT("thumbnail_url"));
                    ULoadTextureFromURL::LoadByte(Url, [this](UTexture2D *texture)
                                                  {
                         ItemImage->SetBrushFromTexture(texture, false);
                         LoadingPanel->SetVisibility(ESlateVisibility::Hidden); });
                }
            }
        }
    }
}
