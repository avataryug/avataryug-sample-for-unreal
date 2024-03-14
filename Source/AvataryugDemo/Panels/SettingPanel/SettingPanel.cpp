// Fill out your copyright notice in the Description page of Project Settings.

#include "SettingPanel.h"
#include "CommonModels.h"
#include "UserAccountManagementAPI/UserAccountManagementHandler.h"
#include "Components/EditableTextBox.h"
#include "AuthenticationAPI/AuthenticationHandler.h"
#include "AuthenticationAPI/AuthenticationModels.h"
#include "AuthenticationAPI/AuthenticationRequest.h"
#include "AuthenticationAPI/AuthenticationAPI.h"
#include "DefaultAPI/DefaultHandler.h"
#include "DefaultAPI/DefaultModels.h"
#include "Components/CanvasPanelSlot.h"
#include "DefaultAPI/DefaultAPI.h"
#include "DefaultAPI/DefaultRequest.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void USettingPanel::NativeConstruct()
{
    Super::NativeConstruct();

    Settings_BackButton->OnClicked.RemoveDynamic(this, &USettingPanel::OnClicksettingBackButton);
    Settings_BackButton->OnClicked.AddDynamic(this, &USettingPanel::OnClicksettingBackButton);

    LogoutButton->OnClicked.RemoveDynamic(this, &USettingPanel::OnClickLogout);
    LogoutButton->OnClicked.AddDynamic(this, &USettingPanel::OnClickLogout);

    UpdateDisplayNameButton->OnClicked.RemoveDynamic(this, &USettingPanel::OnClickUpdateDisplayName);
    UpdateDisplayNameButton->OnClicked.AddDynamic(this, &USettingPanel::OnClickUpdateDisplayName);

    ChangePasswordButton->OnClicked.RemoveDynamic(this, &USettingPanel::OnClickChangePassword);
    ChangePasswordButton->OnClicked.AddDynamic(this, &USettingPanel::OnClickChangePassword);

    CloseButtonDisplayName->OnClicked.RemoveDynamic(this, &USettingPanel::OnClickCloseUpdateDisplayName);
    CloseButtonDisplayName->OnClicked.AddDynamic(this, &USettingPanel::OnClickCloseUpdateDisplayName);

    CloseChangepassword_Button->OnClicked.RemoveDynamic(this, &USettingPanel::OnClickCloseChangePassword);
    CloseChangepassword_Button->OnClicked.AddDynamic(this, &USettingPanel::OnClickCloseChangePassword);

    LinkCustomIDButton->OnClicked.RemoveDynamic(this, &USettingPanel::OnClickLinkCustom);
    LinkCustomIDButton->OnClicked.AddDynamic(this, &USettingPanel::OnClickLinkCustom);

    LinkAndroiddeviceIDButton->OnClicked.RemoveDynamic(this, &USettingPanel::OnClickLinkAndrtoidDeviceID);
    LinkAndroiddeviceIDButton->OnClicked.AddDynamic(this, &USettingPanel::OnClickLinkAndrtoidDeviceID);

    LinkIOSDeviceButton->OnClicked.RemoveDynamic(this, &USettingPanel::OnClickLinkIOSDeviceID);
    LinkIOSDeviceButton->OnClicked.AddDynamic(this, &USettingPanel::OnClickLinkIOSDeviceID);

    LinkGoggleButton->OnClicked.RemoveDynamic(this, &USettingPanel::OnClickLinkGoggleAccount);
    LinkGoggleButton->OnClicked.AddDynamic(this, &USettingPanel::OnClickLinkGoggleAccount);

    LinkAppleButton->OnClicked.RemoveDynamic(this, &USettingPanel::OnClickLinkApple);
    LinkAppleButton->OnClicked.AddDynamic(this, &USettingPanel::OnClickLinkApple);

    LinkFaceBookButton->OnClicked.RemoveDynamic(this, &USettingPanel::OnClickLinkFacebookAccount);
    LinkFaceBookButton->OnClicked.AddDynamic(this, &USettingPanel::OnClickLinkFacebookAccount);

    DeleteUserButton->OnClicked.RemoveDynamic(this, &USettingPanel::OnClickDeleteUser);
    DeleteUserButton->OnClicked.AddDynamic(this, &USettingPanel::OnClickDeleteUser);

    AddDisplayNameButton->OnClicked.RemoveDynamic(this, &USettingPanel::OnClickAddDisplayName);
    AddDisplayNameButton->OnClicked.AddDynamic(this, &USettingPanel::OnClickAddDisplayName);

    CP_ChangePasswordButton->OnClicked.RemoveDynamic(this, &USettingPanel::OnClickUpddateEmailPassword);
    CP_ChangePasswordButton->OnClicked.AddDynamic(this, &USettingPanel::OnClickUpddateEmailPassword);

    EnterAddDisplayNameField->OnTextChanged.AddDynamic(this, &USettingPanel::EnterAddDisplayNameTextChanged);

    OnUnlinkCustomIDResult.BindUFunction(this, "UnLinkCustomIDReply");
    OnUnlinkCustomIException.BindUFunction(this, "UnLinkCustomIDError");

    // LoginCustomIDResult.BindUFunction(this, "OnLoginCustomIdReply");
    // CustomIdApiException.BindUFunction(this, "OnLoginCustomIdError");

    UnlinkAndroidDeviceIDResult.BindUFunction(this, "UnlinkAndroidDeviceIDReply");
    UnlinkAndroidDeviceIDApiException.BindUFunction(this, "UnlinkAndroidDeviceIDError");

    // LoginWithAndroidResult.BindUFunction(this, "OnLoginAndroidIDReply");
    // OnLoginWithAndroidIDException.BindUFunction(this, "OnLoginAndroidIDError");

    OnUnlinkIOSDeviceIDResult.BindUFunction(this, "OnUnlinkIOSDeviceIDReply");
    UnlinkIOSDeviceIDApiException.BindUFunction(this, "OnUnlinkIOSDeviceIDError");

    // LoginWithIOSDeviceIDResult.BindUFunction(this, "LoginIOSDeviceIDReply");
    // LoginWithIOSDeviceIDApiException.BindUFunction(this, "OnLoginIOSDeviceIDError");

    LinkWithGoogleResult.BindUFunction(this, "LinkGoggleAccountReply");
    LinkWithGoogleApiException.BindUFunction(this, "LinkGoggleAccountError");

    UnlinkGoogleAccounResult.BindUFunction(this, "UnLinkGoggleAccountReply");
    UnLinkWithGoogleApiException.BindUFunction(this, "UnLinkGoggleAccountError");

    OnLinkAppleResult.BindUFunction(this, "OnLinkAppleReply");
    OnLinkAppleApiException.BindUFunction(this, "OnLinkAppleError");

    UnlinkAppleResult.BindUFunction(this, "UnLinkAppleReply");
    UnlinkAppleResult.BindUFunction(this, "UnlinkAppleError");

    OnLinkFacebookAccountResult.BindUFunction(this, "OnLinkFacebookAccountReply");
    OnLinkFacebookAccountApiException.BindUFunction(this, "OnLinkFacebookAccountError");

    OnUnlinkFacebookAccountResult.BindUFunction(this, "OnUnlinkFacebookAccountReply");
    OnUnlinkFacebookAccountApiException.BindUFunction(this, "OnUnlinkFacebookAccountError");

    OnDeleteUserResponse.BindUFunction(this, "OnDeleteUserReply");
    OnDeleteUserApiException.BindUFunction(this, "OnDeleteUserResponseError");

    OnUpdateUserProjectDisplayNameResult.BindUFunction(this, "OnUpdateUserProjectDisplayNameReply");
    OnUpdateUserProjectDisplayNameApiException.BindUFunction(this, "OnUpdateUserProjectDisplayNameError");

    OnChangePasswordResult.BindUFunction(this, "OnChangePasswordReply");
    OnChangePasswordApiException.BindUFunction(this, "OnChangePasswordError");

    LinkCustomIDResult.BindUFunction(this, "LinkCustomIDReply");
    OnLinkCustomIDApiException.BindUFunction(this, "LinkCustomIDError");

    LinkAndroidDeviceIDResult.BindUFunction(this, "LinkAndroidDeviceIDReply");
    LinkAndroidDeviceIDApiException.BindUFunction(this, "LinkAndroidIDError");

    NewLinkIOSDeviceIDResult.BindUFunction(this, "LinkIOSDeviceIDReply");
    NewLinkIOSDeviceIDApiException.BindUFunction(this, "LinkIOSDeviceIDError");

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
        if (APIEvents)
        {
            APIEvents->OnScreenOrientation.AddDynamic(this, &USettingPanel::OnSettingScreenOrientation);
        }
    }
}

