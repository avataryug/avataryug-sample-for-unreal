// Fill out your copyright notice in the Description page of Project Settings.

#include "OnBoardingPanel.h"
#include "OnBoardingAvatarButton.h"
#include "Components/VerticalBoxSlot.h"
#include "JsonObjectConverter.h"
#include "Components/SizeBox.h"
#include "Components/SizeBoxSlot.h"
#include "Components/CanvasPanelSlot.h"

void UOnBoardingPanel::NativeConstruct()
{
    Super::NativeConstruct();

    if (AvatarHandler == nullptr)
    {
        AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AAvatarHandler::StaticClass());
        AvatarHandler = Cast<AAvatarHandler>(FoundActor);
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

    if (UserDetailHolder == nullptr)
    {
        AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AUserDetailHolder::StaticClass());
        UserDetailHolder = Cast<AUserDetailHolder>(FoundActor);
        if (UserDetailHolder == nullptr)

        {
            UserDetailHolder = GetWorld()->SpawnActor<AUserDetailHolder>();
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
    if (APIEvents == nullptr)
    {
        AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AAPIEvents::StaticClass());
        APIEvents = Cast<AAPIEvents>(FoundActor);
        if (APIEvents == nullptr)
        {
            APIEvents = GetWorld()->SpawnActor<AAPIEvents>();
        }
        if (APIEvents)
        {
            APIEvents->OnScreenOrientation.AddDynamic(this, &UOnBoardingPanel::OnBoardingScreenOrientation);
        }
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

    if (CurrentAvatarChangesHolder == nullptr)
    {
        AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), ACurrentAvatarChanges::StaticClass());
        CurrentAvatarChangesHolder = Cast<ACurrentAvatarChanges>(FoundActor);
        // CurrentAvatarChangesHolder->SetActorLabel(FString("CurrentAvatarChangesHolder"));
    }

    CreateCustomButton->OnClicked.RemoveDynamic(this, &UOnBoardingPanel::CreateCustomAvatar);
    CreateCustomButton->OnClicked.AddDynamic(this, &UOnBoardingPanel::CreateCustomAvatar);

    LetsBeginWithAvatarButton->OnClicked.RemoveDynamic(this, &UOnBoardingPanel::LetsBeginWithAvatar);
    LetsBeginWithAvatarButton->OnClicked.AddDynamic(this, &UOnBoardingPanel::LetsBeginWithAvatar);

    SelectGenderCloseButton->OnClicked.RemoveDynamic(this, &UOnBoardingPanel::CloseGenderPanel);
    SelectGenderCloseButton->OnClicked.AddDynamic(this, &UOnBoardingPanel::CloseGenderPanel);

    MaleButton->OnClicked.RemoveDynamic(this, &UOnBoardingPanel::MaleGenderSelected);
    MaleButton->OnClicked.AddDynamic(this, &UOnBoardingPanel::MaleGenderSelected);

    FemaleButton->OnClicked.RemoveDynamic(this, &UOnBoardingPanel::FemaleGenderSelected);
    FemaleButton->OnClicked.AddDynamic(this, &UOnBoardingPanel::FemaleGenderSelected);

    GetAvatarPresetsResult.BindUFunction(this, "OnGetAvatarPresetsResult");
    GetAvatarPresetsError.BindUFunction(this, "OnGetAvatarPresetsError");

    onGltfModelHomeCallback.BindUFunction(this, "OnModelAssetHomeCallback");

    // OnChangeIndex.BindUFunction(this, "ScrollOnClick");
    // OnChangeIndex.BindDynamic(this, &UOnBoardingPanel::LoadModelScrollerValue);
    //  OnChangeIndex.BindUFunction(this, "ScrollOnClick");
    // APIEvents->OnChangeFlipbookIndex.BindUFunction(this, "ScrollOnClick");

    APIEvents->OnChangeFlipbookIndex.AddDynamic(this, &UOnBoardingPanel::LoadModelScrollerValue);

    // APIEvents->OnOnBoardingClickIndex.AddDynamic( this ,&UOnBoardingPanel::ScrollOnClick);

    UpdateUserDemographicsResponse.BindUFunction(this, "OnUpdateUserDemographicsResponse");
    UpdateUserDemographicsError.BindUFunction(this, "OnUpdateUserDemographicsError");

    GrantAvatarPresetItemsToUserResponse.BindUFunction(this, "OnGrantAvatarPresetItemsToUserResponse");
    GrantAvatarPresetItemsToUserError.BindUFunction(this, "OnGrantAvatarPresetItemsToUserError");

    GrantAvatarToUserResponse.BindUFunction(this, "OnGrantAvatarToUserResponse");
    GrantAvatarToUserError.BindUFunction(this, "OnGrantAvatarToUserError");

    RenderAvatarImageResponse.BindUFunction(this, "OnRenderAvatarImageResponse");
    RenderAvatarImageError.BindUFunction(this, "OnRenderAvatarImageError");

    GenerateAvatarMeshResponse.BindUFunction(this, "OnGenerateAvatarMeshResponse");
    GenerateAvatarMeshError.BindUFunction(this, "OnGenerateAvatarMeshError");

    UpdateDefaultAvatarIDResult.BindUFunction(this, "OnUpdateDefaultAvatarIDResult");
    UpdateDefaultAvatarIDError.BindUFunction(this, "OnUpdateDefaultAvatarIDError");

    OnGetUserInventoryResult.BindUFunction(this, "GetUserInventoryResult");
    OnInventoryApiError.BindUFunction(this, "InventoryApiError");

    GetUsersAllAvatarsResult.BindUFunction(this, "OnGetUsersAllAvatarsResult");
    GetUsersAllAvatarsError.BindUFunction(this, "OnGetUsersAllAvatarsError");
}

