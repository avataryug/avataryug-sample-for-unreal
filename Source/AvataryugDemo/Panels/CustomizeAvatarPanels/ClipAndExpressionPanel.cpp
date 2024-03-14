// Fill out your copyright notice in the Description page of Project Settings.


#include "ClipAndExpressionPanel.h"
#include "Kismet/GameplayStatics.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/SizeBoxSlot.h"
#include "EngineUtils.h"
#include "Components/ExponentialHeightFogComponent.h"
#include "Components/CanvasPanelSlot.h"

void UClipAndExpressionPanel::NativeConstruct()
{
  Super::NativeConstruct();
  if (CommonFunctionHolder == nullptr)
  {
    AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), ACommonFunction::StaticClass());
    CommonFunctionHolder = Cast<ACommonFunction>(FoundActor);
    if (CommonFunctionHolder == nullptr)
    {
      CommonFunctionHolder = GetWorld()->SpawnActor<ACommonFunction>();
    }
  }
   if (AllGraphicsHolder == nullptr)
  {
    AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AAllGraphicsHolder::StaticClass());
    AllGraphicsHolder = Cast<AAllGraphicsHolder>(FoundActor);
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
        if(APIEvents)
        {
            APIEvents->OnScreenOrientation.AddDynamic(this,&UClipAndExpressionPanel::ExpressionScreenOrientation);
        }
    }

    if (AvatarHandler == nullptr)
    {
        AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AAvatarHandler::StaticClass());
        AvatarHandler = Cast<AAvatarHandler>(FoundActor);
        // AvatarHandler->SetActorLabel(FString("AvatarHandler"));

    }
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
   HeadCustomizeButton->OnClicked.RemoveDynamic(this, &UClipAndExpressionPanel::OnClickHeadCustomizeButton);
   HeadCustomizeButton->OnClicked.AddDynamic(this, &UClipAndExpressionPanel::OnClickHeadCustomizeButton);

    FullCustomizeButton->OnClicked.RemoveDynamic(this, &UClipAndExpressionPanel::OnClickFullCustomizeButton);
    FullCustomizeButton->OnClicked.AddDynamic(this, &UClipAndExpressionPanel::OnClickFullCustomizeButton);

    ExpressionButton->OnClicked.RemoveDynamic(this, &UClipAndExpressionPanel::OnClickExpressionButton);
    ExpressionButton->OnClicked.AddDynamic(this, &UClipAndExpressionPanel::OnClickExpressionButton);

    ClipButton->OnClicked.RemoveDynamic(this, &UClipAndExpressionPanel::OnClickClipButton);
    ClipButton->OnClicked.AddDynamic( this, &UClipAndExpressionPanel::OnClickClipButton);


    BuySaveButton->OnClicked.RemoveDynamic(this, &UClipAndExpressionPanel::OnClickBuySaveButton);
    BuySaveButton->OnClicked.AddDynamic(this, &UClipAndExpressionPanel::OnClickBuySaveButton);

    // APIEvents->OnUpdatexpPanelUI.RemoveDynamic(this,&UClipAndExpressionPanel::ShowExpressions);
    // APIEvents->OnUpdatexpPanelUI.AddDynamic(this,&UClipAndExpressionPanel::ShowExpressions);
    // APIEvents->OnItemSelect.RemoveDynamic(this,&UClipAndExpressionPanel::ShowExpressions);
    // APIEvents->OnItemSelect.AddDynamic(this,&UClipAndExpressionPanel::ShowExpressions);

    APIEvents->OnUpdatexpPanelUI.RemoveDynamic(this, &UClipAndExpressionPanel::UpdateClipExpPropUI);
    APIEvents->OnUpdatexpPanelUI.AddDynamic(this, &UClipAndExpressionPanel::UpdateClipExpPropUI);

    APIEvents->OnUpdateClipPanelUI.RemoveDynamic(this, &UClipAndExpressionPanel::UpdateClipPropUI);
    APIEvents->OnUpdateClipPanelUI.AddDynamic(this, &UClipAndExpressionPanel::UpdateClipPropUI);


    APIEvents->OnUpdateUiAfterItemSelect.RemoveDynamic(this, &UClipAndExpressionPanel::OnItemSelected);
    APIEvents->OnUpdateUiAfterItemSelect.AddDynamic(this, &UClipAndExpressionPanel::OnItemSelected);

    APIEvents->OnUpdateUiAfterPurchase.RemoveDynamic(this, &UClipAndExpressionPanel::UpdateUIAfterPurchase);
    APIEvents->OnUpdateUiAfterPurchase.AddDynamic(this, &UClipAndExpressionPanel::UpdateUIAfterPurchase);

    ExpDarkModeButton->OnCheckStateChanged.RemoveDynamic(this, &UClipAndExpressionPanel::OnDarkModeToggleStateChanged);
    ExpDarkModeButton->OnCheckStateChanged.AddDynamic(this, &UClipAndExpressionPanel::OnDarkModeToggleStateChanged);
    GetClipsResponse.BindUFunction(this, "OnGetClipsResponse");
    GetClipsError.BindUFunction(this, "OnGetClipsError");

    GetExpressionsResponse.BindUFunction(this, "OnGetExpressionsResponse");
    GetExpressionsError.BindUFunction(this,"OnGetExpressionsError");

    ClipButtonSizeBox->SetVisibility(ESlateVisibility::Hidden);
}

