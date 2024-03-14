// Fill out your copyright notice in the Description page of Project Settings.
#include "CommonFunction.h"
#include "Kismet/GameplayStatics.h"
#include "UserItemManagementAPI/UserItemManagementRequest.h"
#include "UserItemManagementAPI/UserItemManagementHandler.h"
#include "UserItemManagementAPI/UserItemManagementModels.h"
#include "UserAccountManagementAPI/UserAccountManagementHandler.h"
#include "UserAccountManagementAPI/UserAccountManagementModels.h"
#include "UserAccountManagementAPI/UserAccountManagementRequest.h"
#include "UserAccountManagementAPI/UserAccountManagementAPI.h"
#include "DefaultAPI/DefaultHandler.h"
#include "GameStructs.h"
#include "JsonObjectConverter.h"
// Sets default values
ACommonFunction::ACommonFunction()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACommonFunction::BeginPlay()
{
    Super::BeginPlay();

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
    }

    // CallFun([this](FString id){
    //       UE_LOG(LogTemp, Warning, TEXT("Source retrieved (lambda)1%s"),*id);
    // });

    // SyncAvatar("Android",[this]{
    //      UE_LOG(LogTemp, Warning, TEXT("SyncAvatar retrieved (lambda)1%s"));
    // });

    //  CommonFunctionHolder->UpdateDefaultAvatarID(avatarid ,[this]{
    //      APIEvents->HideLoading();
    // UE_LOG(LogTemp, Display, TEXT("On--UpdateDefaultAvatarID--->Response------>%s"));
    // });
}

// Called every frame
void ACommonFunction::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

EPlatform ACommonFunction::GetPlatform()
{
    EPlatform PlatformName = EPlatform::Android;

#if PLATFORM_ANDROID
    PlatformName = EPlatform::Android;
#endif

#if PLATFORM_IOS
    PlatformName = EPlatform::iOS;
#endif

    return PlatformName;
}