void UOnBoardingPanel::LoadOnBoardingPanelDetail()
{
    GltfFullActorList.Empty();
    APIEvents->ShowLoading();
    ArtifactList.Empty();
    // UAvatarPresetsHandler::GetAvatarPresets(3,1,GetAvatarPresetsResult, GetAvatarPresetsError);
    UAvatarPresetsHandler::GetAvatarPresets(
        3, 1, [this](FGetAvatarPresetsResult res)
        {
            FString ResultJsonString;

            // Serialize FGetAvatarPresetsResult to a JSON string.
            FJsonObjectConverter::UStructToJsonObjectString(res, ResultJsonString);

            // Log the JSON string.
            UE_LOG(LogTemp, Warning, TEXT("GetAvatarPresets---->>Result JSON: %s"), *ResultJsonString);
            UE_LOG(LogTemp, Display, TEXT("LoadOnBoardingPanelDetail------>%s"), *res.Status);
            UE_LOG(LogTemp, Display, TEXT("LoadOnBoardingPanelDetail---COUNT--->%d"), res.Data.Num());
            presetsResult = res;
            if (res.Data.Num() > 0)
            {

                presetsResult.Data = res.Data;

                m_thumburls.SetNum(presetsResult.Data.Num());
                m_SpawnedModels.SetNum(presetsResult.Data.Num());
                avatarUrl.SetNum(presetsResult.Data.Num());
                for (FGetAvatarPresetsResultDataInner item : presetsResult.Data)
                {
                    presetsQueue.Add(item);
                    UE_LOG(LogTemp, Display, TEXT("PRESETs---ADDED--->"));
                    // ArtifactList.Add(item);
                }
                NewQueuePresetModel();
            } },
        [this](FApiException error)
        {
            UE_LOG(LogTemp, Display, TEXT("LoadOnBoardingPanelDetail---error--->%s"), *error.ErrorMessage);
        });
}

void UOnBoardingPanel::LetsBeginWithAvatar()
{
    APIEvents->ShowLoading();
    FClipExpressionData clipExpressionData;
    clipExpressionData.Style.ClipID = "standard_clip";
    clipExpressionData.Style.ExpressionID = "";
    UserDetailHolder->UserDetails.Gender = ArtifactList[CurrentIndex].Gender == 2 ? EGender::FEMALE : EGender::MALE;
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
    avatarData.AgeRange = ArtifactList[CurrentIndex].AgeRange;
    avatarData.Race = ArtifactList[CurrentIndex].Race;
    avatarData.Gender = UserDetailHolder->UserDetails.Gender == EGender::FEMALE ? 1 : 0;
    avatarData.CustomMetaData = ArtifactList[CurrentIndex].CustomMetaData;

    FPropColors propcolors;
    FJsonObjectConverter::JsonObjectStringToUStruct(ArtifactList[CurrentIndex].Color, &propcolors,0,0);
    avatarData.ColorMeta = propcolors;

    FProps props;
    FString propString = "{";
    propString.Append("\"props\":");
    propString.Append(ArtifactList[CurrentIndex].Props);
    propString.Append("}");
    FJsonObjectConverter::JsonObjectStringToUStruct(propString, &props,0,0);
    avatarData.BucketData = props.props;

    FBlendShapes blendshapes;
    FString blendString = "{";
    blendString.Append("\"blendShapes\":");
    blendString.Append(ArtifactList[CurrentIndex].BlendshapeKeys);
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
    UE_LOG(LogTemp, Display, TEXT("==================  %s"), *avatarDataStr);

    UAvatarPresetsHandler::GrantAvatarPresetItemsToUser(
        request, [this](FGrantAvatarPresetItemsToUserResponse result)
        {
       // UE_LOG(LogTemp, Display, TEXT("-------GET------GrantAvatarPresetItemsToUser------>%s"), *result.Status);
        FGrantAvatarToUserRequest grantAvatarRequest;
        grantAvatarRequest.AvatarData = avatarDataStr;
        UAvatarPresetsHandler::GrantAvatarPresetToUser(
            grantAvatarRequest, [this](FGrantAvatarToUserResponse gresult)
            {
                  //  UE_LOG(LogTemp, Display, TEXT("-------GET------GrantAvatarPresetToUser------>%s"), *gresult.Status);
                    CommonFunctionHolder->UpdateDefaultAvatarID(gresult.Data.AvatarID, [this,gresult]
                                                                { 
                                                                    UserDetailHolder->UserDetails.DefaultAvatarID = gresult.Data.AvatarID;
                                                                                                                      CommonFunctionHolder->GetCommonUserInventory([this]
                                                                                                                                                                   {
                       // UE_LOG(LogTemp, Display, TEXT("CommonFunctionHolder---GET--UserInventory--->Response------>"));
                        CommonFunctionHolder->GetUserAllAvatars([this]()
                                                                {

                                this->SetVisibility(ESlateVisibility::Hidden);
    APIEvents->ShowPanel(EUIPanels::HOME, true); }); }); }); },
            [this](FApiException errorz)
            {
                APIEvents->HideLoading();
                APIEvents->ShowErrorNotification(FString::FromInt(errorz.ErrorCode), errorz.ErrorMessage);
               // UE_LOG(LogTemp, Display, TEXT("GrantAvatarPresetItemsToUser---ERROR--->%s"), *errorz.ErrorMessage);
            }); },
        [this](FApiException error)
        {
            APIEvents->HideLoading();
            APIEvents->ShowErrorNotification(FString::FromInt(error.ErrorCode), error.ErrorMessage);
            //  UE_LOG(LogTemp, Display, TEXT("UpdateUserDemographics---ERROR--->%s"), *error.ErrorMessage);
        });
}