void UClipAndExpressionPanel::OnItemSelected()
{
  UpdateBuySaveButtonAfterChanges();
}
void UClipAndExpressionPanel::UpdateUIAfterPurchase()
{
  UpdateBuySaveButtonAfterChanges();
}

void UClipAndExpressionPanel::UpdateBuySaveButtonAfterChanges()
{
  BuySaveButton->OnClicked.RemoveDynamic(this, &UClipAndExpressionPanel::BuildModelButton);
  BuySaveButton->OnClicked.RemoveDynamic(this, &UClipAndExpressionPanel::OnClickBuySaveButton);
  if (AvatarHandler->TypeOfMontization == EMonitizeType::Monitize)
  {
    BuySaveButton->SetVisibility(ESlateVisibility::Hidden);

    int count = 0;
    TArray<FEconomyItems> currentSelectedBodyParts = DataHolder->currentSelectedBodyParts;
    for (int i = 0; i < currentSelectedBodyParts.Num(); i++)
    {
      if (!UserInventoryHolder->IsPresentInventory(currentSelectedBodyParts[i].iD))
      {
        count++;
      }
    }
    if (count > 0)
    {
      BuyText->SetText(FText::FromString("Buy"));
      BuySaveButton->SetVisibility(ESlateVisibility::Visible);
      BuySaveButton->OnClicked.AddDynamic(this, &UClipAndExpressionPanel::OnClickBuySaveButton);
    }
    else
    {
      BuyText->SetText(FText::FromString("Save"));
      BuySaveButton->SetVisibility(ESlateVisibility::Visible);
      BuySaveButton->OnClicked.AddDynamic(this, &UClipAndExpressionPanel::BuildModelButton);
    }
  }
  else
  {
    BuySaveButton->SetVisibility(ESlateVisibility::Visible);
    BuyText->SetText(FText::FromString("Save"));
    BuySaveButton->OnClicked.AddDynamic(this, &UClipAndExpressionPanel::BuildModelButton);
  }
}
void UClipAndExpressionPanel::OnClickHeadCustomizeButton()
{
    this->SetVisibility(ESlateVisibility::Hidden);
    APIEvents->ShowPanel(EUIPanels::CUSTOMIZEHEAD,true);
    APIEvents->OnChangeCamera.Broadcast(CameraPanels::CustomizeAvatar_Head);
    AvatarHandler->ForCustomizeAvatar->ResetExpression();
}

void UClipAndExpressionPanel::OnClickFullCustomizeButton()
{
    AvatarHandler->ForCustomizeAvatar->ResetExpression();
    this->SetVisibility(ESlateVisibility::Hidden);
    APIEvents->ShowPanel(EUIPanels::CUSTOMIZEFULL,true);
    APIEvents->OnChangeCamera.Broadcast(CameraPanels::CustomizeAvatar_FullBody);
      UE_LOG(LogTemp, Display, TEXT("OnClickFullBodyCustomizeButton----->>>>"));
  this->SetVisibility(ESlateVisibility::Hidden);
  // APIEvents->OnUpdateBuyButtonUI.RemoveDynamic(this, &UCustomizeFullAvatarPanel::UpdateBuyUI);
}