void USettingPanel::OnClickLogout()
{
    FString MapName = "AvataryugSample";
    UWorld *World = GetWorld();
    if (World)
    {
        UGameplayStatics::OpenLevel(World, FName(*MapName), true);
    }
}

void USettingPanel::OnClickUpdateDisplayName()
{
    AddDisplayNamePanel->SetVisibility(ESlateVisibility::Visible);
}

void USettingPanel::OnClickChangePassword()
{
    AddEmailPasswordPanel->SetVisibility(ESlateVisibility::Visible);
}

void USettingPanel::LoadSettingPanelData()
{
    UE_LOG(LogTemp, Display, TEXT("THE ACCOUNTS COUNTS---->>%d"), UserDetailHolder->UserDetails.linkedAcounts.linkedAcounts.Num());
    if (UserDetailHolder->UserDetails.linkedAcounts.linkedAcounts.Num() > 0)
    {
        for (int i = 0; i < UserDetailHolder->UserDetails.linkedAcounts.linkedAcounts.Num(); i++)
        {
            UE_LOG(LogTemp, Display, TEXT("THE LINKED--ACCOUNTS NAMESS---->>%s"), *UserDetailHolder->UserDetails.linkedAcounts.linkedAcounts[i].Platform);

            if (UserDetailHolder->UserDetails.linkedAcounts.linkedAcounts[i].Platform.Contains("Custom"))
            {
                isLoginCustomID = true;
                ChangePasswordButton->SetVisibility(ESlateVisibility::Collapsed);
                LinkCustomText->SetText(FText::FromString("UnLink Custom ID"));
                UE_LOG(LogTemp, Display, TEXT("THE LINKED--CUSTOMID---->>"));
            }
            if (UserDetailHolder->UserDetails.linkedAcounts.linkedAcounts[i].Platform.Contains("Android"))
            {
                isAndroidDeviceID = true;
                LinkAndroidDeviceText->SetText(FText::FromString("UnLink Android Device ID"));
                UE_LOG(LogTemp, Display, TEXT("THE LINKED--Android---->>"));
            }
            if (UserDetailHolder->UserDetails.linkedAcounts.linkedAcounts[i].Platform.Contains("Google"))
            {
                isLinkedGoggle = true;
                LinkGoggleText->SetText(FText::FromString("UnLink Goggle Account"));
                UE_LOG(LogTemp, Display, TEXT("THE LINKED--Google---->>"));
            }
            if (UserDetailHolder->UserDetails.linkedAcounts.linkedAcounts[i].Platform.Contains("Email"))
            {
                ChangePasswordButton->SetVisibility(ESlateVisibility::Visible);
                UE_LOG(LogTemp, Display, TEXT("THE LINKED--Email---->>"));
            }
            if (UserDetailHolder->UserDetails.linkedAcounts.linkedAcounts[i].Platform.Contains("Facebook"))
            {
                isFacebookLogin = true;
                LinkFBText->SetText(FText::FromString("UnLink Facebook Account"));
                UE_LOG(LogTemp, Display, TEXT("THE LINKED--Facebook---->>"));
            }

            if (UserDetailHolder->UserDetails.linkedAcounts.linkedAcounts[i].Platform.Contains("Apple"))
            {
                isLinkApple = true;
                LinkAppleText->SetText(FText::FromString("UnLink Apple"));
                UE_LOG(LogTemp, Display, TEXT("THE LINKED--Apple---->>"));
            }

            if (UserDetailHolder->UserDetails.linkedAcounts.linkedAcounts[i].Platform.Contains("IOS Device"))
            {
                isLinkIOSDeviceID = true;
                LinkIOSText->SetText(FText::FromString("UnLink IOS Device ID"));
                UE_LOG(LogTemp, Display, TEXT("THE LINKED--IOS---->>"));
            }
        }
    }
}