void UOnBoardingPanel::OnUpdateUserDemographicsResponse(FUpdateUserDemographicsResponse result)
{
    FGrantAvatarPresetItemsToUserRequest request;
    UE_LOG(LogTemp, Display, TEXT("OnUpdateUserDemographicsResponse------>"));
    for (int i = 0; i < UserDetailHolder->UserDetails.currentUserSelectedAvatar.AvatarData.BucketData.Num(); i++)
    {
        FGrantAvatarPresetItemsToUserRequestItemIDsInner item;
        item.ItemID = UserDetailHolder->UserDetails.currentUserSelectedAvatar.AvatarData.BucketData[i].ID;
        // itemID.Add(UserDetailHolder->UserDetails.currentUserSelectedAvatar.AvatarData.BucketData[i].ID);
        request.ItemIDs.Add(item);
    }
    EGender GenderValue = UserDetailHolder->UserDetails.Gender; // Replace with your enum value

    // Convert enum value to string
    FString EnumAsString = UEnum::GetValueAsString(GenderValue);
    UE_LOG(LogTemp, Display, TEXT("USER DEMO GENDER------>%s"), *EnumAsString);
    UAvatarPresetsHandler::GrantAvatarPresetItemsToUser(request, GrantAvatarPresetItemsToUserResponse, GrantAvatarPresetItemsToUserError);
}

void UOnBoardingPanel::OnUpdateUserDemographicsError(FOnApiException error)
{
}

void UOnBoardingPanel::OnGrantAvatarPresetItemsToUserResponse(FGrantAvatarPresetItemsToUserResponse result)
{
    UE_LOG(LogTemp, Display, TEXT("OnGrantAvatarPresetItemsToUserResponse------>"));
    FGrantAvatarToUserRequest request;
    //   request.UserID = UserDetailHolder->UserDetails.userID;
    request.AvatarData = avatarDataStr;
    UAvatarPresetsHandler::GrantAvatarPresetToUser(request, GrantAvatarToUserResponse, GrantAvatarToUserError);
}

void UOnBoardingPanel::OnGrantAvatarToUserResponse(FGrantAvatarToUserResponse result)
{
    UE_LOG(LogTemp, Display, TEXT("On--GrantAvatar--->ToUserResponse------>%s"), *result.Data.AvatarID);

    FUpdateDefaultAvatarIDRequest request;
    request.DefaultAvatarID = result.Data.AvatarID;
    avatarid = result.Data.AvatarID;
    // UDefaultHandler::UpdateDefaultAvatarID(request, UpdateDefaultAvatarIDResult, UpdateDefaultAvatarIDError);
    CommonFunctionHolder->UpdateDefaultAvatarID(avatarid, [this]
                                                {
    // APIEvents->HideLoading();
    UE_LOG(LogTemp, Display, TEXT("-------UpdateDefaultAvatarID--->Response------>"));
        CommonFunctionHolder->GetCommonUserInventory([this]{
            UE_LOG(LogTemp, Display, TEXT("CommonFunctionHolder---GET--UserInventory--->Response------>"));
                // UUserAccountManagementHandler::GetUsersAllAvatars(UserDetailHolder->UserDetails.userID, GetUsersAllAvatarsResult, GetUsersAllAvatarsError);
                  CommonFunctionHolder->GetUserAllAvatars([this]
                  {
                    UE_LOG(LogTemp, Display, TEXT("CommonFunctionHolder---GET--GetUserAllAvatars--->Response------>"));
                        TArray<AActor*> AttachedChildActors;
                        AvatarHandler->SpawnedOnBoardingParent->GetAttachedActors(AttachedChildActors);

                        for (AActor* AttachedActor : AttachedChildActors)
                        {
                            // Check if AttachedActor is a child actor you are interested in
                            if (AttachedActor)
                            {
                                // UE_LOG(LogTemp, Display, TEXT("On--SpawnedOnBoardingParent--->Child------>%s"),*AttachedActor->GetActorLabel());
                                AttachedActor->Destroy();
                            }
                        }
                        // UCommomFunction* CommonFunctionInstance = NewObject<UCommomFunction>(); // Create an instance

                        if (CommonFunctionHolder)
                        {
                            UE_LOG(LogTemp, Display, TEXT("On--CommonFunctionInstance--->Child------>"))
                            CommonFunctionHolder->SetCurrentAvatarDetail(); // Call the function on the instance
                        }
                        AvatarHandler->SetCurrentAvatarDetail();
                        // UCommomFunction::SetCurrentAvatarDetail();
                        this->SetVisibility(ESlateVisibility::Hidden);
                        APIEvents->ShowPanel(EUIPanels::HOME, true);
                });
        }); });
    // FRenderAvatarImageRequest request;

    // request.AvatarID = result.Data.AvatarID;
    // request.Platform = "Android";
    // UDefaultHandler::RenderAvatarImage(request, RenderAvatarImageResponse, RenderAvatarImageError);
}
void UOnBoardingPanel::OnRenderAvatarImageResponse(FRenderAvatarImageResponse result)
{
    FGenerateAvatarMeshRequest request;
    request.AvatarID = avatarid;
    request.Platform = "Android";
    UE_LOG(LogTemp, Display, TEXT("On--RenderAvatar--->Response------>"));
    UDefaultHandler::GenerateAvatarMesh(request, GenerateAvatarMeshResponse, GenerateAvatarMeshError);
}

void UOnBoardingPanel::OnGenerateAvatarMeshResponse(FGenerateAvatarMeshResponse result)
{
    FUpdateDefaultAvatarIDRequest request;
    request.DefaultAvatarID = avatarid;
    UE_LOG(LogTemp, Display, TEXT("On--GenerateAvatarMesh--->Response------>"));
    // UDefaultHandler::UpdateDefaultAvatarID(request, UpdateDefaultAvatarIDResult, UpdateDefaultAvatarIDError);
    CommonFunctionHolder->UpdateDefaultAvatarID(avatarid, [this]
                                                {
         APIEvents->HideLoading();
    UE_LOG(LogTemp, Display, TEXT("On--UpdateDefaultAvatarID--->Response------>%s")); });
}