void UClipAndExpressionPanel::OnClickClipButton()
{
     ExpSelectImage->SetVisibility(ESlateVisibility::Hidden);
     SelectClipImage->SetVisibility(ESlateVisibility::Visible);
      APIEvents->OnChangeCamera.Broadcast(CameraPanels::CustomizeAvatar_FullBody);
    APIEvents->ShowLoading();
    if(clipLists.Num() <= 0)
    {
        UDefaultHandler::GetClips(1,GetClipsResponse,GetClipsError);
    }
    else
    {
        ShowClips();
    }
}

void UClipAndExpressionPanel::OnClickExpressionButton()
{
    ExpSelectImage->SetVisibility(ESlateVisibility::Visible);
    SelectClipImage->SetVisibility(ESlateVisibility::Hidden);
    APIEvents->OnChangeCamera.Broadcast(CameraPanels::CustomizeAvatar_Head);
    APIEvents->ShowLoading();

    if (expressionLists.Num() <= 0)
    {
        UDefaultHandler::GetExpressions(1,GetExpressionsResponse,GetExpressionsError);
    }
    else
    {
        ShowExpressions();
    }
}

void UClipAndExpressionPanel::LoadExpressionClipPanelData() 
{
    if (APIEvents->isDarkMode)
    {
      ExpDarkModeButton->SetCheckedState(ECheckBoxState::Checked);
       OnDarkModeToggleStateChanged(APIEvents->isDarkMode);
    }
    else
    {
      ExpDarkModeButton->SetCheckedState(ECheckBoxState::Unchecked);
      OnDarkModeToggleStateChanged(APIEvents->isDarkMode);
    }
    if (AvatarHandler->TypeOfMontization == EMonitizeType::NonMonitize)
    {
      ExpressionCoinTop_Panel->SetVisibility(ESlateVisibility::Hidden);
    }
    else
    {
    ExpressionCoinTop_Panel->SetVisibility(ESlateVisibility::Visible);
       CoinHeaderPanel->SetCoins();
    }
   AvatarHandler->SetActorRotation(FRotator(0, 0, 0));
    OnClickExpressionButton();

 
    OnItemSelected();
}
void UClipAndExpressionPanel::OnDarkModeToggleStateChanged(bool bNewState)
{
    APIEvents->isDarkMode = bNewState;
  if (bNewState)
  {
    // Get the world
    UWorld* World = GetWorld();

    if (World)
    {
      // Iterate through all actors in the world
      for (TActorIterator<AExponentialHeightFog> ActorItr(World); ActorItr; ++ActorItr)
      {
        AExponentialHeightFog* FogActor = *ActorItr;
          
        // Check if the actor is an ExponentialHeightFog actor
        if (FogActor)
        {
          UActorComponent* FogComponentBase = FogActor->GetComponentByClass(UExponentialHeightFogComponent::StaticClass());

          // Check if the component is an ExponentialHeightFog component
          if (FogComponentBase)
          {
            UExponentialHeightFogComponent* FogComponent = Cast<UExponentialHeightFogComponent>(FogComponentBase);
            // Check if the cast is successful
              if (FogComponent)
            {
              // Set the fog color to black
              FogComponent->SetFogInscatteringColor(FLinearColor(0.0f, 0.003392f, 0.086039f));
            }
          }
        }
      }
    }
  }
  else
  {
    UWorld* World = GetWorld();

    if (World)
    {
      // Iterate through all actors in the world
      for (TActorIterator<AExponentialHeightFog> ActorItr(World); ActorItr; ++ActorItr)
      {
        AExponentialHeightFog* FogActor = *ActorItr;

        // Check if the actor is an ExponentialHeightFog actor
        if (FogActor)
        {
          UActorComponent* FogComponentBase = FogActor->GetComponentByClass(UExponentialHeightFogComponent::StaticClass());

          // Check if the component is an ExponentialHeightFog component
          if (FogComponentBase)
          {
            UExponentialHeightFogComponent* FogComponent = Cast<UExponentialHeightFogComponent>(FogComponentBase);

            // Check if the cast is successful
            if (FogComponent)
            {
              // Set the fog color to black
              FogComponent->SetFogInscatteringColor(FLinearColor::White);
            }
          }
        }
      }
    }
  }
}