void USettingPanel::OnClickCloseUpdateDisplayName()
{
    AddDisplayNamePanel->SetVisibility(ESlateVisibility::Hidden);
}

void USettingPanel::OnClickCloseChangePassword()
{
    AddEmailPasswordPanel->SetVisibility(ESlateVisibility::Hidden);
}
//=================== LINK/UNLINK CUSTOM ID===========================
void USettingPanel::OnClickLinkCustom()
{
    UE_LOG(LogTemp, Display, TEXT("Clicked On CUSTOmID---->>"))
    APIEvents->ShowLoading();
    if (isLoginCustomID)
    {

        UE_LOG(LogTemp, Display, TEXT("Clicked On CUSTOmID222---222->>"))
        UUserAccountManagementHandler::UnlinkCustomID(OnUnlinkCustomIDResult, OnUnlinkCustomIException);
    }
    else
    {
        APIEvents->ShowLoading();
        // FLoginWithCustomIDRequest request;
        // request.CustomID = "CustomID2457";
        // request.CreateAccount = true;
        // UAuthenticationHandler::LoginWithCustomId(request, LoginCustomIDResult, CustomIdApiException);

        FLinkCustomIDRequest request;
        request.ForceLink = true;
        request.CustomID = "Abcd";

        UUserAccountManagementHandler::LinkCustomID(request, LinkCustomIDResult, OnLinkCustomIDApiException);
    }
}
void USettingPanel::OnClicksettingBackButton()
{
    this->SetVisibility(ESlateVisibility::Hidden);
    if (APIEvents != nullptr)
    {
        APIEvents->ShowPanel(EUIPanels::HOME, true);
    }
}
void USettingPanel::LinkCustomIDReply(FLinkCustomIDResult result)
{
    UE_LOG(LogTemp, Display, TEXT("OnLinkWithCustomIdReply ----->>%s"), *result.Message);
    isLoginCustomID = true;
    LinkCustomText->SetText(FText::FromString("UnLink Custom ID"));
    APIEvents->HideLoading();
}
void USettingPanel::LinkCustomIDError(FApiException result)
{
    APIEvents->HideLoading();
    APIEvents->ShowErrorNotification(FString::FromInt(result.ErrorCode), result.ErrorMessage);
    UE_LOG(LogTemp, Display, TEXT("Error%s"), *result.ErrorMessage);
}