FString ACommonFunction::GetPlatformAsString()
{
    EPlatform Platform = GetPlatform();
    FString PlatformString;

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
int32 ACommonFunction::GetPlatformAsInt()
{
    int32 PlatformValue = 0; // Default value for Android or any other platform

#if PLATFORM_ANDROID
    PlatformValue = 1; // Set to 1 for Android
#endif

#if PLATFORM_IOS
    PlatformValue = 2; // Set to 2 for iOS
#endif

    return PlatformValue;
}

void ACommonFunction::SetCurrentAvatarDetail()
{
    AvatarCurrentChangesHolder = Cast<ACurrentAvatarChanges>(UGameplayStatics::GetActorOfClass(GetWorld(), ACurrentAvatarChanges::StaticClass()));
    UE_LOG(LogTemp, Display, TEXT("On--SetCurrentAvatarDetail------>"));
    // AUserDetailHolder*  UserDetailHolderInstance = Cast<AUserDetailHolder>(UGameplayStatics::GetActorOfClass(GetWorld(), AUserDetailHolder::StaticClass()))
    if (AvatarCurrentChangesHolder == nullptr)
    {
        AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), ACurrentAvatarChanges::StaticClass());
        AvatarCurrentChangesHolder = Cast<ACurrentAvatarChanges>(FoundActor);
        UE_LOG(LogTemp, Display, TEXT("--AvatarCurrentChangesHolder------>"));
        if (AvatarCurrentChangesHolder != nullptr)
        {
            UE_LOG(LogTemp, Display, TEXT("--AvatarCurrentChangesHolder---FOUND--->"));
            AvatarCurrentChangesHolder = GetWorld()->SpawnActor<ACurrentAvatarChanges>();
        }
    }
    if (UserDetailHolder == nullptr)
    {
        AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AUserDetailHolder::StaticClass());
        UserDetailHolder = Cast<AUserDetailHolder>(FoundActor);
        // if(UserDetailHolder == nullptr)
        // {
        //     UserDetailHolder = GetWorld()->SpawnActor<AUserDetailHolder>();
        // }
    }
    if (AvatarCurrentChangesHolder)
    {
        UE_LOG(LogTemp, Display, TEXT("On--CommonFunction--->AvatarCurrentChangesHolder------>"));
        AvatarCurrentChangesHolder->currentProps = FProps();
        AvatarCurrentChangesHolder->changedProps = FProps();
        AvatarCurrentChangesHolder->changeBlendShapes = TArray<FBlendShapeValue>();
        AvatarCurrentChangesHolder->currentBlendShapes = TArray<FBlendShapeValue>();

        for (FProp item : UserDetailHolder->UserDetails.currentUserSelectedAvatar.AvatarData.BucketData)
        {
           UE_LOG(LogTemp, Display, TEXT("On--CommonFunction--->currentUserSelectedAvatar---Adding prop Data--->"));
            FProp tempItem;
            tempItem.CoreBucket = item.CoreBucket;
            tempItem.ID = item.ID;

            AvatarCurrentChangesHolder->changedProps.props.Add(tempItem);
            AvatarCurrentChangesHolder->currentProps.props.Add(tempItem);
        }

        for (FBlendShapeValue item : UserDetailHolder->UserDetails.currentUserSelectedAvatar.AvatarData.Blendshapes)
        {
              UE_LOG(LogTemp, Display, TEXT("On--CommonFunction--->currentUserSelectedAvatar---Adding Blendshape Data--->"));
            AvatarCurrentChangesHolder->changeBlendShapes.Add(item);
            AvatarCurrentChangesHolder->currentBlendShapes.Add(item);
        }

        FString hairColor = UserDetailHolder->UserDetails.currentUserSelectedAvatar.AvatarData.ColorMeta.HairColor;
        FString eyebrowcolor = UserDetailHolder->UserDetails.currentUserSelectedAvatar.AvatarData.ColorMeta.EyebrowColor;
        FString facialhaircolor = UserDetailHolder->UserDetails.currentUserSelectedAvatar.AvatarData.ColorMeta.FacialHairColor;
        FString lipcolor = UserDetailHolder->UserDetails.currentUserSelectedAvatar.AvatarData.ColorMeta.LipColor;

        AvatarCurrentChangesHolder->changePropColors.HairColor = AvatarCurrentChangesHolder->currentpropColors.HairColor = hairColor;
        AvatarCurrentChangesHolder->changePropColors.EyebrowColor = AvatarCurrentChangesHolder->currentpropColors.EyebrowColor = eyebrowcolor;
        AvatarCurrentChangesHolder->changePropColors.FacialHairColor = AvatarCurrentChangesHolder->currentpropColors.FacialHairColor = facialhaircolor;
        AvatarCurrentChangesHolder->changePropColors.LipColor = AvatarCurrentChangesHolder->currentpropColors.LipColor = lipcolor;
    }
}

void ACommonFunction::UpdateDefaultAvatarID(FString AvatarID)
{
    FUpdateDefaultAvatarIDRequest request;
    request.DefaultAvatarID = AvatarID;
    UE_LOG(LogTemp, Display, TEXT("On--CommonFunction--->UpdateDefaultAvatarID------>"));
    UDefaultHandler::UpdateDefaultAvatarID(request, UpdateDefaultAvatarIDResult, UpdateDefaultAvatarIDError);
}