void UClipAndExpressionPanel::OnGetClipsResponse(FGetClipsResponse result)
{
    for (int i = 0; i < result.Data.Num(); i++)
    {
        FClip clip;
        clip.DisplayName = result.Data[i].DisplayName;
        clip.Description = result.Data[i].Description;
        clip.Category = result.Data[i].Category;
        clip.CustomMetaData = result.Data[i].CustomMetaData;
   

        clip.Tags = result.Data[i].Tags;
        clip.Color = result.Data[i].Color;
        clip.Metadata = result.Data[i].Metadata;
        clip.Status = result.Data[i].Status;
        clip.ClipType = result.Data[i].ClipType;
        clip.ID = result.Data[i].ID;
        clip.ClipTemplateID = result.Data[i].ClipTemplateID;
        FClipThumbnailUrls thumbnailsUrls;
         UE_LOG(LogTemp,Display,TEXT("CLip--THumb-NUM->>%d"),result.Data[i].ThumbnailUrl.Num());
        for (int j = 0; j < result.Data[i].ThumbnailUrl.Num(); j++) 
        {
            if(j == 0)
            {
                // FThumbnailUrlClip
                FClipThumbnailUrl thumbnail;
                thumbnail.device = result.Data[i].ThumbnailUrl[0].device;
                thumbnail.texture = result.Data[i].ThumbnailUrl[0].texture;
                thumbnail.thumbnail_url = result.Data[i].ThumbnailUrl[0].thumbnail_url;
                 UE_LOG(LogTemp,Display,TEXT("Clip--THumb-->>%s"),*result.Data[i].ThumbnailUrl[0].thumbnail_url);
                // expression.ThumbnailUrl.Add(thumbnail);
                thumbnailsUrls.itemThumbnails.Add(thumbnail);
              break;
            }
          
        }
        clip.ThumbnailsUrl = thumbnailsUrls;

        FClipArtifacts clipartifacts;
        UE_LOG(LogTemp,Display,TEXT("CLip--Art-NUM->>%d"),result.Data[i].Artifacts.Num());
        for (int j = 0; j < result.Data[i].Artifacts.Num(); j++) 
        {
            if(j == 0)
            {
                FClipArtifact artifact;
                artifact.device = result.Data[i].Artifacts[0].device;
                artifact.format = result.Data[i].Artifacts[0].format;
                artifact.url = result.Data[i].Artifacts[0].url;
              UE_LOG(LogTemp,Display,TEXT("Clip--Artifact-->>%s"),*result.Data[i].Artifacts[0].url);
            // expression.ThumbnailUrl.Add(thumbnail);
              clipartifacts.clips.Add(artifact);
              break;
            }
          
        }
        clip.Artifacts = clipartifacts;
  

        clipLists.Add(clip);
    }
    ShowClips();
}

void UClipAndExpressionPanel::OnGetClipsError(FApiException result)
{
    UE_LOG(LogTemp, Display, TEXT("OnGetClipsError---->>%s"),*result.ErrorMessage);
    APIEvents->HideLoading();
    APIEvents->ShowErrorNotification(FString::FromInt(result.ErrorCode),result.ErrorMessage);
}

void UClipAndExpressionPanel::OnGetExpressionsResponse(FGetExpressionsResponse result)
{

    UE_LOG(LogTemp,Display,TEXT("Exp--Response-->>%s"),*result.Status)
    for (int i = 0; i < result.Data.Num(); i++)
    {
        FExpression expression;
        expression.DisplayName = result.Data[i].DisplayName;
        expression.Description = result.Data[i].Description;
        expression.Category = result.Data[i].Category;
        expression.CustomMetaData = result.Data[i].CustomMetaData;
        expression.Tags = result.Data[i].Tags;
        expression.Color = result.Data[i].Color;
        expression.Metadata = result.Data[i].Metadata;
        expression.Status = result.Data[i].Status;
        expression.ID = result.Data[i].ID;

        FBlendShapesExp blendshapeKeys;
        FString expStr = "{";
        expStr.Append("\"blendShapes\":");
        expStr.Append(result.Data[i].BlendshapeKeys);
        expStr.Append("}");
        FJsonObjectConverter::JsonObjectStringToUStruct(expStr, &blendshapeKeys,0,0);
        expression.BlendshapeKeys = blendshapeKeys;

        FExpThumbnailUrls thumbnailsUrls;
        //  UE_LOG(LogTemp,Display,TEXT("Exp--THumb-NUM->>%d"),result.Data[i].ThumbnailUrl.Num());
        for (int j = 0; j < result.Data[i].ThumbnailUrl.Num(); j++) 
        {
            if(j == 0)
            {
                FExpThumbnailUrl thumbnail;
                thumbnail.device = result.Data[i].ThumbnailUrl[0].device;
                thumbnail.texture = result.Data[i].ThumbnailUrl[0].texture;
                thumbnail.thumbnail_url = result.Data[i].ThumbnailUrl[0].thumbnail_url;
            //   UE_LOG(LogTemp,Display,TEXT("Exp--THumb-->>%s"),*result.Data[i].ThumbnailUrl[0].thumbnail_url);
            // expression.ThumbnailUrl.Add(thumbnail);
              thumbnailsUrls.itemThumbnails.Add(thumbnail);
              break;
            }
          
        }
        expression.ThumbnailUrl = thumbnailsUrls;
       
        expressionLists.Add(expression);
    }
    ShowExpressions();
}