void USettingPanel::UnLinkCustomIDReply(FUnlinkCustomIDResult result)
{
    APIEvents->HideLoading();
    UE_LOG(LogTemp, Display, TEXT("THE UnLINKED--SUCCESS---->>%s"), *result.Message);
    isLoginCustomID = false;
    LinkCustomText->SetText(FText::FromString("Link Custom ID"));
}
void USettingPanel::UnLinkCustomIDError(FApiException result)
{
    APIEvents->HideLoading();
    UE_LOG(LogTemp, Display, TEXT("THE UnLINKED--FAILED---->>%s"), *result.ErrorMessage);
    APIEvents->ShowErrorNotification(FString::FromInt(result.ErrorCode), result.ErrorMessage);
}
//=================== LINK/UNLINK ANdroid DEVICE===========================
void USettingPanel::OnClickLinkAndrtoidDeviceID()
{
    if (isAndroidDeviceID)
    {
        APIEvents->ShowLoading();
        UE_LOG(LogTemp, Display, TEXT("Clicked On CUSTOmID222---222->>"))
        UUserAccountManagementHandler::UnlinkAndroidDeviceID(UnlinkAndroidDeviceIDResult, UnlinkAndroidDeviceIDApiException);
    }
    else
    {
        APIEvents->ShowLoading();
        FLinkAndroidDeviceIDRequest request;
        request.AndroidDeviceID = "AndroidID0012";
        request.ForceLink = true;
        UUserAccountManagementHandler::LinkAndroidDeviceID(request, LinkAndroidDeviceIDResult, LinkAndroidDeviceIDApiException);
    }
}
void USettingPanel::LinkAndroidDeviceIDReply(FLinkAndroidDeviceIDResult result)
{
    APIEvents->HideLoading();
    isAndroidDeviceID = true;
    LinkAndroidDeviceText->SetText(FText::FromString("UnLink Android Device ID"));
    UE_LOG(LogTemp, Display, TEXT("THE LINKED ANDROID--SUCCESS---->>"));
}
void USettingPanel::LinkAndroidIDError(FApiException result)
{
    APIEvents->HideLoading();
    UE_LOG(LogTemp, Display, TEXT("THE LINKED-Android-FAILED---->>%s"), *result.ErrorMessage);
    APIEvents->ShowErrorNotification(FString::FromInt(result.ErrorCode), result.ErrorMessage);
}

