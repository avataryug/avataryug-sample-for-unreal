// Fill out your copyright notice in the Description page of Project Settings.

#include "AvatarGeneratedPopup.h"
#include "../../Utilitys/LoadTextureFromURL.h"
void UAvatarGeneratedPopup::NativeConstruct()
{
    Super::NativeConstruct();

    if (APIEvents == nullptr)
    {
        AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AAPIEvents::StaticClass());
        APIEvents = Cast<AAPIEvents>(FoundActor);
        if (APIEvents == nullptr)
        {
            APIEvents = GetWorld()->SpawnActor<AAPIEvents>();
        }
    }

    CopyMeshurlButton->OnClicked.RemoveDynamic(this, &UAvatarGeneratedPopup::CopyMeshUrl);
    CopyMeshurlButton->OnClicked.AddDynamic(this, &UAvatarGeneratedPopup::CopyMeshUrl);

    CopyImageurlButton->OnClicked.RemoveDynamic(this, &UAvatarGeneratedPopup::CopyImageUrl);
    CopyImageurlButton->OnClicked.AddDynamic(this, &UAvatarGeneratedPopup::CopyImageUrl);

    OkButton->OnClicked.RemoveDynamic(this, &UAvatarGeneratedPopup::ClosePopup);
    OkButton->OnClicked.AddDynamic(this, &UAvatarGeneratedPopup::ClosePopup);
}

void UAvatarGeneratedPopup::LoadAvatarGeneratedPanelData(FString meshurl, FString imageurl)
{
    MeshurlText->SetText(FText::FromString(meshurl));
    ImageurlText->SetText(FText::FromString(imageurl));
    ULoadTextureFromURL::LoadByte(imageurl,[this](UTexture2D *texture)
    {
        GeneratedAvatarImage->SetBrushFromTexture(texture, false);
    });
}

void UAvatarGeneratedPopup::ClosePopup()
{
    this->SetVisibility(ESlateVisibility::Hidden);
}

void UAvatarGeneratedPopup::CopyMeshUrl()
{
    FText stringToCopy = MeshurlText->Text;

    // Convert the FText to FString
    FString TextToCopy = stringToCopy.ToString();
    if (!TextToCopy.IsEmpty())
    {
        FGenericPlatformMisc::ClipboardCopy(*TextToCopy);
    }

}

void UAvatarGeneratedPopup::CopyImageUrl()
{
    FText stringToCopy = ImageurlText->Text;

    // Convert the FText to FString
    FString TextToCopy = stringToCopy.ToString();
    if (!TextToCopy.IsEmpty())
    {
        FGenericPlatformMisc::ClipboardCopy(*TextToCopy);
    }
}