void ACommonFunction::CheckAvatarDifference()
{
    if (AvatarCurrentChangesHolder)
    {
        if (AvatarCurrentChangesHolder->currentpropColors.EyebrowColor != AvatarCurrentChangesHolder->changePropColors.EyebrowColor)
        {
            isSameModels = false;
            //  OnComplete.ExecuteIfBound(isSameModels);
            // OnComplete.Broadcast(isSameModels);
            return;
        }
        if (AvatarCurrentChangesHolder->currentpropColors.FacialHairColor != AvatarCurrentChangesHolder->changePropColors.FacialHairColor)
        {
            isSameModels = false;
            // OnComplete.ExecuteIfBound(isSameModels);
            // OnComplete.Broadcast(isSameModels);
            return;
        }
        if (AvatarCurrentChangesHolder->currentpropColors.HairColor != AvatarCurrentChangesHolder->changePropColors.HairColor)
        {
            isSameModels = false;
            // OnComplete.ExecuteIfBound(isSameModels);
            // OnComplete.Broadcast(isSameModels);

            return;
        }
        if (AvatarCurrentChangesHolder->currentpropColors.LipColor != AvatarCurrentChangesHolder->changePropColors.LipColor)
        {
            isSameModels = false;
            // OnComplete.ExecuteIfBound(isSameModels);
            //    OnComplete.Broadcast(isSameModels);
            return;
        }
        if (AvatarCurrentChangesHolder->currentProps.props.Num() != AvatarCurrentChangesHolder->changedProps.props.Num())
        {
            isSameModels = false;
            // OnComplete.ExecuteIfBound(isSameModels);
            // OnComplete.Broadcast(isSameModels);
            return;
        }
        else
        {
            for (int i = 0; i < AvatarCurrentChangesHolder->changedProps.props.Num(); i++)
            {
                FString id = AvatarCurrentChangesHolder->changedProps.props[i].ID;
                if (!AvatarCurrentChangesHolder->isPresentInCurrent(id))
                {
                    isSameModels = false;
                    // OnComplete.ExecuteIfBound(isSameModels);
                    // OnComplete.Broadcast(isSameModels);
                    break;
                }
            }
            if (isSameModels)
            {
                // OnComplete.ExecuteIfBound(isSameModels);
                // OnComplete.Broadcast(isSameModels);
                return;
            }
        }
        if (AvatarCurrentChangesHolder->currentBlendShapes.Num() != AvatarCurrentChangesHolder->changeBlendShapes.Num())
        {
            isSameModels = false;
            // OnComplete.ExecuteIfBound(isSameModels);
            // OnComplete.Broadcast(isSameModels);
            return;
        }
        else
        {
            for (int i = 0; i < AvatarCurrentChangesHolder->changeBlendShapes.Num(); i++)
            {
                if (AvatarCurrentChangesHolder->isPresentInCurrentShape(AvatarCurrentChangesHolder->changeBlendShapes[i]))
                {
                    isSameModels = false;
                    // OnComplete.ExecuteIfBound(isSameModels);
                    // OnComplete.Broadcast(isSameModels);
                    break;
                }
            }
            if (isSameModels)
            {
                // OnComplete.ExecuteIfBound(isSameModels);
                // OnComplete.Broadcast(isSameModels);
                return;
            }
        }
    }
}
void ACommonFunction::CheckAvatarDifference(TFunction<void(bool)> OnComplete)
{
    if (AvatarCurrentChangesHolder)
    {
        if (AvatarCurrentChangesHolder->currentpropColors.EyebrowColor != AvatarCurrentChangesHolder->changePropColors.EyebrowColor)
        {
            isSameModels = false;
            //  OnComplete.ExecuteIfBound(isSameModels);
            // OnComplete.Broadcast(isSameModels);
            OnComplete(isSameModels);
            return;
        }
        if (AvatarCurrentChangesHolder->currentpropColors.FacialHairColor != AvatarCurrentChangesHolder->changePropColors.FacialHairColor)
        {
            isSameModels = false;
            OnComplete(isSameModels);
            // OnComplete.ExecuteIfBound(isSameModels);
            // OnComplete.Broadcast(isSameModels);
            return;
        }
        if (AvatarCurrentChangesHolder->currentpropColors.HairColor != AvatarCurrentChangesHolder->changePropColors.HairColor)
        {
            isSameModels = false;
            OnComplete(isSameModels);
            // OnComplete.ExecuteIfBound(isSameModels);
            // OnComplete.Broadcast(isSameModels);

            return;
        }
        if (AvatarCurrentChangesHolder->currentpropColors.LipColor != AvatarCurrentChangesHolder->changePropColors.LipColor)
        {
            isSameModels = false;
            OnComplete(isSameModels);
            // OnComplete.ExecuteIfBound(isSameModels);
            //    OnComplete.Broadcast(isSameModels);
            return;
        }
        if (AvatarCurrentChangesHolder->currentProps.props.Num() != AvatarCurrentChangesHolder->changedProps.props.Num())
        {
            isSameModels = false;
            OnComplete(isSameModels);
            // OnComplete.ExecuteIfBound(isSameModels);
            // OnComplete.Broadcast(isSameModels);
            return;
        }
        else
        {
            for (int i = 0; i < AvatarCurrentChangesHolder->changedProps.props.Num(); i++)
            {
                FString id = AvatarCurrentChangesHolder->changedProps.props[i].ID;
                if (!AvatarCurrentChangesHolder->isPresentInCurrent(id))
                {
                    isSameModels = false;
                    OnComplete(isSameModels);
                    // OnComplete.ExecuteIfBound(isSameModels);
                    // OnComplete.Broadcast(isSameModels);
                    break;
                }
            }
            if (isSameModels)
            {
                OnComplete(isSameModels);
                // OnComplete.ExecuteIfBound(isSameModels);
                // OnComplete.Broadcast(isSameModels);
                return;
            }
        }
        if (AvatarCurrentChangesHolder->currentBlendShapes.Num() != AvatarCurrentChangesHolder->changeBlendShapes.Num())
        {
            isSameModels = false;
            // OnComplete.ExecuteIfBound(isSameModels);
            // OnComplete.Broadcast(isSameModels);
            OnComplete(isSameModels);
            return;
        }
        else
        {
            for (int i = 0; i < AvatarCurrentChangesHolder->changeBlendShapes.Num(); i++)
            {
                if (AvatarCurrentChangesHolder->isPresentInCurrentShape(AvatarCurrentChangesHolder->changeBlendShapes[i]))
                {
                    isSameModels = false;
                    OnComplete(isSameModels);
                    // OnComplete.ExecuteIfBound(isSameModels);
                    // OnComplete.Broadcast(isSameModels);
                    break;
                }
            }
            if (isSameModels)
            {
                // OnComplete.ExecuteIfBound(isSameModels);
                // OnComplete.Broadcast(isSameModels);
                OnComplete(isSameModels);
                return;
            }
        }
    }
}