void UOnBoardingPanel::OnUpdateDefaultAvatarIDResult(FUpdateDefaultAvatarIDResult result)
{
    // FString userid, FOnGetUserInventoryResult result, FOnApiException error
    APIEvents->HideLoading();
    UE_LOG(LogTemp, Display, TEXT("On--UpdateDefaultAvatarID--->Response------>%s"), *result.Message);
    // UserDetailHolder->UserDetails.DefaultAvatarID = result.
    // UUserItemManagementHandler::GetUserInventory(UserDetailHolder->UserDetails.userID, OnGetUserInventoryResult, OnInventoryApiError);
    // UUserItemManagementHandler::GetUserInventoryCall(UserDetailHolder->UserDetails.userID, [this](FGetUserInventoryResult result){
    //     UE_LOG(LogTemp, Display, TEXT("GET--UserInventory--->Response------>%s"), *result.Status);
    //      UserInventoryHolder->AddUserInventory(result.Data);
    //

    // },[this](FApiException error)
    // {
    //     UE_LOG(LogTemp, Display, TEXT("GET--UserInventory--->Error------>"));
    // } );
    CommonFunctionHolder->GetCommonUserInventory([this]
                                                 {
        UE_LOG(LogTemp, Display, TEXT("CommonFunctionHolder---GET--UserInventory--->Response------>"));
            UUserAccountManagementHandler::GetUsersAllAvatars(UserDetailHolder->UserDetails.userID, GetUsersAllAvatarsResult, GetUsersAllAvatarsError); });
}

void UOnBoardingPanel::GetUserInventoryResult(FGetUserInventoryResult result)
{

    UE_LOG(LogTemp, Display, TEXT("GET--UserInventory--->Response------>"));
}

void UOnBoardingPanel::OnGetUsersAllAvatarsResult(FGetUsersAllAvatarsResult result)
{
    if (DataHolder != nullptr)
    {
        DataHolder->SynAvatars();
    }
    FString JsonString;
    FJsonObjectConverter::UStructToJsonObjectString(result.Data[0], JsonString);
    UE_LOG(LogTemp, Display, TEXT("LOADING PART---->>%s"), *JsonString);
    //  UE_LOG(LogTemp, Display, TEXT("GET--UsersAllAvatars--->Response------>%s",*result.Data[0]));
    FString userid = UserDetailHolder->UserDetails.userID;
    FString platfrom = "Android";

    if (result.Data.Num() > 0)
    {

        UserDetailHolder->UserDetails.userAvatars.Empty();
        for (int i = 0; i < result.Data.Num(); i++)
        {
            // UE_LOG(LogTemp,Display,TEXT("userAvatars---->>%s"),*result.Data[i].AvatarUrl);

            // uservatar.AvatarID = result.Data[i].AvatarID;
            // UserDetailHolder->UserDetails.DefaultAvatarID = result.Data[i].AvatarID;
            // FString JsonStr;
            // FJsonObjectConverter::UStructToJsonObjectString(result.Data[i], JsonStr);
            // UE_LOG(LogTemp,Display,TEXT("userAvatars Data---->>%s"),*JsonStr);

            FAvatarUrlDataList avatarurls;
            if (!result.Data[i].AvatarUrl.IsEmpty())
            {
                FString avatarurlstring = "{";
                avatarurlstring.Append("\"AvatarUrls\":");
                avatarurlstring.Append(result.Data[i].AvatarUrl);
                avatarurlstring.Append("}");
                FJsonObjectConverter::JsonObjectStringToUStruct(avatarurlstring, &avatarurls,0,0);
                UE_LOG(LogTemp, Display, TEXT("Same AvatarUrls---->%s"), *result.Data[i].AvatarUrl);
                // uservatar.AvatarUrls = avatarurls.AvatarUrls;
            }
            FAvatarThumbDataList thumburls;
            if (!result.Data[i].ThumbUrl.IsEmpty())
            {

                FString thumburlstring = "{";
                thumburlstring.Append("\"ThumbUrls\":");
                thumburlstring.Append(result.Data[i].ThumbUrl);
                thumburlstring.Append("}");
                FJsonObjectConverter::JsonObjectStringToUStruct(thumburlstring, &thumburls,0,0);
                UE_LOG(LogTemp, Display, TEXT("Same thumburlstring---->%s"), *thumburlstring);
                // uservatar.ThumbUrls = thumburls.ThumbUrls;
            }

            FUserAvatar tempuservatar = FUserAvatar();

            // FAvatarData avaatar;
            FAvatarData avaatar;
            FJsonObjectConverter::JsonObjectStringToUStruct(result.Data[i].AvatarData, &avaatar,0,0);
            // UE_LOG(LogTemp,Display,TEXT(" AvatarUrls---->%s"),*avaatarstring);
            // Avatar->AvatarData = FAvatarData();
            tempuservatar.AvatarData.Race = avaatar.Race;
            tempuservatar.AvatarData.AgeRange = avaatar.AgeRange;
            tempuservatar.AvatarData.Gender = avaatar.Gender;
            tempuservatar.AvatarData.CustomMetaData = avaatar.CustomMetaData;
            tempuservatar.AvatarData.MetaData = avaatar.MetaData;
            tempuservatar.AvatarData.ColorMeta = avaatar.ColorMeta;
            tempuservatar.AvatarData.BucketData = avaatar.BucketData;
            tempuservatar.AvatarData.Blendshapes = avaatar.Blendshapes;
            tempuservatar.AvatarID = result.Data[i].AvatarID;
            tempuservatar.AvatarUrls = avatarurls.AvatarUrls;
            tempuservatar.ThumbUrls = thumburls.ThumbUrls;

            UserDetailHolder->UserDetails.userAvatars.Add(tempuservatar);

            if (UserDetailHolder->UserDetails.DefaultAvatarID == tempuservatar.AvatarID)
            {
                UE_LOG(LogTemp, Display, TEXT("Same Avatar IDss---->"));
                UserDetailHolder->UserDetails.currentUserSelectedAvatar = tempuservatar;
                UserDetailHolder->UserDetails.Gender = UserDetailHolder->UserDetails.currentUserSelectedAvatar.AvatarData.Gender == 1 ? EGender::FEMALE : EGender::MALE;
            }
        }
        //
    }

    TArray<AActor *> AttachedChildActors;
    AvatarHandler->SpawnedOnBoardingParent->GetAttachedActors(AttachedChildActors);

    for (AActor *AttachedActor : AttachedChildActors)
    {
        // Check if AttachedActor is a child actor you are interested in
        if (AttachedActor)
        {
            // UE_LOG(LogTemp, Display, TEXT("On--SpawnedOnBoardingParent--->Child------>%s"),*AttachedActor->GetActorLabel());
            AttachedActor->Destroy();
        }
    }
    // UCommomFunction* CommonFunctionInstance = NewObject<UCommomFunction>(); // Create an instance

    if (CommonFunctionHolder)
    {
        UE_LOG(LogTemp, Display, TEXT("On--CommonFunctionInstance--->Child------>"))
        CommonFunctionHolder->SetCurrentAvatarDetail(); // Call the function on the instance
    }
    AvatarHandler->SetCurrentAvatarDetail();
    // UCommomFunction::SetCurrentAvatarDetail();
    this->SetVisibility(ESlateVisibility::Hidden);
    APIEvents->ShowPanel(EUIPanels::HOME, true);
}
void UOnBoardingPanel::OnGetUsersAllAvatarsError(FApiException error)
{
}