void UClipAndExpressionPanel::OnGetExpressionsError(FApiException result)
{
     UE_LOG(LogTemp,Display,TEXT("Exp--Response-->>"),*result.ErrorMessage)
}

void UClipAndExpressionPanel::UpdateClipExpPropUI(bool isUpdate)
{
    UE_LOG(LogTemp, Display, TEXT("--Customize  exp Panel-->>>UpdatePropUI---- "));
    if(isUpdate)
    {
      UE_LOG(LogTemp, Display, TEXT("Clip exp Panel-----isUpdate>> "));
      ShowExpressions();
    }
}

void UClipAndExpressionPanel::UpdateClipPropUI(bool isUpdate)
{
    UE_LOG(LogTemp, Display, TEXT("--Customize Clip  Panel-->>>UpdatePropUI---- "));
    if(isUpdate)
    {
      UE_LOG(LogTemp, Display, TEXT("Clip  Panel-----isUpdate>> "));
      ShowClips();
    }
}

void UClipAndExpressionPanel::ShowExpressions()
{
    if (PropItemListView)
    {
        PropItemListView->ClearListItems();
    }
    float floatValue = expressionLists.Num();
    float contaientGridCount = floatValue / 4;
    int myCeilInt = FMath::CeilToInt(contaientGridCount);
    for (int i = 0; i < myCeilInt; i++)
    {
        UCustomizeListData *item = NewObject<UCustomizeListData>();
        item->StartIndex = 4 * i;
        item->TotalCount = expressionLists.Num();
        item->expressionLists = expressionLists;
        item->dataType = "EXPRESSION";
        PropItemListView->AddItem(item);
    }
    APIEvents->HideLoading();
}

void UClipAndExpressionPanel:: ShowClips()
{
    if (PropItemListView)
    {
        PropItemListView->ClearListItems();
    }
    float floatValue = clipLists.Num();
    float contaientGridCount = floatValue / 4;
    int myCeilInt = FMath::CeilToInt(contaientGridCount);
    for (int i = 0; i < myCeilInt; i++)
    {
        UCustomizeListData *item = NewObject<UCustomizeListData>();
        item->StartIndex = 4 * i;
        item->TotalCount = clipLists.Num();
        item->clipLists = clipLists;
        item->dataType = "CLIP";
        PropItemListView->AddItem(item);
    }
    APIEvents->HideLoading();
}

void UClipAndExpressionPanel::OnClickBuySaveButton()
{
   APIEvents->ShowPanel(EUIPanels::BUYITEMS, true);
}