void USettingPanel::UnlinkAndroidDeviceIDReply(FUnlinkAndroidDeviceIDResult result)
{
    APIEvents->HideLoading();
    isAndroidDeviceID = false;
    LinkAndroidDeviceText->SetText(FText::FromString("Link Android Device ID"));
    UE_LOG(LogTemp, Display, TEXT("THE UnLINKED ANDROID--SUCCESS---->>%s"), *result.Message);
}
void USettingPanel::UnlinkAndroidDeviceIDError(FOnApiException result)
{
    APIEvents->HideLoading();
    UE_LOG(LogTemp, Display, TEXT("THE UnLINKED--FAILED---->"));
    // APIEvents->ShowErrorNotification(FString::FromInt(result.ErrorCode),result.ErrorMessage);
}
// void USettingPanel::OnLoginAndroidIDReply(FLoginWithAndroidDeviceIDResult result)
// {
//     APIEvents->HideLoading();
//     isAndroidDeviceID = true;
//     LinkAndroidDeviceText->SetText(FText::FromString("UnLink Android Device ID"));
//     UE_LOG(LogTemp, Display, TEXT("THE LINKED ANDROID--SUCCESS---->>"));
// }
// void USettingPanel::OnLoginAndroidIDError(FApiException result)
// {
//      APIEvents->HideLoading();
//     UE_LOG(LogTemp, Display, TEXT("THE LINKED-Android-FAILED---->>%s"),*result.ErrorMessage);
//     APIEvents->ShowErrorNotification(FString::FromInt(result.ErrorCode),result.ErrorMessage);
// }

//=================== UNLINK IOS DEVICE===========================
void USettingPanel::OnClickLinkIOSDeviceID()
{
    if (isLinkIOSDeviceID)
    {
        APIEvents->ShowLoading();
        UE_LOG(LogTemp, Display, TEXT("Clicked On IOS DEVICE ---222->>"));
        UUserAccountManagementHandler::UnlinkIOSDeviceID(OnUnlinkIOSDeviceIDResult, UnlinkIOSDeviceIDApiException);
    }
    else
    {
        // APIEvents->ShowLoading();
        UE_LOG(LogTemp, Display, TEXT("Clicked On LINK IOS DEVICE ---->>"));

        FLinkIOSDeviceIDRequest request;
        request.DeviceID = "IOSRAWDEVICE123";
        request.ForceLink = true;
        UUserAccountManagementHandler::LinkIOSDeviceID(request, NewLinkIOSDeviceIDResult, NewLinkIOSDeviceIDApiException);
    }
}
void USettingPanel::OnUnlinkIOSDeviceIDReply(FUnlinkIOSDeviceIDResult result)
{
    APIEvents->HideLoading();
    isLinkIOSDeviceID = false;
    LinkIOSText->SetText(FText::FromString("Link IOS Device ID"));
    UE_LOG(LogTemp, Display, TEXT("THE UNLINKED IOS DEVICE--SUCCESS---->>%s"), *result.Message);
}
void USettingPanel::OnUnlinkIOSDeviceIDError(FApiException result)
{
    APIEvents->HideLoading();
    UE_LOG(LogTemp, Display, TEXT("THE UNLINKED-IOS DEVICE-FAILED---->>%s"), *result.ErrorMessage);
    APIEvents->ShowErrorNotification(FString::FromInt(result.ErrorCode), result.ErrorMessage);
}

void USettingPanel::LinkIOSDeviceIDReply(FLinkIOSDeviceIDResult result)
{
    APIEvents->HideLoading();
    isLinkIOSDeviceID = true;
    LinkIOSText->SetText(FText::FromString("UnLink IOS Device ID"));
    UE_LOG(LogTemp, Display, TEXT("THE LINKED IOS DEVICE--SUCCESS---->>"));
}
void USettingPanel::LinkIOSDeviceIDError(FApiException result)
{
    APIEvents->HideLoading();
    UE_LOG(LogTemp, Display, TEXT("THE LINKED-IOS DEVICE-FAILED---->>%s"), *result.ErrorMessage);
    APIEvents->ShowErrorNotification(FString::FromInt(result.ErrorCode), result.ErrorMessage);
}