void UOnBoardingPanel::InventoryApiError(FApiException error)
{
}
void UOnBoardingPanel::OnUpdateDefaultAvatarIDError(FApiException error)
{
}

void UOnBoardingPanel::OnGenerateAvatarMeshError(FApiException error)
{
}

void UOnBoardingPanel::OnRenderAvatarImageError(FApiException error)
{
}

void UOnBoardingPanel::OnGrantAvatarToUserError(FApiException error)
{
}

void UOnBoardingPanel::OnGrantAvatarPresetItemsToUserError(FApiException error)
{
}

void UOnBoardingPanel::CreateCustomAvatar()
{
    DataHolder->isCustomizeAvatar = true;
    //  this->SetVisibility(ESlateVisibility::Hidden);
    SelectGenderPanel->SetVisibility(ESlateVisibility::Visible);
}
void UOnBoardingPanel::CloseGenderPanel()
{
    SelectGenderPanel->SetVisibility(ESlateVisibility::Hidden);
}
void UOnBoardingPanel::OnGetAvatarPresetsResult(FGetAvatarPresetsResult result)
{
    UE_LOG(LogTemp, Warning, TEXT("Code: %d"), result.Code);
    UE_LOG(LogTemp, Warning, TEXT("Status: %s"), *result.Status);

    for (const FGetAvatarPresetsResultDataInner &InnerData : result.Data)
    {
        UE_LOG(LogTemp, Warning, TEXT("InnerData MeshArtifacts: %s"), *InnerData.MeshArtifacts);
        UE_LOG(LogTemp, Warning, TEXT("------"));
        UE_LOG(LogTemp, Warning, TEXT("InnerData ImageArtifacts: %s"), *InnerData.ImageArtifacts);
    }
    ArtifactList.Empty();
    ArtifactQueueList.Empty();
    for (int i = 0; i < result.Data.Num(); i++)
    {
        ArtifactList.Add(result.Data[i]);
        ArtifactQueueList.Add(result.Data[i]);
    }
    QueuePresetModel();
}

void UOnBoardingPanel::OnGetAvatarPresetsError(FApiException error)
{
    UE_LOG(LogTemp, Display, TEXT("OnGetAvatarPresetsError-->>>%s"), *error.ErrorMessage);
}

void UOnBoardingPanel::QueuePresetModel()
{
    if (ArtifactQueueList.Num() > 0)
    {
        FGetAvatarPresetsResultDataInner data = ArtifactQueueList[0];
        ArtifactQueueList.RemoveAt(0);
        LoadArtifact(data);
    }
    else
    {
        ShowOnBoarding();
    }
}

void UOnBoardingPanel::NewQueuePresetModel()
{
    UE_LOG(LogTemp, Display, TEXT("NewQueuePresetModel------>"));
    if (presetsQueue.Num() > 0)
    {
        UE_LOG(LogTemp, Display, TEXT("presetsQueue---Greater > 0 --->"));
        // FGetAvatarPresetsResultDataInner data = ArtifactQueueList[0];
        // ArtifactQueueList.RemoveAt(0);
        LoadArtifacts(presetsQueue[0], presetsQueue.Num());
    }
    else
    {
        ShowNewOnBoarding();
    }
}

void UOnBoardingPanel::LoadArtifact(FGetAvatarPresetsResultDataInner artdata)
{
    FString artifactString = "{";
    artifactString.Append("\"artifacts\":");
    artifactString.Append(artdata.MeshArtifacts);
    artifactString.Append("}");
    FJsonObjectConverter::JsonObjectStringToUStruct(artifactString, &artifactDatalist,0,0);
    UE_LOG(LogTemp, Display, TEXT("LoadArtifact  %s"), *artifactString);

    if (artifactDatalist.artifacts.Num() > 0)
    {
        FglTFRuntimeConfig runtimeConfig;
        runtimeConfig.TransformBaseType = EglTFRuntimeTransformBaseType::YForward;
        FJsonSerializableKeyValueMap headers;
        UglTFRuntimeFunctionLibrary::glTFLoadAssetFromUrl(artifactDatalist.artifacts[0].url, headers, onGltfModelHomeCallback, runtimeConfig);
        UE_LOG(LogTemp, Display, TEXT("MESH URRLLL---->>  %s"), *artifactDatalist.artifacts[0].url);
        meshURLList.Add(artifactDatalist.artifacts[0].url);
    }
    else
    {
        QueuePresetModel();
    }
}