void ACommonFunction::SyncAvatar(FString platform, TFunction<void()> OnComplete)
{
    FSyncAvatarsRequest request;
    request.Mesh = true;
    request.Image = true;
    request.Platform = platform;

    UDefaultHandler::SyncAvatar(
        request, [this, OnComplete](FString result)
        {
        UE_LOG(LogTemp, Display, TEXT("GET--SyncAvatar--->Response------>%s"), *result);
        if(APIEvents)
        {
            APIEvents->HideLoading();
        }
        OnComplete(); },
        [this](FApiException error)
        {
            UE_LOG(LogTemp, Display, TEXT("GET--SyncAvatar--->Error------>"));
            if (APIEvents)
            {
                APIEvents->HideLoading();
            }
        });
}

void ACommonFunction::UpdateDefaultAvatarID(FString avatarid, TFunction<void()> Callback)
{
    FUpdateDefaultAvatarIDRequest request;
    request.DefaultAvatarID = avatarid;
UserDetailHolder->UserDetails.DefaultAvatarID = avatarid;
    UDefaultHandler::UpdateDefaultAvatarID(
        request, [this, Callback](FUpdateDefaultAvatarIDResult result)
        {
        UE_LOG(LogTemp, Display, TEXT("GET--UpdateDefaultAvatarID--->Response------>%s"), *result.Status);
        Callback(); },
        [this](FApiException error)
        {
            UE_LOG(LogTemp, Display, TEXT("GET--UpdateDefaultAvatarID--->Error------>"));
        });
}

void ACommonFunction::GetCommonUserInventory(TFunction<void()> InventoryLoaded)
{
    FString userid = UserDetailHolder->UserDetails.userID;

    UUserItemManagementHandler::GetUserInventoryCall(
        UserDetailHolder->UserDetails.userID, [this, InventoryLoaded](FGetUserInventoryResult result)
        {
        UserInventoryHolder->Inventory.Empty(); 
        UserInventoryHolder->AddUserInventory(result.Data);
        // Call the InventoryLoaded callback after successful response
        if (InventoryLoaded)
        {
            InventoryLoaded();
        } },
        [this](FApiException error)
        {
            UE_LOG(LogTemp, Display, TEXT("GET--UserInventory--->Error------>"));
        });
}