void UClipAndExpressionPanel::ExpressionScreenOrientation(bool isLandscape)
{
    if(isLandscape)
    {
        UVerticalBoxSlot* VerticalBoxSlot = Cast<UVerticalBoxSlot>(ExpresssionButtonsTopPanel->Slot);
        VerticalBoxSlot->SetPadding(FMargin(0.0f,0.0f,980.0f,0.0f));

        FWidgetTransform Transform;
        Transform.Translation.X = 0.0f;
        Transform.Translation.Y = -168.0f;
        Transform.Scale = FVector2D(1,1);
        Transform.Angle = 0.0f;


        ExpresssionButtonsTopPanel->SetRenderTransform(Transform);


        UVerticalBoxSlot* VerticalPropBoxSlot = Cast<UVerticalBoxSlot>(ExpressionBottomPanel->Slot);
        VerticalPropBoxSlot->SetPadding(FMargin(950.0f,-1250.0f,0.0f,0.0f));

        USizeBoxSlot* ExpressionCoinBoxSlot = Cast<USizeBoxSlot>(ExpressionCoinTop_Panel->Slot);
        ExpressionCoinBoxSlot->SetPadding(FMargin(0,0,960,0));

        // UCanvasPanelSlot *Canvas = Cast<UCanvasPanelSlot>(UndoButton->Slot);
        // Canvas->SetAnchors(FAnchors(0.5f,0.5f,0.5f,0.5f));
        // Canvas->SetOffsets(FMargin(54.0f, -0.34f, 100, 100));
    }
    else
    {
        USizeBoxSlot* ExpressionCoinBoxSlot = Cast<USizeBoxSlot>(ExpressionCoinTop_Panel->Slot);
        // FullBodyCoinBoxSlot->SetPadding(FMargin(0,0,960,0));
        ExpressionCoinBoxSlot->SetPadding(FMargin(0,0,0,0));


        UVerticalBoxSlot* VerticalBoxSlot = Cast<UVerticalBoxSlot>(ExpresssionButtonsTopPanel->Slot);
        VerticalBoxSlot->SetPadding(FMargin(0.0f,0.0f,0.0f,0.0f));
        FWidgetTransform Transform;
        Transform.Translation.X = 0.0f;
        Transform.Translation.Y = 0.0f;
        Transform.Scale = FVector2D(1,1);
        Transform.Angle = 0.0f;
        ExpresssionButtonsTopPanel->SetRenderTransform(Transform);


        UVerticalBoxSlot* VerticalPropBoxSlots = Cast<UVerticalBoxSlot>(ExpressionBottomPanel->Slot);
        VerticalPropBoxSlots->SetPadding(FMargin(0.0f,0.0f,0.0f,0.0f));
    }
}
void UClipAndExpressionPanel::BuildModelButton() {
  APIEvents->ShowLoading();
  FClipExpressionData clipExpressionData;
  clipExpressionData.Style.ClipID = "61c43d03-f21c-4a7c-97fe-9665be6739a4";
  clipExpressionData.Style.ExpressionID = "";
  clipExpressionData.gender = UserDetailHolder->UserDetails.Gender == EGender::FEMALE ? 1 : 0;
  FString metaData;
  FJsonObjectConverter::UStructToJsonObjectString(clipExpressionData, metaData);
  metaData.ReplaceInline(TEXT("\\r"), TEXT(""));
  FAvatarData avatarData;
  avatarData.AgeRange = "18-22";
  avatarData.Race = "Custom";
  avatarData.MetaData = metaData;
  avatarData.Gender = UserDetailHolder->UserDetails.Gender == EGender::FEMALE ? 1 : 0;
  avatarData.CustomMetaData = "";
  avatarData.ColorMeta = CurrentAvatarChanges->changePropColors;
  avatarData.ColorMeta.FaceColor = "#ffffff";
  avatarData.BucketData = CurrentAvatarChanges->changedProps.props;

  for (int i = 0; i < CurrentAvatarChanges->changeBlendShapes.Num(); i++)
  {
    FBlendShapeValue blendshape;
    blendshape.value = CurrentAvatarChanges->changeBlendShapes[i].value;
    blendshape.shapekeys = CurrentAvatarChanges->changeBlendShapes[i].shapekeys;
    avatarData.Blendshapes.Add(blendshape);
  }

  FGrantAvatarPresetItemsToUserRequest request;
  for (int i = 0; i < CurrentAvatarChanges->changedProps.props.Num(); i++)
  {
    FGrantAvatarPresetItemsToUserRequestItemIDsInner item;
    item.ItemID = CurrentAvatarChanges->changedProps.props[i].ID;
    request.ItemIDs.Add(item);
  }
  FString avatarDataStr;
  FJsonObjectConverter::UStructToJsonObjectString(avatarData, avatarDataStr);


  TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
  for (TFieldIterator<FProperty> It(FAvatarData::StaticStruct()); It; ++It)
  {
    FProperty* Property = *It;
    FString PropertyName = Property->GetName();
    TSharedPtr<FJsonValue> JsonValue = FJsonObjectConverter::UPropertyToJsonValue(Property, Property->ContainerPtrToValuePtr<void>(&avatarData, 0));
    JsonObject->SetField(PropertyName, JsonValue);
  }
  
    FString JsonString;
    TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&JsonString);
    FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);
    JsonString.ReplaceInline(TEXT("coreBucket"), TEXT("CoreBucket"));
    JsonString.ReplaceInline(TEXT("expressionId"), TEXT("ExpressionID"));
    JsonString.ReplaceInline(TEXT("clipId"), TEXT("ClipID"));
    JsonString.ReplaceInline(TEXT("hairColor"), TEXT("HairColor"));
    JsonString.ReplaceInline(TEXT("eyebrowColor"), TEXT("EyebrowColor"));
    JsonString.ReplaceInline(TEXT("facialHairColor"), TEXT("FacialHairColor"));
    JsonString.ReplaceInline(TEXT("lipColor"), TEXT("LipColor"));
    JsonString.ReplaceInline(TEXT("faceColor"), TEXT("FaceColor"));
    JsonString.ReplaceInline(TEXT("style"), TEXT("Style"));
    JsonString.ReplaceInline(TEXT("\\n"), TEXT(""));
    JsonString.ReplaceInline(TEXT("\\t"), TEXT(""));
    JsonString.ReplaceInline(TEXT("\"id\""), TEXT("\"ID\""));
    JsonString.ReplaceInline(TEXT(" "), TEXT(""));
    UE_LOG(LogTemp, Display, TEXT("============       %s"),*JsonString);
  
    if (DataHolder->isCustomizeAvatar) 
    {
        if (AvatarHandler->TypeOfMontization == EMonitizeType::Monitize)
        {
            APIEvents->ShowLoading();
            UAvatarPresetsHandler::GrantAvatarPresetItemsToUser(request, [this, JsonString](FGrantAvatarPresetItemsToUserResponse result)
            {
                FGrantAvatarToUserRequest grantAvatarRequest;
                grantAvatarRequest.AvatarData = JsonString;
                UE_LOG(LogTemp, Display, TEXT("GrantAvatarPresetItemsToUser%%%%%%%%"));
                APIEvents->ShowLoading();
                UAvatarPresetsHandler::GrantAvatarPresetToUser( grantAvatarRequest, [this](FGrantAvatarToUserResponse gresult) 
                {
                    CommonFunctionHolder->UpdateDefaultAvatarID(gresult.Data.AvatarID, [this,gresult]
                    { 
                        UE_LOG(LogTemp, Display, TEXT("GrantAvatarPresetToUser%%%%%%%%"));
                        APIEvents->ShowLoading();
                        CommonFunctionHolder->GetUserAllAvatars([this, gresult]() 
                        {
                            UE_LOG(LogTemp, Display, TEXT("GetUserAllAvatars%%%%%%%%"));
                            APIEvents->ShowLoading();
                            CommonFunctionHolder->GenerateMesh(gresult.Data.AvatarID,[this, gresult](FGenerateAvatarMeshResponse resuleMesh) 
                            {
                                UE_LOG(LogTemp, Display, TEXT("GenerateMesh%%%%%%%%"));
                                APIEvents->ShowLoading();
                                CommonFunctionHolder->RenderImage(gresult.Data.AvatarID, [this,resuleMesh](FRenderAvatarImageResponse resultImage)
                                { 
                                    UE_LOG(LogTemp, Display, TEXT("RenderImage%%%%%%%%"));
                                    APIEvents->HideLoading();
                                    DataHolder->cameFromFirstAvatar =true;
                                    APIEvents->ShowGeneratedAvatar(resuleMesh.Data.MeshUrl, resultImage.Data.ImageURL);
                                    //APIEvents->ShowPanel(EUIPanels::HOME, true); 
                                });
                            }); 
                        }); 
                    });
                },
                [this](FApiException errorz)
                {
                    APIEvents->HideLoading();
                    APIEvents->ShowErrorNotification(FString::FromInt(errorz.ErrorCode), errorz.ErrorMessage);
                }); 
            },
            [this](FApiException error)
            {
                APIEvents->HideLoading();
                APIEvents->ShowErrorNotification(FString::FromInt(error.ErrorCode), error.ErrorMessage);
            });
        }
        else
        {
            APIEvents->ShowLoading();
            UAvatarPresetsHandler::GrantAvatarPresetItemsToUser(request, [this, JsonString](FGrantAvatarPresetItemsToUserResponse result)
            {
                FGrantAvatarToUserRequest grantAvatarRequest;
                grantAvatarRequest.AvatarData = JsonString;
                UE_LOG(LogTemp, Display, TEXT("GrantAvatarPresetItemsToUser"));
                APIEvents->ShowLoading();
                UAvatarPresetsHandler::GrantAvatarPresetToUser(grantAvatarRequest, [this](FGrantAvatarToUserResponse gresult)
                { 
                    UE_LOG(LogTemp, Display, TEXT("GrantAvatarPresetToUser"));
                    APIEvents->ShowLoading();
                    CommonFunctionHolder->GetUserAllAvatars([this, gresult]() 
                    {
                        UE_LOG(LogTemp, Display, TEXT("GetUserAllAvatars"));
                        APIEvents->ShowLoading();
                        CommonFunctionHolder->GenerateMesh(gresult.Data.AvatarID,[this, gresult](FGenerateAvatarMeshResponse resuleMesh) 
                        {
                            UE_LOG(LogTemp, Display, TEXT("GenerateMesh"));
                            APIEvents->ShowLoading();
                            CommonFunctionHolder->RenderImage(gresult.Data.AvatarID, [this,resuleMesh](FRenderAvatarImageResponse resultImage)
                            { 
                                UE_LOG(LogTemp, Display, TEXT("RenderImage"));
                                APIEvents->HideLoading();
                                CommonFunctionHolder->GetUserAllAvatars([this]() {});
                                APIEvents->ShowGeneratedAvatar(resuleMesh.Data.MeshUrl,resultImage.Data.ImageURL); 
                            });
                        }); 
                    }); 
                },
                [this](FApiException errorz)
                {
                    APIEvents->HideLoading();
                    APIEvents->ShowErrorNotification(FString::FromInt(errorz.ErrorCode), errorz.ErrorMessage);
                });     
            },
            [this](FApiException error)
            {
                APIEvents->HideLoading();
                APIEvents->ShowErrorNotification(FString::FromInt(error.ErrorCode), error.ErrorMessage);
            });
        }
    } 
    else 
    {
        APIEvents->ShowLoading();
        UAvatarPresetsHandler::GrantAvatarPresetItemsToUser(request, [this, JsonString](FGrantAvatarPresetItemsToUserResponse result)
        {
            FGrantAvatarToUserRequest grantAvatarRequest;
            grantAvatarRequest.AvatarData = JsonString;
            //UE_LOG(LogTemp, Display, TEXT("GrantAvatarPresetItemsToUser=========="));
            APIEvents->ShowLoading();
            UAvatarPresetsHandler::GrantAvatarPresetToUser(grantAvatarRequest, [this](FGrantAvatarToUserResponse gresult)
            { 
               // UE_LOG(LogTemp, Display, TEXT("GrantAvatarPresetToUser==========="));
                APIEvents->ShowLoading();
                CommonFunctionHolder->GetUserAllAvatars([this, gresult]() 
                {
                    //UE_LOG(LogTemp, Display, TEXT("GetUserAllAvatars==========="));
                    APIEvents->ShowLoading();
                    CommonFunctionHolder->GenerateMesh(gresult.Data.AvatarID,[this, gresult](FGenerateAvatarMeshResponse resuleMesh) 
                    {
                        //UE_LOG(LogTemp, Display, TEXT("GenerateMesh=========="));
                        APIEvents->ShowLoading();
                        CommonFunctionHolder->RenderImage(gresult.Data.AvatarID, [this,resuleMesh](FRenderAvatarImageResponse resultImage)
                        { 
                            //UE_LOG(LogTemp, Display, TEXT("RenderImage==========="));
                            APIEvents->HideLoading();
                            APIEvents->ShowGeneratedAvatar(resuleMesh.Data.MeshUrl,resultImage.Data.ImageURL); 
                        });
                    }); 
                }); 
            },
            [this](FApiException errorz)
            {
                APIEvents->HideLoading();
                APIEvents->ShowErrorNotification(FString::FromInt(errorz.ErrorCode), errorz.ErrorMessage);
            }); 
        },
        [this](FApiException error)
        {
            APIEvents->HideLoading();
            APIEvents->ShowErrorNotification(FString::FromInt(error.ErrorCode), error.ErrorMessage);
        });
    }
}