void UOnBoardingPanel::LoadArtifacts(FGetAvatarPresetsResultDataInner resultDataInner, int i)
{
    UE_LOG(LogTemp, Display, TEXT("LoadArtifacts--->"));
    FAvatarPresetArtifacts presetArtifacts;
    FString artifactString = "{";
    artifactString.Append("\"artifacts\":");
    artifactString.Append(resultDataInner.MeshArtifacts);
    artifactString.Append("}");
    FJsonObjectConverter::JsonObjectStringToUStruct(artifactString, &presetArtifacts,0,0);

    // FString JsonString;
    // FJsonObjectConverter::UStructToJsonObjectString(resultDataInner, JsonString);
    // UE_LOG(LogTemp,Display,TEXT("resultDataInner JSONDATA---->>%s"),*JsonString);

    UE_LOG(LogTemp, Display, TEXT("LoadArtifacts--->%s"), *resultDataInner.MeshArtifacts);
    UE_LOG(LogTemp, Display, TEXT("LoadArtifacts-presetArtifacts-->%d"), presetArtifacts.artifacts.Num());
    if (presetArtifacts.artifacts.Num() > 0)
    {

        int32 PlatformValue = CommonFunctionHolder->GetPlatformAsInt();
        FAvatarPresetArtifact artifact;
        for (FAvatarPresetArtifact &item : presetArtifacts.artifacts)
        {
            UE_LOG(LogTemp, Display, TEXT("presetArtifacts ---->>Artifact  %s"), *item.url);
            UE_LOG(LogTemp, Display, TEXT("presetArtifacts ---->>Artifact---device->>>  %d"), item.device);
            // if(item.device == PlatformValue)
            // {
            artifact = item;
            // break;
            // }
        }

        if (!artifact.url.IsEmpty())
        {
            avatarUrl[presetsResult.Data.Num() - i] = artifact.url;
            FglTFRuntimeConfig runtimeConfig;
            runtimeConfig.TransformBaseType = EglTFRuntimeTransformBaseType::YForward;
            FJsonSerializableKeyValueMap headers;
            UglTFRuntimeFunctionLibrary::glTFLoadAssetFromUrl(artifact.url, headers, onGltfModelHomeCallback, runtimeConfig);
            UE_LOG(LogTemp, Display, TEXT("MESH URRLLL---->>  %s"), *artifact.url);

            meshURLList.Add(artifact.url);
        }
        else
        {
            APIEvents->HideLoading();
        }
        FString imageArtifactString = "{";
        imageArtifactString.Append("\"ImageArtifacts\":");
        imageArtifactString.Append(resultDataInner.ImageArtifacts);
        imageArtifactString.Append("}");
        FAvatarPresetImageArtifacts artifactlist;
        FJsonObjectConverter::JsonObjectStringToUStruct(imageArtifactString, &artifactlist,0,0);
        TSharedPtr<FJsonObject> JsonObject;
        TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(imageArtifactString);
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
                        UE_LOG(LogTemp, Warning, TEXT("First ONBAORDING ONE URL: %s"), *Url);
                        m_thumburls[presetsResult.Data.Num() - i] = Url;
                        // ULoadTextureFromURL::LoadTexture(Url,OnReceiveTexture);
                        //   ULoadTextureFromURL::LoadTexture(artifactlist.artifacts[0].url,ReceiveEyebrowTexture);
                    }
                }
            }
        }
        else
        {
            // Handle JSON parsing error if needed
            // UE_LOG(LogTemp, Display, TEXT("LoadArtifacts-presetArtifacts-NOT AVAILABLE ->%d"),presetArtifacts.artifacts.Num());
            // APIEvents->HideLoading();
        }
    }
    else
    {
        // Handle JSON parsing error if needed
        UE_LOG(LogTemp, Display, TEXT("LoadArtifacts-presetArtifacts-NOT AVAILABLE ->%d"), presetArtifacts.artifacts.Num());
        APIEvents->HideLoading();
        // APIEvents->ShowError
        APIEvents->ShowErrorNotification(FString::FromInt(400), "PresetArtifacts are NOT AVAILABLE");
    }
}

void UOnBoardingPanel::OnModelAssetHomeCallback(UglTFRuntimeAsset *asset)
{
    FActorSpawnParameters spawnparams;
    spawnparams.Owner = AvatarHandler->SpawnedOnBoardingParent;
    if (BP_GltfFullActorHome != nullptr)
    {
        const FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
        AGltfFullActor *GltfFullActorHome = GetWorld()->SpawnActor<AGltfFullActor>(BP_GltfFullActorHome, FVector(0, 0, 0), FRotator(0, 0, 0), spawnparams);
        GltfFullActorHome->Asset = asset;
        GltfFullActorHome->AttachToActor(AvatarHandler->SpawnedOnBoardingParent, AttachmentTransformRules);
        GltfFullActorHome->LoadModel();
        GltfFullActorHome->SetActorHiddenInGame(true);
        GltfFullActorList.Add(GltfFullActorHome);
        m_SpawnedModels.Add(GltfFullActorHome);
        presetsQueue.RemoveAt(0);
        NewQueuePresetModel();
        // APIEvents->HideLoading();
        // QueuePresetModel();
    }
}
void UOnBoardingPanel::LoadModelScrollerValue(int index)
{
    // modelIndex=index;
    // if(AEventHandlerRef)
    // {

    if (BP_GltfFullActorHome != nullptr)
    {
        if (GltfFullActorList.Num() > 0)
        {
            for (int i = 0; i < GltfFullActorList.Num(); i++)
            {
                if (i == index)
                {
                    GltfFullActorList[i]->SetActorHiddenInGame(false);
                }
                else
                {
                    GltfFullActorList[i]->SetActorHiddenInGame(true);
                }
            }
        }
    }
    CurrentIndex = index;
    APIEvents->url = meshURLList[index];
    UE_LOG(LogTemp, Display, TEXT("Index Value------>>%d"), index);
    UE_LOG(LogTemp, Display, TEXT("Index URL------>>%s"), *meshURLList[index]);
    APIEvents->HideLoading();
    // APIEvents->OnChangeFlipbookIndex.Broadcast(index);
    // }
    // if(ArtifactList.Num() == ButtonsH.Num())
    // {
    //     APIEvents->HideLoading();
    // }
}