void ACommonFunction::GetUserAccountInfo(TFunction<void()> OnComplete)
{
    UUserAccountManagementAPI::GetUserAccountInfo(
        UserDetailHolder->UserDetails.userID, [this, OnComplete](FGetUserAccountInfoResult result)
        {
            UE_LOG(LogTemp, Display, TEXT("GET---COMMONFUNCTION---GetUserAccountInfo--->OnComplete------>%s"), *result.Status);
            FWallets Wallets;
            FString ResponseString = "{";
            ResponseString.Append("\"wallets\":");
            ResponseString.Append(result.Data.Wallet);
            ResponseString.Append("}");
            FJsonObjectConverter::JsonObjectStringToUStruct(ResponseString, &Wallets,0,0);
            UserDetailHolder->UserDetails.wallets = Wallets;
            UserDetailHolder->UserDetails.Loacation = result.Data.Location;
            UserDetailHolder->UserDetails.DefaultAvatarID = result.Data.DefaultAvatarID;
            OnComplete(); },
        [this](FApiException error)
        {
            UE_LOG(LogTemp, Display, TEXT("GET---COMMONFUNCTION---GetUserAccountInfo--->Error------>"));
        });
}

void ACommonFunction::GetUserAccountInfo(TFunction<void(FGetUserAccountInfoResult)> OnComplete)
{
    //   UUserAccountManagementAPI::GetUserAccountInfo(UserDetailHolder->UserDetails.userID, OnGetUserAccountInfoResult, OnGetUserAccountInfoError);
    UUserAccountManagementAPI::GetUserAccountInfo(
        UserDetailHolder->UserDetails.userID, [this, OnComplete](FGetUserAccountInfoResult result)
        {
            UE_LOG(LogTemp, Display, TEXT("GET---COMMONFUNCTION---GetUserAccountInfo--->Response------>%s"), *result.Data.Wallet);
            FWallets Wallets;
            FString ResponseString = "{";
            ResponseString.Append("\"wallets\":");
            ResponseString.Append(result.Data.Wallet);
            ResponseString.Append("}");
            FJsonObjectConverter::JsonObjectStringToUStruct(ResponseString, &Wallets,0,0);
            UserDetailHolder->UserDetails.wallets = Wallets;
            UserDetailHolder->UserDetails.Loacation = result.Data.Location;
            UserDetailHolder->UserDetails.DefaultAvatarID = result.Data.DefaultAvatarID;

            for (int i = 0; i < UserDetailHolder->UserDetails.userAvatars.Num(); i++)
            {
                if (UserDetailHolder->UserDetails.userAvatars[i].AvatarID == result.Data.DefaultAvatarID)
                {
                    UserDetailHolder->UserDetails.currentUserSelectedAvatar = UserDetailHolder->UserDetails.userAvatars[i];
                }
            }
            OnComplete(result); },
        [this](FApiException error)
        {
            UE_LOG(LogTemp, Display, TEXT("GET---COMMONFUNCTION---GetUserAccountInfo--->Error------>"));
        });
}