//================END=== UNLINK IOS DEVICE===========================

//=================== LINK/UNLINK GOGGLE ACCOUNT=========================
void USettingPanel::OnClickLinkGoggleAccount()
{
    if (isLinkedGoggle)
    {
        APIEvents->ShowLoading();
        UUserAccountManagementHandler::UnlinkGoogleAccount(UnlinkGoogleAccounResult, UnLinkWithGoogleApiException);
    }
    else
    {
        UE_LOG(LogTemp, Display, TEXT("Clicked On LINK GOGGLE ACCOUNT ---->>"));
        FLinkGoogleAccountRequest request;
        request.GoogleID = "hsgfhisohgID";
        request.GoogleServerAuthCode = "sahf09hwhf";
        request.ForceLink = true;
        APIEvents->ShowLoading();
        UUserAccountManagementHandler::LinkGoogleAccount(request, LinkWithGoogleResult, LinkWithGoogleApiException);
    }
}
void USettingPanel::LinkGoggleAccountReply(FLinkGoogleAccountResult result)
{
    APIEvents->HideLoading();
    isLinkedGoggle = true;
    LinkGoggleText->SetText(FText::FromString("UnLink Goggle Account"));
    UE_LOG(LogTemp, Display, TEXT("Clicked On LINK GOGGLE SUCCESS ---->>%"));
}
void USettingPanel::LinkGoggleAccountError(FApiException result)
{
    APIEvents->HideLoading();
    UE_LOG(LogTemp, Display, TEXT("Clicked On LINK GOGGLE Failed ---->>%s"), *result.ErrorMessage);
}
void USettingPanel::UnLinkGoggleAccountReply(FUnlinkGoogleAccountResult result)
{
    APIEvents->HideLoading();
    isLinkedGoggle = false;
    LinkGoggleText->SetText(FText::FromString("Link Goggle Account"));
    UE_LOG(LogTemp, Display, TEXT("THE UNLINKED GOGGLE ACCOUNT--SUCCESS---->>%s"), *result.Message);
}
void USettingPanel::UnLinkGoggleAccountError(FApiException result)
{
    APIEvents->HideLoading();
    UE_LOG(LogTemp, Display, TEXT("THE UNLINKED GOGGLE ACCOUNT--Failed---->>%s"));
}

//===============END==== LINK/UNLINK GOGGLE ACCOUNT=========================

