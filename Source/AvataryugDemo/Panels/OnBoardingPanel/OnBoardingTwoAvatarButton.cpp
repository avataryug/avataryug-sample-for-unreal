// Fill out your copyright notice in the Description page of Project Settings.
#include "OnBoardingTwoAvatarButton.h"
#include "CommonModels.h"

void UOnBoardingTwoAvatarButton::NativeConstruct()
{
    Super::NativeConstruct();
    OnReceiveTexture.BindUFunction(this, "OnLoadImage");
}
void UOnBoardingTwoAvatarButton::SetButtonData(FGetAvatarPresetsResultDataInner item)
{
    //  = image;

  //  UE_LOG(LogTemp, Display, TEXT("UpdateOnBoardThreeData---->>%s"), *item.ImageArtifacts);
    FString artifactString = "{";
    artifactString.Append("\"ImageArtifacts\":");
    artifactString.Append(item.ImageArtifacts);
    artifactString.Append("}");
    FAvatarPresetImageArtifacts artifactlist;
    FJsonObjectConverter::JsonObjectStringToUStruct(artifactString, &artifactlist);
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
                    // Now, 'Url' contains the URL string from the first item in the array.
                    // You can use it as needed.
                    // For example, you can print it to the log:
                 //   UE_LOG(LogTemp, Warning, TEXT("First ONBAORDING THREE URL: %s"), *Url);
                    ULoadTextureFromURL::LoadTexture(Url, OnReceiveTexture);
                    //   ULoadTextureFromURL::LoadTexture(artifactlist.artifacts[0].url,ReceiveEyebrowTexture);
                }
            }
        }
    }
    else
    {
        // Handle JSON parsing error if needed
    }
}

void UOnBoardingTwoAvatarButton::OnLoadImage(UTexture2D *textures)
{
    AvatarImage->SetBrushFromTexture(textures, false);
}