void ACommonFunction::GetUserAllAvatars(TFunction<void()> OnComplete)
{
    UUserAccountManagementHandler::GetUsersAllAvatars(
        UserDetailHolder->UserDetails.userID, [this, OnComplete](FGetUsersAllAvatarsResult result)
        {
        UE_LOG(LogTemp, Display, TEXT("GET--GetUsersAllAvatars--->Response------> %s"),*result.Status);
        if (result.Data.Num() > 0)
        {
            UserDetailHolder->UserDetails.userAvatars.Empty();
            for (int i = 0; i < result.Data.Num(); i++)
            {
                FUserAvatar uservatar = FUserAvatar();
                uservatar.AvatarID = result.Data[i].AvatarID;
                FAvatarUrlDataList avatarurls;
                FString avatarurlstring = "{";
                avatarurlstring.Append("\"AvatarUrls\":");
                avatarurlstring.Append(result.Data[i].AvatarUrl);
                avatarurlstring.Append("}");
                FJsonObjectConverter::JsonObjectStringToUStruct(avatarurlstring, &avatarurls,0,0);
                uservatar.AvatarUrls = avatarurls.AvatarUrls;

                FAvatarThumbDataList thumburls;
                FString thumburlstring = "{";
                thumburlstring.Append("\"ThumbUrls\":");
                thumburlstring.Append(result.Data[i].ThumbUrl);
                thumburlstring.Append("}");
                FJsonObjectConverter::JsonObjectStringToUStruct(thumburlstring, &thumburls,0,0);
                uservatar.ThumbUrls = thumburls.ThumbUrls;
                uservatar.AvatarID = result.Data[i].AvatarID;
        
                FAvatarData avatarData;
                FJsonObjectConverter::JsonObjectStringToUStruct(result.Data[i].AvatarData, &avatarData,0,0);
                uservatar.AvatarData = avatarData;

                UserDetailHolder->UserDetails.userAvatars.Add(uservatar);
                if (result.Data[i].AvatarID == UserDetailHolder->UserDetails.DefaultAvatarID)
                {
                    UE_LOG(LogTemp, Display, TEXT("SAME AVATAR ID------------>"));
                    UserDetailHolder->UserDetails.currentUserSelectedAvatar = uservatar;
                    UserDetailHolder->UserDetails.Gender = UserDetailHolder->UserDetails.currentUserSelectedAvatar.AvatarData.Gender == 1 ? EGender::FEMALE : EGender::MALE;
           
                }
            }
            if(APIEvents)
            {
                APIEvents->HideLoading();
            }
             OnComplete();
            
        }
        else
        {
            if(APIEvents)
            {
                 UE_LOG(LogTemp, Display, TEXT("GET--GetUsersAllAvatars--->Response---Else---> %s"),*result.Status);
                APIEvents->HideLoading();
            }
            OnComplete();
        } },
        [this](FApiException error)
        {
            UE_LOG(LogTemp, Display, TEXT("GET--GetUsersAllAvatars--->Error------> %s"), *error.ErrorMessage);
        });
}

void ACommonFunction::GetUserAllAvatars(TFunction<void(FGetUsersAllAvatarsResult)> OnComplete)
{

    UUserAccountManagementHandler::GetUsersAllAvatars(
        UserDetailHolder->UserDetails.userID, [this, OnComplete](FGetUsersAllAvatarsResult result)
        {
        
        if (result.Data.Num() > 0)
        {
            UserDetailHolder->UserDetails.userAvatars.Empty();
            for (int i = 0; i < result.Data.Num(); i++)
            {
             
                FUserAvatar uservatar = FUserAvatar();
                uservatar.AvatarID = result.Data[i].AvatarID;
                FAvatarUrlDataList avatarurls;
                FString avatarurlstring = "{";
                avatarurlstring.Append("\"AvatarUrls\":");
                avatarurlstring.Append(result.Data[i].AvatarUrl);
                avatarurlstring.Append("}");
                   UE_LOG(LogTemp, Display, TEXT(">>>>>>>>>>>>>>>>>  %s"),*avatarurlstring);
                FJsonObjectConverter::JsonObjectStringToUStruct(avatarurlstring, &avatarurls,0,0);
                uservatar.AvatarUrls = avatarurls.AvatarUrls;

                FAvatarThumbDataList thumburls;
                FString thumburlstring = "{";
                thumburlstring.Append("\"ThumbUrls\":");
                thumburlstring.Append(result.Data[i].ThumbUrl);
                thumburlstring.Append("}");
                FJsonObjectConverter::JsonObjectStringToUStruct(thumburlstring, &thumburls,0,0);
                uservatar.ThumbUrls = thumburls.ThumbUrls;
                uservatar.AvatarID = result.Data[i].AvatarID;

                FAvatarData avatarData;
                FJsonObjectConverter::JsonObjectStringToUStruct(result.Data[i].AvatarData, &avatarData,0,0);
                uservatar.AvatarData = avatarData;

                UserDetailHolder->UserDetails.userAvatars.Add(uservatar);
                if (result.Data[i].AvatarID == UserDetailHolder->UserDetails.DefaultAvatarID)
                {
                    UserDetailHolder->UserDetails.currentUserSelectedAvatar = uservatar;
                  
                }
            }
            UserDetailHolder->UserDetails.Gender = UserDetailHolder->UserDetails.currentUserSelectedAvatar.AvatarData.Gender == 1 ? EGender::FEMALE : EGender::MALE;
            OnComplete(result);
        }
        else
        {
            OnComplete(result);
        } },
        [this](FApiException error)
        {
            UE_LOG(LogTemp, Display, TEXT("GET--GetUsersAllAvatars--->Error------> %s"), *error.ErrorMessage);
        });
}