//=================== LINK/UNLINK APPLE=========================
void USettingPanel::OnClickLinkApple()
{
    if (isLinkApple)
    {
        UE_LOG(LogTemp, Display, TEXT("CLICKED IN--APPLE-->>"));
        APIEvents->ShowLoading();
        UUserAccountManagementHandler::UnlinkApple(UnlinkAppleResult, OnUnLinkAppleApiException);
    }
    else
    {
        FLinkAppleRequest request;

        request.AppleID = "AppleId2545";
        request.ForceLink = true;
        request.IdentityToken = "IdentityToken2442rr";

        APIEvents->ShowLoading();
        UUserAccountManagementHandler::LinkApple(request, OnLinkAppleResult, OnLinkAppleApiException);
    }
}
void USettingPanel::OnLinkAppleReply(FLinkAppleResult result)
{
    APIEvents->HideLoading();
    isLinkApple = true;
    LinkAppleText->SetText(FText::FromString("UnLink Apple"));
    UE_LOG(LogTemp, Display, TEXT("Clicked On LINK APPLE SUCCESS ---->>"));
}
void USettingPanel::OnLinkAppleError(FApiException result)
{
    APIEvents->HideLoading();
    UE_LOG(LogTemp, Display, TEXT("Clicked On LINK APPLE FAILED ---->>"));
}
void USettingPanel::UnLinkAppleReply(FUnlinkAppleResult result)
{
    APIEvents->HideLoading();
    isLinkApple = false;
    LinkAppleText->SetText(FText::FromString("Link Apple"));
    UE_LOG(LogTemp, Display, TEXT("THE UNLINKED APPLE--SUCCESS---->>%s"), *result.Message);
}
void USettingPanel::UnlinkAppleError(FApiException result)
{
    APIEvents->HideLoading();
    UE_LOG(LogTemp, Display, TEXT("THE UNLINKED APPLEE--Failed---->>%s"));
}
void USettingPanel::OnClickLinkFacebookAccount()
{
    if (isFacebookLogin)
    {
        UE_LOG(LogTemp, Display, TEXT("CLICKED IN--FACEBOOK-->>"));
        APIEvents->ShowLoading();
        UUserAccountManagementHandler::UnlinkFacebookAccount(OnUnlinkFacebookAccountResult, OnUnlinkFacebookAccountApiException);
    }
    else
    {
        FLinkFacebookAccountRequest request;
        request.AccessToken = "iofsaiof";
        request.FacebookID = "FBID38769865";
        request.ForceLink = true;

        APIEvents->ShowLoading();

        UUserAccountManagementHandler::LinkFacebookAccount(request, OnLinkFacebookAccountResult, OnLinkFacebookAccountApiException);
    }
}
void USettingPanel::OnLinkFacebookAccountReply(FLinkFacebookAccountResult result)
{
    APIEvents->HideLoading();
    isFacebookLogin = true;
    LinkFBText->SetText(FText::FromString("UnLink Facebook Account"));
    UE_LOG(LogTemp, Display, TEXT("THE LINKED FACEBOOK--SUCCESSS---->>"));
}
void USettingPanel::OnLinkFacebookAccountError(FApiException result)
{
    APIEvents->HideLoading();
    UE_LOG(LogTemp, Display, TEXT("THE LINKED FACEBOOK--Failed---->>"));
}
void USettingPanel::OnUnlinkFacebookAccountReply(FUnlinkFacebookAccountResult result)
{
    APIEvents->HideLoading();
    isFacebookLogin = false;
    LinkFBText->SetText(FText::FromString("Link Facebook Account"));
    UE_LOG(LogTemp, Display, TEXT("THE UNLINKED FACEBOOK--SUCCESSS---->>"));
}
void USettingPanel::OnUnlinkFacebookAccountError(FApiException result)
{
    APIEvents->HideLoading();
    UE_LOG(LogTemp, Display, TEXT("THE UNLINKED FACEBOOK--Failed---->>"));
}

void USettingPanel::OnClickDeleteUser()
{
    FDeleteUserRequest request;
    request.UserID = UserDetailHolder->UserDetails.userID;
    APIEvents->ShowLoading();
    UDefaultHandler::DeleteUser(request, OnDeleteUserResponse, OnDeleteUserApiException);
}
void USettingPanel::OnDeleteUserReply(FDeleteUserResponse result)
{
    APIEvents->HideLoading();
    FString MapName = "AvataryugSample";
    UWorld *World = GetWorld();
    if (World)
    {
        UGameplayStatics::OpenLevel(World, FName(*MapName), true);
    }
    //  UserDetailHolder->UserDetails = FUserDetails();
    //  UserDetailHolder->UserDetails.linkedAcounts
    UE_LOG(LogTemp, Display, TEXT("THE DELETE USERS--->>%s"), *result.Message);
    // UE_LOG(LogTemp, Display, TEXT("THE DELETE USERS------>>%s",*result.Message));
}
void USettingPanel::OnDeleteUserResponseError(FApiException result)
{
    APIEvents->HideLoading();
    // UE_LOG(LogTemp, Display, TEXT("THE DELETE USERS--Failed---->>"));
    UE_LOG(LogTemp, Display, TEXT("THE DELETE USERS-Failed-->>%s"), *result.ErrorMessage);
}

void USettingPanel::OnClickAddDisplayName()
{

    if (EnterAddDisplayNameField->GetText().IsEmpty())
    {
        UE_LOG(LogTemp, Display, TEXT("THE  UPDATE DISPLAYNAME--EMPTY---->>"));
    }
    else
    {
        FUpdateUserProjectDisplayNameRequest request;

        request.DisplayName = EnterAddDisplayNameField->GetText().ToString();
        APIEvents->ShowLoading();
        UUserAccountManagementHandler::UpdateUserProjectDisplayName(request, OnUpdateUserProjectDisplayNameResult, OnUpdateUserProjectDisplayNameApiException);
    }
}