void UOnBoardingPanel::ShowOnBoarding()
{
    // for (int i = 0; i < ArtifactList.Num(); i++)
    // {
    //     UUserWidget *widget = CreateWidget(this, AvatarButton);
    //     OnBoardingAvatarBox->AddChildToHorizontalBox(widget);
    //     UOnBoardingAvatarButton *buttons = Cast<UOnBoardingAvatarButton>(widget);
    // }
    for (int i = 0; i < ArtifactList.Num(); i++)
    {
        UUserWidget *widget = CreateWidget(this, AvatarButton);
        OnBoardingAvatarBox->AddChildToHorizontalBox(widget);
        UOnBoardingAvatarButton *buttons = Cast<UOnBoardingAvatarButton>(widget);
        buttons->SetButtonData(i);
        ButtonsH.Add(widget);
    }
    LoadModelScrollerValue(0);
}

void UOnBoardingPanel::ShowNewOnBoarding()
{
    APIEvents->ShowLoading();
    // for (int i = 0; i < ArtifactList.Num(); i++)
    // {
    //     UUserWidget *widget = CreateWidget(this, AvatarButton);
    //     OnBoardingAvatarBox->AddChildToHorizontalBox(widget);
    //     UOnBoardingAvatarButton *buttons = Cast<UOnBoardingAvatarButton>(widget);
    // }
    for (int i = 0; i < m_thumburls.Num(); i++)
    {
        UUserWidget *widget = CreateWidget(this, AvatarButton);
        OnBoardingAvatarBox->AddChildToHorizontalBox(widget);
        UOnBoardingAvatarButton *buttons = Cast<UOnBoardingAvatarButton>(widget);
        buttons->SetNewButtonData(i, m_thumburls[i]);
        ButtonsH.Add(widget);
        APIEvents->HideLoading();
    }
    LoadModelScrollerValue(0);
    //
}

void UOnBoardingPanel::ScrollOnClick(int value)
{

    UE_LOG(LogTemp, Display, TEXT("BROADCASTED---->> Value------>>%d"), value);
    FVector2D itemWidth = ScrollBox_166->GetDesiredSize();
    //   int32 NumItems = MyItems.Num();
    float ItemaWidth = itemWidth.X / 5;

    float scrollOffset = ItemaWidth * value;
    UE_LOG(LogTemp, Display, TEXT("The WIDTH--->Value------>>%d"), scrollOffset);
    // UE_LOG(LogTemp, Display, TEXT("SetScrollOffset--->Value------>>%d"),ScrollBox_166->GetScrollOffset());
    ScrollBox_166->SetScrollOffset(scrollOffset);

    // float sb = ScrollBox_166->GetScrollOffset();

    // if (value == 4)
    //   {
    // FVector2D itemWidth2 = ScrollBox_166->GetDesiredSize();
    // //   int32 NumItems = MyItems.Num();
    // float ItemaWidth2 = itemWidth2.X / 5;
    // UE_LOG(LogTemp, Display, TEXT("The WIDTH--->Value---4--->>%d"), ItemaWidth2);
    // float scrollOffset2 = ItemaWidth2 / value;
    // UE_LOG(LogTemp, Display, TEXT("SetScrollOffset--->Value---4--->>%d"),ScrollBox_166->GetScrollOffset());
    // ScrollBox_166->SetScrollOffset(scrollOffset2);
    // }

    // float off =
}
void UOnBoardingPanel::OnBoardingScreenOrientation(bool isLandscape)
{
    if (isLandscape)
    {
        // BottomButtonVerticalBox RenderTransform(0,193)

        // BottomScrollerVerticalBox SetAchor(0,0,1,1)
        // BottomScrollerVerticalBox SetOffset(0,490,0,0)
        // BottomScrollerVerticalBox RenderTransfrom Translation(0,-242)

        // BottomPanelSizeBox MinDesiredheight(1300)
        //   BottomPanelSizeBox Slot Padding(850,0,0,0)

        UVerticalBoxSlot *TopTextSizeBoxSlot = Cast<UVerticalBoxSlot>(TopTextSizeBox->Slot);
        TopTextSizeBoxSlot->SetPadding(FMargin(890.0f, 0.0f, 0.0f, 0.0f));

        UVerticalBoxSlot *BottomPanelSizeBoxSlot = Cast<UVerticalBoxSlot>(BottomPanelSizeBox->Slot);
        BottomPanelSizeBoxSlot->SetPadding(FMargin(850.0f, 0.0f, 0.0f, 0.0f));
        BottomPanelSizeBox->bOverride_MinDesiredHeight = true;
        BottomPanelSizeBox->SetMinDesiredHeight(1300.0f);

        //   USizeBoxSlot* SizeBoxSlot = Cast<USizeBoxSlot>(BottomPanelSizeBox);
        UCanvasPanelSlot *Canvas = Cast<UCanvasPanelSlot>(BottomScrollerVerticalBox->Slot);
        Canvas->SetAnchors(FAnchors(0.0f, 0.0f, 1.0f, 1.0f));
        Canvas->SetOffsets(FMargin(0.0f, 490.0f, 0.0f, 0.0f));
        FWidgetTransform Transform;
        Transform.Translation.X = 0.0f;
        Transform.Translation.Y = -242.0f;
        Transform.Scale = FVector2D(1, 1);
        Transform.Angle = 0.0f;
        // FullBodyButtonsTopPanel->SetRenderTransform(Transform);
        BottomScrollerVerticalBox->SetRenderTransform(Transform);

        FWidgetTransform ButtonTransform;
        ButtonTransform.Translation.X = 0.0f;
        ButtonTransform.Translation.Y = 193.0f;
        ButtonTransform.Scale = FVector2D(1, 1);
        ButtonTransform.Angle = 0.0f;
        BottomButtonVerticalBox->SetRenderTransform(ButtonTransform);
    }
    else
    {
        UVerticalBoxSlot *TopTextSizeBoxSlot = Cast<UVerticalBoxSlot>(TopTextSizeBox->Slot);
        TopTextSizeBoxSlot->SetPadding(FMargin(0.0f, 0.0f, 0.0f, 0.0f));

        UVerticalBoxSlot *BottomPanelSizeBoxSlot = Cast<UVerticalBoxSlot>(BottomPanelSizeBox->Slot);
        BottomPanelSizeBoxSlot->SetPadding(FMargin(0.0f, 0.0f, 0.0f, 0.0f));
        BottomPanelSizeBox->bOverride_MinDesiredHeight = true;
        BottomPanelSizeBox->SetMinDesiredHeight(500.0f);

        UCanvasPanelSlot *Canvas = Cast<UCanvasPanelSlot>(BottomScrollerVerticalBox->Slot);
        Canvas->SetAnchors(FAnchors(0.0f, 0.0f, 1.0f, 1.0f));
        Canvas->SetOffsets(FMargin(0.0f, 0.0f, 0.0f, 0.0f));
        FWidgetTransform Transform;
        Transform.Translation.X = 0.0f;
        Transform.Translation.Y = 0.0f;
        Transform.Scale = FVector2D(1, 1);
        Transform.Angle = 0.0f;
        // FullBodyButtonsTopPanel->SetRenderTransform(Transform);
        BottomScrollerVerticalBox->SetRenderTransform(Transform);

        FWidgetTransform ButtonTransform;
        ButtonTransform.Translation.X = 0.0f;
        ButtonTransform.Translation.Y = 0.0f;
        ButtonTransform.Scale = FVector2D(1, 1);
        ButtonTransform.Angle = 0.0f;
        BottomButtonVerticalBox->SetRenderTransform(ButtonTransform);
    }
}
void UOnBoardingPanel::MaleGenderSelected()
{
    UE_LOG(LogTemp, Warning, TEXT("GENDER BUTTON IS CLICKED---: MALE"));
    OnClickMaleFemaleButton(EGender::MALE);
}
void UOnBoardingPanel::FemaleGenderSelected()
{
    UE_LOG(LogTemp, Warning, TEXT("GENDER BUTTON IS CLICKED---: FEMALE"));
    OnClickMaleFemaleButton(EGender::FEMALE);
}