void ACommonFunction::RenderImage(FString avatarid, TFunction<void(FRenderAvatarImageResponse)> OnComplete)
{
    FRenderAvatarImageRequest request;
    request.AvatarID = avatarid;
    request.Platform = "Android";

    UDefaultHandler::RenderAvatarImage(
        request, [this, OnComplete](FRenderAvatarImageResponse result)
        { OnComplete(result); },
        [this](FApiException error)
        {
            UE_LOG(LogTemp, Display, TEXT("GET--RenderImage--->Error------> %s"), *error.ErrorMessage);
        });
}

void ACommonFunction::RenderImageBG(FString avatarid)
{
    FRenderAvatarImageRequest request;
    request.AvatarID = avatarid;
    request.Platform = "Android";
    UDefaultHandler::RenderAvatarImage(
        request, [this](FRenderAvatarImageResponse result)
        { GetUserAllAvatars([this]
                            { UE_LOG(LogTemp, Display, TEXT("RenderImageBG---GET--GetUserAllAvatars--->Response------>")); }); },
        [this](FApiException error)
        {
            UE_LOG(LogTemp, Display, TEXT("GET--RenderImage--->Error------> %s"), *error.ErrorMessage);
        });
}

void ACommonFunction::GenerateMesh(FString avatarid, TFunction<void(FGenerateAvatarMeshResponse)> OnComplete)
{
    FGenerateAvatarMeshRequest request;
    request.AvatarID = avatarid;
    request.Platform = "Android";
    UDefaultHandler::GenerateAvatarMesh(
        request, [this, OnComplete](FGenerateAvatarMeshResponse result)
        {
         UE_LOG(LogTemp, Display, TEXT("GET--GenerateMesh--->Response------> %s"),*result.Status);   
         OnComplete(result); },
        [this](FApiException error)
        {
            UE_LOG(LogTemp, Display, TEXT("GET--GenerateMesh--->Error------> %s"), *error.ErrorMessage);
        });
}
int ACommonFunction::CheckMissingThumbnailAndAvatar()
{
    FString PlatformName = GetPlatformAsString();
    int no = 0;
    for (FUserAvatar item : UserDetailHolder->UserDetails.userAvatars)
    {
        if (item.ThumbUrls.Num() > 0)
        {
            if (item.ThumbUrls.FindByPredicate([PlatformName](const FAvatarThumbData &Thumb)
                                               { return Thumb.Platform == PlatformName; }) == nullptr)
            {
                no++;
            }
        }
        else
        {
            no++;
        }
        if (item.AvatarUrls.Num() > 0)
        {
            if (item.AvatarUrls.FindByPredicate([PlatformName](const FAvatarUrlData &Thumb)
                                                { return Thumb.Platform == PlatformName; }) == nullptr)
            {
                no++;
            }
        }
        else
        {
            no++;
        }
    }
    return no;
}
void ACommonFunction::CallFun(TFunction<void(FString)> Callback)
{
    FString userid = "THE ONE NEO";
    Callback(userid);
}
void ACommonFunction::LoadCurrentAvatarData(TFunction<void()> oncomplete) {
  FString avatarid = UserDetailHolder->UserDetails.currentUserSelectedAvatar.AvatarID;
        UAvatarPresetsHandler::GetUserAvatarAllData(avatarid,"Android", [this,oncomplete](FGetUserAvatarAllDataResponse result) {
        AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AEconomyItemHolder::StaticClass());
        AEconomyItemHolder *EconomyItemHolder = 
            Cast<AEconomyItemHolder>(FoundActor);
        EconomyItemHolder->AddEconomyItemDataFromAvatar(result);
    oncomplete();
      },
      [this](FApiException error)
      {
        UE_LOG(LogTemp, Display, TEXT("ON GETECONOMY ERROR--->>%s"),*error.ErrorMessage);
      });
    }