void USettingPanel::OnUpdateUserProjectDisplayNameReply(FUpdateUserProjectDisplayNameResult result)
{
    APIEvents->HideLoading();
    APIEvents->ShowErrorNotification(FString::FromInt(result.Code), result.Message);
    UE_LOG(LogTemp, Display, TEXT("THE  UPDATE DISPLAYNAME--SUCCESSS---->>%s"), *result.Message);
}
void USettingPanel::OnUpdateUserProjectDisplayNameError(FApiException result)
{
    APIEvents->HideLoading();
    UE_LOG(LogTemp, Display, TEXT("THE UPDATE DISPLAYNAME -FAILED---->>"));
}
void USettingPanel::EnterAddDisplayNameTextChanged(const FText &Text)
{
    FString myText = Text.ToString();

    if (myText.IsEmpty())
    {
        AddDisplayNameErrorText->SetVisibility(ESlateVisibility::Visible);
    }
    else
    {
        AddDisplayNameErrorText->SetVisibility(ESlateVisibility::Collapsed);
    }
}
void USettingPanel::OnClickUpddateEmailPassword()
{
    FChangePasswordRequest request;

    request.OldPassword = CP_EnterOldPasswordField->GetText().ToString();
    request.NewPassword = CP_EnterConfirmPasswordField->GetText().ToString();
    APIEvents->ShowLoading();
    UAuthenticationHandler::ChangePassword(request, OnChangePasswordResult, OnChangePasswordApiException);
}

void USettingPanel::OnChangePasswordReply(FChangePasswordResponse Result)
{
    APIEvents->HideLoading();
    UE_LOG(LogTemp, Display, TEXT("THE  UPDATE PASSWORDS--SUCCESSS---->>%s"), *Result.Message);
}
void USettingPanel::OnChangePasswordError(FApiException result)
{
    APIEvents->HideLoading();
    UE_LOG(LogTemp, Display, TEXT("THE UPDATE PASSWORD -FAILED---->>%s"), *result.ErrorMessage);
}

void USettingPanel::OnSettingScreenOrientation(bool isLandscape)
{
    if (isLandscape)
    {
        UCanvasPanelSlot *ButtonsScrollSlot = Cast<UCanvasPanelSlot>(ButtonsScrollBox->Slot);
        ButtonsScrollSlot->SetAnchors(FAnchors(0, 0, 1, 1));
        ButtonsScrollSlot->SetOffsets(FMargin(477.80f, 41.47f, 477.80f, 53.70f));

        UCanvasPanelSlot *ChangePasswordPoPupSlot = Cast<UCanvasPanelSlot>(Setting_ChangePasswordPoPup->Slot);
        ChangePasswordPoPupSlot->SetAnchors(FAnchors(0, 0, 1, 1));
        ChangePasswordPoPupSlot->SetOffsets(FMargin(350.0f, 656.92f, 350.0f, -329.27f));

        UCanvasPanelSlot *AddDisplayNamePopUp = Cast<UCanvasPanelSlot>(Setting_AddDisplayNamePopUp->Slot);
        AddDisplayNamePopUp->SetAnchors(FAnchors(0, 0, 1, 1));
        AddDisplayNamePopUp->SetOffsets(FMargin(350.0f, 223.0f, 350.0f, 190.0f));
    }
    else
    {
        UCanvasPanelSlot *ButtonsScrollSlot = Cast<UCanvasPanelSlot>(ButtonsScrollBox->Slot);
        ButtonsScrollSlot->SetAnchors(FAnchors(0, 0, 1, 1));
        ButtonsScrollSlot->SetOffsets(FMargin(75.0f, 40.0f, 75.0f, 230.0f));

        UCanvasPanelSlot *ChangePasswordPoPupSlot = Cast<UCanvasPanelSlot>(Setting_ChangePasswordPoPup->Slot);
        ChangePasswordPoPupSlot->SetAnchors(FAnchors(0, 0, 1, 1));
        ChangePasswordPoPupSlot->SetOffsets(FMargin(21.80f, 621.04f, 21.82f, 467.54f));

        UCanvasPanelSlot *AddDisplayNamePopUp = Cast<UCanvasPanelSlot>(Setting_AddDisplayNamePopUp->Slot);
        AddDisplayNamePopUp->SetAnchors(FAnchors(0, 0, 1, 1));
        AddDisplayNamePopUp->SetOffsets(FMargin(40.0f, 785.53f, 40.0f, 604.280f));
    }
}