void UOnBoardingPanel::OnClickMaleFemaleButton(EGender gender)
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
        // Check if AttachedActor is a child actor you are interested in
        if (AttachedActor)
        {
            // UE_LOG(LogTemp, Display, TEXT("On--SpawnedOnBoardingParent--->Child------>%s"),*AttachedActor->GetActorLabel());
            AttachedActor->Destroy();
        }
    }
    m_SpawnedModels.Empty();
    APIEvents->isCustomize = true;
    UserDetailHolder->UserDetails.Gender = gender;
    // AvatarLoader->LoadHeadModel();
    SelectGenderPanel->SetVisibility(ESlateVisibility::Hidden);

    APIEvents->ShowPanel(EUIPanels::CUSTOMIZEHEAD, true);
    APIEvents->OnChangeCamera.Broadcast(CameraPanels::CustomizeAvatar_Head);
    AvatarHandler->customizeAvatarLoader->LoadStartData();
    if (AvatarHandler->CustomizeDefaultAvatarLoader->spawnedHeadActor == nullptr)
    {
        AvatarHandler->CustomizeDefaultAvatarLoader->LoadHeadModel([this]
                                                                   {
            APIEvents->HideLoading();
            APIEvents->ShowLoading();
            AvatarHandler->LoadInventoryPropDetail([this]
            {
                APIEvents->HideLoading();
                ResetData();
                AvatarHandler->CustomizeDefaultAvatarLoader->ResetToDefault([this]
                {
                    // AvatarHandler->CustomizeDefaultAvatarLoader->LoadDefaultModels();
                    APIEvents->OnResetToDefault.ExecuteIfBound([this]
                    {
                        UE_LOG(LogTemp, Display, TEXT("On--OnResetToDefault--->EXECUTED---spawnedHeadActor--PRESENT->"));
                    });

                });
            }); });

        AvatarHandler->ForCustomizeAvatar->LoadHeadModel([this]
                                                         { AvatarHandler->ForCustomizeAvatar->ResetToDefault([this]
                                                                                                             { UE_LOG(LogTemp, Display, TEXT("On--OnResetToDefault--->EXECUTED---ForCustomizeAvatar--PRESENT->")); }); });
    }
    else
    {
        APIEvents->ShowLoading();
        AvatarHandler->LoadInventoryPropDetail([this]
                                               {
            APIEvents->HideLoading();
            ResetData();
            AvatarHandler->CustomizeDefaultAvatarLoader->ResetToDefault([this]
            {
                // if(AvatarHandler->CustomizeDefaultAvatarLoader->count >= 4)
                // {
                //     APIEvents->OnResetToDefault.ExecuteIfBound([this]{
                //     UE_LOG(LogTemp, Display, TEXT("On--OnResetToDefault--->EXECUTED---spawnedHeadActor--PRESENT->"));
                //     });
                // }
            }); });
        AvatarHandler->ForCustomizeAvatar->ResetToDefault([this]
                                                          { UE_LOG(LogTemp, Display, TEXT("On--OnResetToDefault--->EXECUTED---ForCustomizeAvatar--PRESENT->")); });
    }

    this->SetVisibility(ESlateVisibility::Hidden);
}
void UOnBoardingPanel::ResetData()
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