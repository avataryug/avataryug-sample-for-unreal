// Fill out your copyright notice in the Description page of Project Settings.

#include "AuthenticationPanel.h"
#include "TimerManager.h"
#include "UObject/UObject.h"
#include "Engine/World.h"

void UAuthenticationPanel::NativeConstruct()
{
  Super::NativeConstruct();

  GetReference();

  SetButtonEvents();

  SubscribeEvents();

  SetInitialDetails();

}
void UAuthenticationPanel::GetReference()
  {

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
      APIEvents->OnScreenOrientation.AddDynamic(this, &UAuthenticationPanel::ScreenOrientation);
    }
  }
  if (AvatarHandler == nullptr)
  {
    AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AAvatarHandler::StaticClass());
    AvatarHandler = Cast<AAvatarHandler>(FoundActor);
    // AvatarHandler->SetActorLabel(FString("AvatarHandler"));
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

  if (CommonFunctionHolder == nullptr)
  {
    AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), ACommonFunction::StaticClass());
    CommonFunctionHolder = Cast<ACommonFunction>(FoundActor);
    if (CommonFunctionHolder == nullptr)
    {
      CommonFunctionHolder = GetWorld()->SpawnActor<ACommonFunction>();
    }
  }
  }

  void UAuthenticationPanel::SetButtonEvents() {

    SignUpButton->OnClicked.RemoveDynamic(this, &UAuthenticationPanel::OnClickSignUpButton);
  SignUpButton->OnClicked.AddDynamic(this, &UAuthenticationPanel::OnClickSignUpButton);

  LoginCustomIDButton->OnClicked.RemoveDynamic(this, &UAuthenticationPanel::OnClickLoginWithCustomID);
  LoginCustomIDButton->OnClicked.AddDynamic(this, &UAuthenticationPanel::OnClickLoginWithCustomID);

  LoginAndroidButton->OnClicked.RemoveDynamic(this, &UAuthenticationPanel::OnClickLoginWithAndroidID);
  LoginAndroidButton->OnClicked.AddDynamic(this, &UAuthenticationPanel::OnClickLoginWithAndroidID);

  LoginIOSDeviceIDButton->OnClicked.RemoveDynamic(this, &UAuthenticationPanel::OnClickLoginWithIOSDeviceID);
  LoginIOSDeviceIDButton->OnClicked.AddDynamic(this, &UAuthenticationPanel::OnClickLoginWithIOSDeviceID);

  createAccountBackButton->OnClicked.RemoveDynamic(this, &UAuthenticationPanel::OnClickcreateAccountBackButton);
  createAccountBackButton->OnClicked.AddDynamic(this, &UAuthenticationPanel::OnClickcreateAccountBackButton);

  CreateAccountSignInButton->OnClicked.RemoveDynamic(this, &UAuthenticationPanel::OnClickCreateAccountSignInButton);
  CreateAccountSignInButton->OnClicked.AddDynamic(this, &UAuthenticationPanel::OnClickCreateAccountSignInButton);

  ResendOTPButton->OnClicked.RemoveDynamic(this, &UAuthenticationPanel::ResendOTP);
  ResendOTPButton->OnClicked.AddDynamic(this, &UAuthenticationPanel::ResendOTP);

  OrientationButton->OnClicked.RemoveDynamic(this, &UAuthenticationPanel::OnclickChangeOrientationButton);
  OrientationButton->OnClicked.AddDynamic(this, &UAuthenticationPanel::OnclickChangeOrientationButton);
  
  LoginEmailButton->OnClicked.RemoveDynamic(this, &UAuthenticationPanel::OnClickLoginEmailButton);
  LoginEmailButton->OnClicked.AddDynamic(this, &UAuthenticationPanel::OnClickLoginEmailButton);

  EmailLoginBackButton->OnClicked.RemoveDynamic(this, &UAuthenticationPanel::OnClickEmailLoginBackButton);
  EmailLoginBackButton->OnClicked.AddDynamic(this, &UAuthenticationPanel::OnClickEmailLoginBackButton);

  EmailLoginForgetPasswordButton->OnClicked.RemoveDynamic(this, &UAuthenticationPanel::OnClickEmailLoginForgetPasswordButton);
  EmailLoginForgetPasswordButton->OnClicked.AddDynamic(this, &UAuthenticationPanel::OnClickEmailLoginForgetPasswordButton);

  AccountRecoveryBackButton->OnClicked.RemoveDynamic(this, &UAuthenticationPanel::OnClickAccountRecoveryBackButton);
  AccountRecoveryBackButton->OnClicked.AddDynamic( this, &UAuthenticationPanel::OnClickAccountRecoveryBackButton);
  
  ELP_LogInButton->OnClicked.RemoveDynamic(this, &UAuthenticationPanel::OnClickELP_LogInButton);
  ELP_LogInButton->OnClicked.AddDynamic(this, &UAuthenticationPanel::OnClickELP_LogInButton);

  VerifyEmailButton->OnClicked.RemoveDynamic(this, &UAuthenticationPanel::OnClickVerifyEmailButton);
  VerifyEmailButton->OnClicked.AddDynamic(this, &UAuthenticationPanel::OnClickVerifyEmailButton);

  ChangePasswordButton->OnClicked.RemoveDynamic(this, &UAuthenticationPanel::OnClickUpdatePassword);
  ChangePasswordButton->OnClicked.AddDynamic(this, &UAuthenticationPanel::OnClickUpdatePassword);

  changePasswordBackButton->OnClicked.RemoveDynamic(this, &UAuthenticationPanel::OnClickchangePasswordBackButton);
  changePasswordBackButton->OnClicked.AddDynamic(this, &UAuthenticationPanel::OnClickchangePasswordBackButton);

  VerifyOTPsButton->OnClicked.RemoveDynamic(this, &UAuthenticationPanel::OnClickVerifyOTP);
  VerifyOTPsButton->OnClicked.AddDynamic(this, &UAuthenticationPanel::OnClickVerifyOTP);

  DisplayNameInputField->OnTextChanged.AddDynamic(this, &UAuthenticationPanel::OnDisplayNameTextChanged);
  EmailInputField->OnTextChanged.AddDynamic(this, &UAuthenticationPanel::OnEmailIDTextChanged);

  PasswordInputField->OnTextChanged.AddDynamic(this, &UAuthenticationPanel::OnPasswordTextChanged);
  ConfiremPasswordInputField->OnTextChanged.AddDynamic(this, &UAuthenticationPanel::OnConfirmPasswordTextChanged);
  VerifyToggle->OnCheckStateChanged.AddDynamic(this, &UAuthenticationPanel::OnVerifyToggleStateChanged);
  ELP_NonVerifiedToggle->OnCheckStateChanged.AddDynamic(this, &UAuthenticationPanel::OnNonVerifyToggleStateChanged);
  ELP_EnterEmailInputField->OnTextChanged.AddDynamic(this, &UAuthenticationPanel::ELP_EnterEmailTextChanged);
  ELP_EnterPasswordInputField->OnTextChanged.AddDynamic(this, &UAuthenticationPanel::ELP_EnterPasswordTextChanged);
  }

  void UAuthenticationPanel::SubscribeEvents() {

    
  LoginWithCustomIDResult.BindUFunction(this, "OnLoginWithCustomIdReply");
  CustomIdApiException.BindUFunction(this, "OnLoginWithCustomIdError");

  LoginWithEmailAddressResult.BindUFunction(this, "OnLoginWithEmailAddressReply");
  LoginEmailAddressApiException.BindUFunction(this, "OnLoginWithEmailAddressError");

  SendAccoundRecoveryResponse.BindUFunction(this, "OnSendAccountRecoveryEmailReply");
  OnSendAccountRecoveryEmailException.BindUFunction(this, "OnSendRecoveryEmailError");

  LoginWithAndroidResult.BindUFunction(this, "OnLoginWithAndroidIDReply");
  OnLoginWithAndroidIDException.BindUFunction(this, "OnLoginWithAndroidIDError");

  LoginWithIOSDeviceIDResult.BindUFunction(this, "OnLoginWithIOSDeviceIDReply");
  OnLoginWithIOSDeviceIDException.BindUFunction(this, "OnLoginWithIOSDeviceIDError");

  UpdatePasswordResult.BindUFunction(this, "OnUpdatePasswordReply");
  OnUpdateEmailPasswordApiException.BindUFunction(this, "OnUpdateEmailPasswordError");

  RegisterUserResult.BindUFunction(this, "OnRegisterUserWithEmailReply");
  OnRegisterUserWithEmailException.BindUFunction(this, "OnRegisterUserWithEmailError");

  OnVerifyUserWithEmailResult.BindUFunction(this, "OnVerifyWithEmailReply");
  OnVerifyWithEmailException.BindUFunction(this, "OnVerifyWithEmailError");

  SendVerifyUserResponse.BindUFunction(this, "OnVerifyUserReply");
  OnVerifyUserEmailException.BindUFunction(this, "OnVerifyUserError");

  
  OnGetUserInventoryResult.BindUFunction(this, "GetUserInventoryResult");
  OnInventoryApiError.BindUFunction(this, "InventoryApiError");

  OnGetUserAccountInfoResult.BindUFunction(this, "OnReceiveGetUserAccountInfoResult");
  OnGetUserAccountInfoError.BindUFunction(this, "OnReceiveGetUserAccountInfoError");

  GetUsersAllAvatarsResult.BindUFunction(this, "OnGetUsersAllAvatarsResult");
  GetUsersAllAvatarsError.BindUFunction(this, "OnGetUsersAllAvatarsError");
  }

void UAuthenticationPanel::SetInitialDetails()
{
  HomePanel->SetVisibility(ESlateVisibility::Visible);
  OrientationButton->SetVisibility(ESlateVisibility::Hidden);

}

void UAuthenticationPanel::OnDisplayNameTextChanged(const FText &Text)
{
  DisplayNameText = Text.ToString();
  if (DisplayNameText.IsEmpty())
  {
    DisplayNameError->SetVisibility(ESlateVisibility::Visible);
  }
  else
  {
    DisplayNameError->SetVisibility(ESlateVisibility::Collapsed);
  }
}
void UAuthenticationPanel::OnEmailIDTextChanged(const FText &Text)
{
  EmailIDText = Text.ToString();

  if (EmailIDText.IsEmpty())
  {
    EmailError->SetVisibility(ESlateVisibility::Visible);
  }
  else
  {

    if (!FRegexMatcher(MatchEmailPattern, EmailIDText).FindNext())
    {
      // handle invalid email input
      UE_LOG(LogTemp, Display, TEXT("ENTER PROPER EMAIL-->>"));
      EmailError->SetVisibility(ESlateVisibility::Visible);
    }
    else
    {
      // handle valid email input
      EmailError->SetVisibility(ESlateVisibility::Collapsed);
    }
  }
}
void UAuthenticationPanel::OnPasswordTextChanged(const FText &Text)
{
  FString NewText = Text.ToString();
  passwordText = NewText;
  if (passwordText.IsEmpty())
  {
    PasswordError->SetVisibility(ESlateVisibility::Visible);
  }
  else
  {
    PasswordError->SetVisibility(ESlateVisibility::Collapsed);
  }
}
void UAuthenticationPanel::OnConfirmPasswordTextChanged(const FText &Text)
{
  FString NewText = Text.ToString();

  if (NewText.IsEmpty())
  {
    ConfirmPasswordError->SetVisibility(ESlateVisibility::Visible);
  }
  else
  {
    if (passwordText != NewText)
    {
      ConfirmPasswordError->SetVisibility(ESlateVisibility::Visible);
    }
    else
    {
      ConfirmPasswordError->SetVisibility(ESlateVisibility::Collapsed);
    }
  }
}

void UAuthenticationPanel::ELP_EnterEmailTextChanged(const FText &Text)
{
  FString myText = Text.ToString();

  if (myText.IsEmpty())
  {
    ELP_EnterEmailError->SetVisibility(ESlateVisibility::Visible);
  }
  else
  {
    ELP_EnterEmailError->SetVisibility(ESlateVisibility::Collapsed);
  }
}
void UAuthenticationPanel::ELP_EnterPasswordTextChanged(const FText &Text)
{
  FString myText = Text.ToString();

  if (myText.IsEmpty())
  {
    ELP_EnterPasswordError->SetVisibility(ESlateVisibility::Visible);
  }
  else
  {
    ELP_EnterPasswordError->SetVisibility(ESlateVisibility::Collapsed);
  }
}

void UAuthenticationPanel::OnClickSignUpButton()
{
  HomePanel->SetVisibility(ESlateVisibility::Hidden);
  CreateAccountPanel->SetVisibility(ESlateVisibility::Visible);
}

void UAuthenticationPanel::OnClickLoginWithCustomID()
{
  FGuid NewGuid = FGuid::NewGuid();
   if (CustomIDTextField->GetText().IsEmpty())
   {
     UE_LOG(LogTemp, Display, TEXT("ADD CUSTOM ID TO PROCEED--->>>"));
   }
   else
   {
    APIEvents->ShowLoading();
    FLoginWithCustomIDRequest request;
    request.CustomID =   CustomIDTextField->GetText().ToString();// NewGuid.ToString();
    request.CreateAccount = true;
    UAuthenticationHandler::LoginWithCustomId(request,[this](FLoginWithCustomIDResult result)
    {
      SetUserDetailAfterLogin(result.Data);
    },
    [this](FApiException error)
    {
      UE_LOG(LogTemp, Display, TEXT("error"));
    });
  }
}
void UAuthenticationPanel::OnClickLoginWithAndroidID()
{
  UE_LOG(LogTemp, Display, TEXT("OnClickLoginWithANdroid_ID"));
  //  UE_LOG(LogTemp, Display, TEXT("CLICK ON AndroiDID BUTTON"));
  APIEvents->ShowLoading();
  FLoginWithAndroidDeviceIDRequest request;
  request.AndroidDeviceID = "Android24042023";
  request.CreateAccount = true;

  UAuthenticationHandler::LoginWithAndroidDeviceID(request, LoginWithAndroidResult, OnLoginWithAndroidIDException);
}
void UAuthenticationPanel::OnClickLoginWithIOSDeviceID()
{
  UE_LOG(LogTemp, Display, TEXT("OnClickLoginWithIOS DEVICE---->>ID"));

  FLoginWithIOSDeviceIDRequest request;
  request.IOSDeviceID = "MYIOSTIM24042023";
  request.CreateAccount = true;
  APIEvents->ShowLoading();
  UAuthenticationHandler::LoginWithIOSDeviceID(request, LoginWithIOSDeviceIDResult, OnLoginWithIOSDeviceIDException);
}

void UAuthenticationPanel::OnClickELP_LogInButton()
{
  if (ELP_EnterEmailInputField->GetText().ToString().IsEmpty())
  {
    ELP_EnterEmailError->SetVisibility(ESlateVisibility::Visible);
    return;
  }

  if (ELP_EnterPasswordInputField->GetText().ToString().IsEmpty())
  {
    ELP_EnterPasswordError->SetVisibility(ESlateVisibility::Visible);
    return;
  }
  APIEvents->ShowLoading();
  UE_LOG(LogTemp, Display, TEXT("Please Wait LOGIN with EMAIL ADDRESS"));
  FLoginWithEmailAddressRequest Emailrequest;

  Emailrequest.EmailID = ELP_EnterEmailInputField->GetText().ToString();
  Emailrequest.Password = ELP_EnterPasswordInputField->GetText().ToString();
  Emailrequest.CreateAccount = true;
  TempEmailID = ELP_EnterEmailInputField->GetText().ToString();
  UAuthenticationHandler::LoginWithEmailAddress(Emailrequest, LoginWithEmailAddressResult, LoginEmailAddressApiException);
}

void UAuthenticationPanel::OnClickcreateAccountBackButton()
{
  DisplayNameInputField->SetText(FText::FromString(""));
  EmailInputField->SetText(FText::FromString(""));
  PasswordInputField->SetText(FText::FromString(""));
  ConfiremPasswordInputField->SetText(FText::FromString(""));
  DisplayNameError->SetVisibility(ESlateVisibility::Collapsed);
  EmailError->SetVisibility(ESlateVisibility::Collapsed);
  PasswordError->SetVisibility(ESlateVisibility::Collapsed);
  ConfirmPasswordError->SetVisibility(ESlateVisibility::Collapsed);
  CreateAccountPanel->SetVisibility(ESlateVisibility::Hidden);
  HomePanel->SetVisibility(ESlateVisibility::Visible);
}

void UAuthenticationPanel::OnClickLoginEmailButton()
{
  HomePanel->SetVisibility(ESlateVisibility::Hidden);
  EmailLoginPanel->SetVisibility(ESlateVisibility::Visible);
  UE_LOG(LogTemp, Display, TEXT("OnClickLoginWithEmailAddress"));
  UE_LOG(LogTemp, Display, TEXT("CLICK ON EMAIL ADDRESS"));
}

void UAuthenticationPanel::OnLoginWithCustomIdReply(FLoginWithCustomIDResult result)
{
  APIEvents->HideLoading();
  SetUserDetailAfterLogin(result.Data);
  UE_LOG(LogTemp, Display, TEXT("OnLoginWithCustomIdReply----->>Reply"));
  // this->SetVisibility(ESlateVisibility::Hidden);
}

void UAuthenticationPanel::OnLoginWithAndroidIDReply(FLoginWithAndroidDeviceIDResult result)
{
  SetUserDetailAfterLogin(result.Data);
  APIEvents->HideLoading();
  // APIEvents->ShowPanel(EUIPanels::HOME,true);
  //  this->SetVisibility(ESlateVisibility::Hidden);
  UE_LOG(LogTemp, Display, TEXT("OnLoginWithAndroidId----->>Reply%s"));
}

void UAuthenticationPanel::OnLoginWithAndroidIDError(FApiException result)
{
  APIEvents->HideLoading();
  UE_LOG(LogTemp, Display, TEXT("Android ID--->>Error%s"), *result.ErrorMessage);
}

void UAuthenticationPanel::OnLoginWithIOSDeviceIDReply(FLoginWithIOSDeviceIDResult result)
{
  SetUserDetailAfterLogin(result.Data);
  APIEvents->HideLoading();
  APIEvents->ShowPanel(EUIPanels::HOME, true);
  this->SetVisibility(ESlateVisibility::Hidden);
  UE_LOG(LogTemp, Display, TEXT("OnLoginWithIOSId----->>Reply%s"));
}

void UAuthenticationPanel::OnLoginWithIOSDeviceIDError(FApiException result)
{
  UE_LOG(LogTemp, Display, TEXT("IOS DEVICE ID--->>Error%s"), *result.ErrorMessage);
}

void UAuthenticationPanel::OnLoginWithEmailAddressReply(FLoginWithEmailAddressResult result)
{
  UserDetailHolder->UserDetails.AccessToken = result.Data.AccessToken;
  UserDetailHolder->UserDetails.userID = result.Data.User.UserID;
  UserDetailHolder->UserDetails.DisplayName = result.Data.User.DisplayName;
  UserDetailHolder->UserDetails.CreatedAt = result.Data.User.CreatedAt;
  FLinkedAcounts linkedAcounts;
  FString ResponseString = "{";
  ResponseString.Append("\"linkedAcounts\":");
  ResponseString.Append(result.Data.LinkedAccounts);
  ResponseString.Append("}");
  FJsonObjectConverter::JsonObjectStringToUStruct(ResponseString, &linkedAcounts,0,0);
  UserDetailHolder->UserDetails.linkedAcounts = linkedAcounts;

  UE_LOG(LogTemp, Warning, TEXT("NonVerifiedtoggleState = %d"), (int32)NonVerifiedtoggleState);

  if (NonVerifiedtoggleState)
  {
    SetUserDetailAfterLogin(result.Data);
    UE_LOG(LogTemp, Warning, TEXT("NonVerifiedtoggleState TRUE----->> = %d"), (int32)NonVerifiedtoggleState)
    APIEvents->HideLoading();
    APIEvents->ShowPanel(EUIPanels::HOME, true);
    this->SetVisibility(ESlateVisibility::Hidden);
    UE_LOG(LogTemp, Display, TEXT("LOGIN WITH EMAIL COMPLETED--STATE-(TRUE)--->>Result%s"), *result.Data.AccessToken);
  }
  else
  {
    UE_LOG(LogTemp, Display, TEXT("nonVeridfiedToggleIS-----ELSE-->>>%d"), result.Data.User.Verified);
    if (result.Data.User.Verified == 0)
    {
      APIEvents->HideLoading();
      LoginSuccess();
      VerifyUserWithOTPPanel->SetVisibility(ESlateVisibility::Visible);
      EmailLoginPanel->SetVisibility(ESlateVisibility::Hidden);
      UE_LOG(LogTemp, Display, TEXT("OPENING VERFIY EMAIL%s"));
    }
    else
    {
      SetUserDetailAfterLogin(result.Data);
      UE_LOG(LogTemp, Display, TEXT("LOGIN COMPLETE%s"));
      APIEvents->HideLoading();
      APIEvents->ShowPanel(EUIPanels::HOME, true);
      this->SetVisibility(ESlateVisibility::Hidden);
      UE_LOG(LogTemp, Display, TEXT("LOGIN WITH EMAIL COMPLETED------>>Result%s"), *result.Data.AccessToken);
    }
  }
}

void UAuthenticationPanel::OnLoginWithEmailAddressError(FApiException result)
{
  APIEvents->HideLoading();
  UE_LOG(LogTemp, Display, TEXT("Error%s"), *result.ErrorMessage);
}

void UAuthenticationPanel::OnLoginWithCustomIdError(FApiException result)
{
  APIEvents->HideLoading();
  APIEvents->ShowErrorNotification(FString::FromInt(result.ErrorCode), result.ErrorMessage);

  UE_LOG(LogTemp, Display, TEXT("Error%s"), *result.ErrorMessage);
}

void UAuthenticationPanel::OnClickEmailLoginBackButton()
{
  ELP_EnterEmailInputField->SetText(FText::FromString(""));
  ELP_EnterPasswordInputField->SetText(FText::FromString(""));
  ELP_EnterEmailError->SetVisibility(ESlateVisibility::Collapsed);
  ELP_EnterPasswordError->SetVisibility(ESlateVisibility::Collapsed);
  HomePanel->SetVisibility(ESlateVisibility::Visible);
  EmailLoginPanel->SetVisibility(ESlateVisibility::Hidden);
}

void UAuthenticationPanel::OnClickEmailLoginForgetPasswordButton()
{
  AccountRecoveryWithEmailPanel->SetVisibility(ESlateVisibility::Visible);
  EmailLoginPanel->SetVisibility(ESlateVisibility::Hidden);
}

void UAuthenticationPanel::OnClickAccountRecoveryBackButton()
{
  AccountRecoveryWithEmailPanel->SetVisibility(ESlateVisibility::Hidden);
  EmailLoginPanel->SetVisibility(ESlateVisibility::Visible);
}

void UAuthenticationPanel::OnClickCreateAccountSignInButton()
{

  if (DisplayNameInputField->GetText().IsEmpty())
  {
    DisplayNameError->SetVisibility(ESlateVisibility::Visible);
  }

  if (EmailInputField->GetText().IsEmpty())
  {
    EmailError->SetVisibility(ESlateVisibility::Visible);
    return;
  }

  if (PasswordInputField->GetText().IsEmpty())
  {
    PasswordError->SetVisibility(ESlateVisibility::Visible);
    return;
  }
  if (ConfiremPasswordInputField->GetText().IsEmpty())
  {
    ConfirmPasswordError->SetVisibility(ESlateVisibility::Visible);
    return;
  }
  // if (!FRegexMatcher(MatchEmailPattern, EmailIDText).FindNext())
  // {
  //   // handle invalid email input
  //   UE_LOG(LogTemp, Display, TEXT("ENTER PROPER EMAIL-->>"));
  //   EmailError->SetVisibility(ESlateVisibility::Visible);
  //   return;
  // }
  // else
  // {
  // handle valid email input
  EmailError->SetVisibility(ESlateVisibility::Collapsed);
  TempEmailID = EmailInputField->GetText().ToString();
  FRegisterUserRequest userRequest;
  userRequest.EmailID = EmailInputField->GetText().ToString();
  userRequest.Password = ConfiremPasswordInputField->GetText().ToString();
  userRequest.DisplayName = DisplayNameInputField->GetText().ToString();
  APIEvents->ShowLoading();
  UDefaultAPI::RegisterUser(userRequest, RegisterUserResult, OnRegisterUserWithEmailException);
  // }
}

void UAuthenticationPanel::OnRegisterUserWithEmailReply(FRegisterUserResponse result)
{
  // SetUserDetailAfterLogin(result.Data);

  UE_LOG(LogTemp, Display, TEXT("Create New Account Success---->>%s"), *result.Data.AccessToken);

  if (VerifytoggleState)
  {
    UE_LOG(LogTemp, Warning, TEXT("VerifyToggle TRUE----->> = %d"), (int32)VerifytoggleState)

    UserDetailHolder->UserDetails.AccessToken = result.Data.AccessToken;
    UserDetailHolder->UserDetails.userID = result.Data.User.UserID;
    UserDetailHolder->UserDetails.DisplayName = result.Data.User.DisplayName;
    UserDetailHolder->UserDetails.CreatedAt = result.Data.User.CreatedAt;

    FLinkedAcounts linkedAcounts;
    FString ResponseString = "{";
    ResponseString.Append("\"linkedAcounts\":");
    ResponseString.Append(result.Data.LinkedAccounts);
    ResponseString.Append("}");
    FJsonObjectConverter::JsonObjectStringToUStruct(ResponseString, &linkedAcounts,0,0);
    UserDetailHolder->UserDetails.linkedAcounts = linkedAcounts;
    VerifyUserWithOTPPanel->SetVisibility(ESlateVisibility::Visible);
    CreateAccountPanel->SetVisibility(ESlateVisibility::Hidden);
    DisplayNameInputField->SetText(FText::FromString(""));
    EmailInputField->SetText(FText::FromString(""));
    PasswordInputField->SetText(FText::FromString(""));
    ConfiremPasswordInputField->SetText(FText::FromString(""));
    DisplayNameError->SetVisibility(ESlateVisibility::Collapsed);
    EmailError->SetVisibility(ESlateVisibility::Collapsed);
    PasswordError->SetVisibility(ESlateVisibility::Collapsed);
    ConfirmPasswordError->SetVisibility(ESlateVisibility::Collapsed);
    LoginSuccess();
    APIEvents->HideLoading();
    UE_LOG(LogTemp, Display, TEXT("THE ACCOUNTS NAMESS---->>%s"), *UserDetailHolder->UserDetails.linkedAcounts.linkedAcounts[0].Platform);
  }
  else
  {
    UE_LOG(LogTemp, Warning, TEXT("VerifyToggle FALSE----->> = %d"), (int32)VerifytoggleState)
    UserDetailHolder->UserDetails.AccessToken = result.Data.AccessToken;
    UserDetailHolder->UserDetails.userID = result.Data.User.UserID;
    UserDetailHolder->UserDetails.DisplayName = result.Data.User.DisplayName;
    UserDetailHolder->UserDetails.CreatedAt = result.Data.User.CreatedAt;

    FLinkedAcounts linkedAcounts;
    FString ResponseString = "{";
    ResponseString.Append("\"linkedAcounts\":");
    ResponseString.Append(result.Data.LinkedAccounts);
    ResponseString.Append("}");
    FJsonObjectConverter::JsonObjectStringToUStruct(ResponseString, &linkedAcounts,0,0);
    UserDetailHolder->UserDetails.linkedAcounts = linkedAcounts;
    UUserItemManagementHandler::GetUserInventory(result.Data.User.UserID, OnGetUserInventoryResult, OnInventoryApiError);
    OnLoginComplete();
    APIEvents->HideLoading();
  }
}
void UAuthenticationPanel::OnRegisterUserWithEmailError(FApiException result)
{
  UE_LOG(LogTemp, Display, TEXT("Create New Accountl------>>Error%s"), *result.ErrorMessage);
}

void UAuthenticationPanel::OnVerifyToggleStateChanged(bool bNewState)
{
  VerifytoggleState = bNewState;
  // This function will be called whenever the check box is checked or unchecked
  if (bNewState)
  {
    UE_LOG(LogTemp, Warning, TEXT("Check box is now checked"));
  }
  else
  {
    UE_LOG(LogTemp, Warning, TEXT("Check box is now unchecked"));
  }
}
void UAuthenticationPanel::OnNonVerifyToggleStateChanged(bool bNewState)
{
  NonVerifiedtoggleState = bNewState;
  // This function will be called whenever the check box is checked or unchecked
  if (bNewState)
  {
    UE_LOG(LogTemp, Warning, TEXT("NON VERIFIED--->>Check box is now checked"));
  }
  else
  {
    UE_LOG(LogTemp, Warning, TEXT("NON VERIFIED--->>Check box is now unchecked"));
  }
}
void UAuthenticationPanel::OnClickVerifyEmailButton()
{
  UE_LOG(LogTemp, Display, TEXT("Please Wait Sending Recovery Email"));
  FSendAccountVerificationEmailRequest RecoveryEmailrequest;

  // Emailrequest.EmailID = ELP_EnterEmailInputField->GetText().ToString();
  RecoveryEmailrequest.EmailID = VerifyEmailInputField->GetText().ToString();
  VerifiedEmailsIDs = VerifyEmailInputField->GetText().ToString();
  UAuthenticationHandler::SendAccountVerificationEmail(RecoveryEmailrequest, SendVerifyUserResponse, OnVerifyUserEmailException);
}
void UAuthenticationPanel::OnVerifyUserReply(FSendAccountRecoveryEmailResponse result)
{
  UE_LOG(LogTemp, Display, TEXT("FORGET PASSWORD OTP -->>Successs---->>%s"), *result.Message);
  AccountRecoveryWithEmailPanel->SetVisibility(ESlateVisibility::Hidden);
  ChangePasswordPanel->SetVisibility(ESlateVisibility::Visible);
}
void UAuthenticationPanel::OnVerifyUserError(FApiException result)
{
  UE_LOG(LogTemp, Display, TEXT("FORGET PASSWORD OTP------>>Error%s"), *result.ErrorMessage);
}

void UAuthenticationPanel::OnClickVerifyOTP()
{
  UE_LOG(LogTemp, Display, TEXT("GET USERs ID---->>%s"), *UserDetailHolder->UserDetails.userID);

  FVerifyUserWithEmailRequest VerifyUserwithEmailRequest;
  VerifyUserwithEmailRequest.UserID = UserDetailHolder->UserDetails.userID;
  VerifyUserwithEmailRequest.VerificationCode = VerifyWithOtpInputField->GetText().ToString();
  APIEvents->ShowLoading();
  UE_LOG(LogTemp, Display, TEXT("GET USERs ID---->>%s"), *VerifyUserwithEmailRequest.VerificationCode);
  UAuthenticationHandler::VerifyUserWithEmail(VerifyUserwithEmailRequest, OnVerifyUserWithEmailResult, OnVerifyWithEmailException);
}
void UAuthenticationPanel::OnVerifyWithEmailReply(FVerifyUserWithEmailResponse result)
{
  APIEvents->HideLoading();
  APIEvents->ShowPanel(EUIPanels::HOME, true);
  this->SetVisibility(ESlateVisibility::Hidden);
  UE_LOG(LogTemp, Display, TEXT("On-VERIFY-with-OUT--Email New-->>Successs---->>%s"), *result.Message);
}
void UAuthenticationPanel::OnVerifyWithEmailError(FApiException result)
{
  APIEvents->HideLoading();
  UE_LOG(LogTemp, Display, TEXT("On-VERIFY-with-OUT--Email--Failed---->>%s"), *result.ErrorMessage);
}
void UAuthenticationPanel::LoginSuccess()
{
  UE_LOG(LogTemp, Display, TEXT("Please Wait Sending Verification OTP --->>Email"));
  FSendAccountVerificationEmailRequest verificationEmailrequest;
  verificationEmailrequest.EmailID = TempEmailID;
  VerifiedEmailsIDs = TempEmailID;

  UAuthenticationHandler::SendAccountVerificationEmail(verificationEmailrequest, SendAccoundRecoveryResponse, OnSendAccountRecoveryEmailException);

  // Emailrequest.EmailID = ELP_EnterEmailInputField->GetText().ToString();
  // RecoveryEmailrequest.EmailID = VerifyEmailInputField->GetText().ToString();
  // VerifiedEmailsIDs = VerifyEmailInputField->GetText().ToString();
  // UAuthenticationHandler::SendAccountVerificationEmail(RecoveryEmailrequest,SendAccoundRecoveryResponse,OnSendAccountRecoveryEmailException);
}
void UAuthenticationPanel::ResendOTP()
{
  UE_LOG(LogTemp, Display, TEXT("RESENDING Verification OTP --->>Email"));
  FSendAccountVerificationEmailRequest resendverificationEmailrequest;
  resendverificationEmailrequest.EmailID = TempEmailID;
  UAuthenticationHandler::SendAccountVerificationEmail(resendverificationEmailrequest, SendAccoundRecoveryResponse, OnSendAccountRecoveryEmailException);
}

void UAuthenticationPanel::OnSendAccountRecoveryEmailReply(FSendAccountRecoveryEmailResponse result)
{
  UE_LOG(LogTemp, Display, TEXT("OnSendRecoveryEmail New-->>Successs---->>%s"), *result.Message);
  VerifyEmailInputField->SetText(FText::FromString(""));
  AccountRecoveryWithEmailPanel->SetVisibility(ESlateVisibility::Hidden);
}

void UAuthenticationPanel ::OnClickUpdatePassword()
{
  UE_LOG(LogTemp, Display, TEXT("CLICK ON Update PASSWORD"));
  FUpdateEmailPasswordRequest updaterequest;
  updaterequest.EmailID = VerifiedEmailsIDs;
  updaterequest.VerificationCode = EnterTheOtpInputField->GetText().ToString();
  updaterequest.Password = ConfirmUpdatePasswordInputField->GetText().ToString();
  APIEvents->ShowLoading();
  UAuthenticationHandler::UpdateEmailPassword(updaterequest, UpdatePasswordResult, OnUpdateEmailPasswordApiException);
}
void UAuthenticationPanel ::OnClickchangePasswordBackButton()
{
  EnterTheOtpInputField->SetText(FText::FromString(""));
  NewUpdatePasswordsInputField->SetText(FText::FromString(""));
  ConfirmUpdatePasswordInputField->SetText(FText::FromString(""));
  AccountRecoveryWithEmailPanel->SetVisibility(ESlateVisibility::Visible);
  ChangePasswordPanel->SetVisibility(ESlateVisibility::Hidden);
}

void UAuthenticationPanel ::OnUpdatePasswordReply(FUpdateEmailPasswordResponse result)
{
  UE_LOG(LogTemp, Display, TEXT("Update Password Successs---->>%s"), *result.Message);
  APIEvents->HideLoading();
  APIEvents->ShowErrorNotification(FString::FromInt(400), "PASSWORD UPDATED");
  AccountRecoveryWithEmailPanel->SetVisibility(ESlateVisibility::Hidden);
  ChangePasswordPanel->SetVisibility(ESlateVisibility::Hidden);
  HomePanel->SetVisibility(ESlateVisibility::Visible);
}

void UAuthenticationPanel ::OnUpdateEmailPasswordError(FApiException result)
{
  APIEvents->HideLoading();
  UE_LOG(LogTemp, Display, TEXT("Update Password Failed---->>%s"), *result.ErrorMessage);
}
void UAuthenticationPanel ::OnSendRecoveryEmailError(FApiException result)
{
  APIEvents->HideLoading();
  UE_LOG(LogTemp, Display, TEXT("Send Recovery Email------>>Error%s"), *result.ErrorMessage);
}
void UAuthenticationPanel ::OnLoginComplete()
{

  this->SetVisibility(ESlateVisibility::Hidden);
  APIEvents->ShowPanel(EUIPanels::HOME, true);
  APIEvents->OnChangeCamera.Broadcast(CameraPanels::Lobby);
}

void UAuthenticationPanel::SetUserDetailAfterLogin(FLoginWithAndroidDeviceIDResultData data)
{
  UserDetailHolder->UserDetails.AccessToken = data.AccessToken;
  UserDetailHolder->UserDetails.userID = data.User.UserID;
  UserDetailHolder->UserDetails.DisplayName = data.User.DisplayName;
  UserDetailHolder->UserDetails.CreatedAt = data.User.CreatedAt;

  FLinkedAcounts linkedAcounts;
  FString ResponseString = "{";
  ResponseString.Append("\"linkedAcounts\":");
  ResponseString.Append(data.LinkedAccounts);
  ResponseString.Append("}");
  FJsonObjectConverter::JsonObjectStringToUStruct(ResponseString, &linkedAcounts,0,0);
  UserDetailHolder->UserDetails.linkedAcounts = linkedAcounts;
  APIEvents->ShowLoading();
  LoginComplete();
}

void UAuthenticationPanel::LoginComplete()
{
  CommonFunctionHolder->GetUserAccountInfo( [this](FGetUserAccountInfoResult info) {
    CommonFunctionHolder->GetCommonUserInventory([this,info]    {
      CommonFunctionHolder->GetUserAllAvatars([this,info](FGetUsersAllAvatarsResult avatarres)      {
        FString platform = CommonFunctionHolder->GetPlatformAsString();
        if(avatarres.Data.Num() > 0)
        {
          if(!info.Data.DefaultAvatarID.IsEmpty())
          {
            FUserAvatar userAvatar = FUserAvatar();
            for(FUserAvatar item : UserDetailHolder->UserDetails.userAvatars)
            {
              if(item.AvatarID == info.Data.DefaultAvatarID)
              {
                userAvatar = item;
                break;
              }
            }
            bool found = false;
            if(userAvatar.AvatarUrls.Num() > 0)
            {
              for (FAvatarUrlData item : userAvatar.AvatarUrls)
              {
                if(item.Platform == platform)
                {
                  found = true;
                  break;
                }
              }
            }
            CommonFunctionHolder->SetCurrentAvatarDetail();
            int count = 0;
            if (!found) {
              APIEvents->ShowLoading();
              CommonFunctionHolder->GenerateMesh(userAvatar.AvatarID,[this,platform](FGenerateAvatarMeshResponse result)
              {
                CommonFunctionHolder->GetUserAllAvatars([this,platform]
                {
                    AAvatarSync* AvatarSyncActor = GetWorld()->SpawnActor<AAvatarSync>();
                    if (AvatarSyncActor)
                    {
                      AvatarSyncActor->SyncAvatars();
                    }

                  if(AvatarHandler->TypeOfMontization == EMonitizeType::NonMonitize)
                  {
                      OpenCustomizeNonMonitize();
                  }
                  else
                  {
                      OpenHomePanel();
                  }
                });
              });
            }
            else
            {
              if(AvatarHandler->TypeOfMontization == EMonitizeType::NonMonitize)
              {
                OpenCustomizeNonMonitize();
              }
              else
              {
                APIEvents->HideLoading();
                this->SetVisibility(ESlateVisibility::Hidden);
                APIEvents->ShowPanel(EUIPanels::HOME, true);
                APIEvents->OnChangeCamera.Broadcast(CameraPanels::Lobby);
               
              }
            }
            if(count > 0)
            {
              AAvatarSync* AvatarSyncActor = GetWorld()->SpawnActor<AAvatarSync>();
              if (AvatarSyncActor)
              {
                UE_LOG(LogTemp, Display, TEXT("AvatarSyncActor---->>%s"), *platform);
                // Call the SyncAvatars function on the created actor
                AvatarSyncActor->SyncAvatars();
              }
            }
          } 
          else 
          {
            SetDefaultIdIfNotSet();
          }
        }
        else
        {
         OpenSettingPanel();
        }
      });
    }); });
}

///////GetUserAccountInfo==================================================================
void UAuthenticationPanel::OnReceiveGetUserAccountInfoResult(FGetUserAccountInfoResult result)
{
  APIEvents->HideLoading();
  FWallets Wallets;
  FString ResponseString = "{";
  ResponseString.Append("\"wallets\":");
  ResponseString.Append(result.Data.Wallet);
  ResponseString.Append("}");
  FJsonObjectConverter::JsonObjectStringToUStruct(ResponseString, &Wallets,0,0);
  UserDetailHolder->UserDetails.wallets = Wallets;
  UserDetailHolder->UserDetails.DefaultAvatarID = result.Data.DefaultAvatarID;
  UE_LOG(LogTemp, Display, TEXT("OnReceiveGetUserAccountInfoResult------>>%s"), *result.Data.Wallet);
  APIEvents->ShowLoading();
  UUserItemManagementHandler::GetUserInventory(UserDetailHolder->UserDetails.userID, OnGetUserInventoryResult, OnInventoryApiError);
}
void UAuthenticationPanel::OnReceiveGetUserAccountInfoError(FApiException error)
{
  APIEvents->HideLoading();
  APIEvents->ShowErrorNotification(FString::FromInt(error.ErrorCode), error.ErrorMessage);
  UE_LOG(LogTemp, Display, TEXT("OnReceiveGetUserAccountInfoError------>>%s"), *error.ErrorMessage);
}
void UAuthenticationPanel::GetUserInventoryResult(FGetUserInventoryResult result)
{
  UE_LOG(LogTemp, Display, TEXT("GetUserInventoryResult------>>%s"), *result.Status);
  UserInventoryHolder->AddUserInventory(result.Data);
  //------Added new Common Function-------->>
  UUserAccountManagementHandler::GetUsersAllAvatars(UserDetailHolder->UserDetails.userID, GetUsersAllAvatarsResult, GetUsersAllAvatarsError);
  //   CommonFunctionHolder->GetUserAccountInfo([this](FGetUserAccountInfoResult result){
  //   UE_LOG(LogTemp, Display, TEXT("OnReceive------>>>>>>>>GetUserAccountInfoResult------>>%s"), *result.Data.DefaultAvatarID);
  //   OnReceiveGetUserAccountInfoResult(result);
  // });
}

void UAuthenticationPanel::InventoryApiError(FApiException error)
{
  APIEvents->HideLoading();
  APIEvents->ShowErrorNotification(FString::FromInt(error.ErrorCode), error.ErrorMessage);
  UE_LOG(LogTemp, Display, TEXT("Send Recovery Email------>>Error%s"), *error.ErrorMessage);
}
///////======================================================================================
///////GetUsersAllAvatars==================================================================
void UAuthenticationPanel::OnGetUsersAllAvatarsResult(FGetUsersAllAvatarsResult result)
{
  FString userid = UserDetailHolder->UserDetails.userID;

  UE_LOG(LogTemp, Display, TEXT("OnGetUsersAllAvatarsResult------>>r%s"), *result.Status);
  FString platfrom = "Android";
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
      UserDetailHolder->UserDetails.userAvatars.Add(uservatar);
      if (result.Data[i].AvatarID == UserDetailHolder->UserDetails.DefaultAvatarID)
      {
        UserDetailHolder->UserDetails.currentUserSelectedAvatar = uservatar;
      }
    }
    UserDetailHolder->UserDetails.Gender = UserDetailHolder->UserDetails.currentUserSelectedAvatar.AvatarData.Gender == 1 ? EGender::FEMALE : EGender::MALE;
    FUserAvatar tempuserAvatar = FUserAvatar();
    for (int i = 0; i < UserDetailHolder->UserDetails.userAvatars.Num(); i++)
    {
      if (UserDetailHolder->UserDetails.userAvatars[i].AvatarID == UserDetailHolder->UserDetails.DefaultAvatarID)
      {
        tempuserAvatar = UserDetailHolder->UserDetails.userAvatars[i];
        break;
      }
    }
    bool found = false;
    for (auto &item : tempuserAvatar.AvatarUrls)
    {
      if (item.Platform == platfrom)
      {
        found = true;
        break;
      }
    }
    if (!found)
    {
    }
    else
    {

      int count = 0;
      for (auto &item : UserDetailHolder->UserDetails.userAvatars)
      {
        bool foundurls = false;
        for (auto &urls : item.AvatarUrls)
        {
          if (urls.Platform == platfrom)
          {
            foundurls = true;
          }
        }
        bool foundthumb = false;
        for (auto &urls : item.ThumbUrls)
        {
          if (urls.Platform == platfrom)
          {
            foundthumb = true;
          }
        }
        if (!foundurls)
        {
          count++;
        }
        if (!foundthumb)
        {
          count++;
        }
      }
      if (count > 0)
      {
        // GameObject gameObject = new GameObject();
        // AvatarSyncScript avatarSync = gameObject.AddComponent<AvatarSyncScript>();
        // avatarSync.SyncAvatars();
      }
      APIEvents->HideLoading();
      this->SetVisibility(ESlateVisibility::Hidden);
      APIEvents->ShowPanel(EUIPanels::HOME, true);
      APIEvents->OnChangeCamera.Broadcast(CameraPanels::Lobby);
    }
  }
  else
  {
    // Got Client Setting Panel
    //     APIEvents->HideLoading();
    this->SetVisibility(ESlateVisibility::Hidden);
    APIEvents->ShowPanel(EUIPanels::CLIENTSETTING, true);

    APIEvents->HideLoading();
    // this->SetVisibility(ESlateVisibility::Hidden);
    // APIEvents->ShowPanel(EUIPanels::HOME, true);
  }
}

void UAuthenticationPanel::OnGetUsersAllAvatarsError(FApiException error)
{
  APIEvents->HideLoading();
  APIEvents->ShowErrorNotification(FString::FromInt(error.ErrorCode), error.ErrorMessage);
  UE_LOG(LogTemp, Display, TEXT("OnReceiveGetUserAccountInfoError------>>%s"), *error.ErrorMessage);
}
///////======================================================================================

void UAuthenticationPanel::OnclickChangeOrientationButton()
{
  isClicked = !isClicked;
  // APIEvents->	OnScreenOrientation.Broadcast(isClicked);
  APIEvents->SetResolution(isClicked);
}
void UAuthenticationPanel::ScreenOrientation(bool isLandscape)
{
  if (isLandscape)
  {
    UE_LOG(LogTemp, Display, TEXT(" Game isLandscape------>>"));
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "Game isLandscape------>>");
    // UVerticalBoxSlot* VerticalBoxSlot = Cast<UVerticalBoxSlot>(IconPanel->RenderTransform);
    //  if (VerticalBoxSlot != nullptr)
    // {
    //  FMargin Padding(10.0f); // Set the padding values (all sides)
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "IconPanel CanvasSlot------>>");

    // FVector2D Translation(-650.0f, 450.0f); // Set the translation values (X, Y)
    // FVector2D Scale(1.0f, 1.0f); // Set the scale values (X, Y)
    // float Rotation = 0.0f; // Set the rotation value (in degrees)

    FWidgetTransform Transform;
    Transform.Translation.X = -650.0f;
    Transform.Translation.Y = 450.0f;
    Transform.Scale = FVector2D(1, 1);
    Transform.Angle = 0.0f;

    IconPanel->SetRenderTransform(Transform);

    // Canvas->Padding(0,0,300,0);
    // Canvas->SetAnchors(FAnchors(1, 0, 1, 1));
    // Canvas->SetOffsets(FMargin(0, -10, 750, 0));
    // Canvas->SetAlignment(FVector2D(1, 0));

    UCanvasPanelSlot *Canvas = Cast<UCanvasPanelSlot>(ButtonsVerticalBox->Slot);
    Canvas->SetAnchors(FAnchors(0, 0, 1, 1));
    Canvas->SetOffsets(FMargin(950, 0, 20, 140));

    // InputFieldsVerticalBox setOffset(70,131,70,-16)
    // Canvas->SetAnchors(FAnchors(0, 0, 1, 1));

    UCanvasPanelSlot *CreateAccountInputFieldSlot = Cast<UCanvasPanelSlot>(InputFieldsVerticalBox->Slot);
    CreateAccountInputFieldSlot->SetAnchors(FAnchors(0, 0, 1, 1));
    CreateAccountInputFieldSlot->SetOffsets(FMargin(70.0f, 140.0f, 70.0f, -16.0f));

    UCanvasPanelSlot *WhiteBGImageSlot = Cast<UCanvasPanelSlot>(WhiteBGImage->Slot);
    WhiteBGImageSlot->SetAnchors(FAnchors(0, 0, 1, 1));
    WhiteBGImageSlot->SetOffsets(FMargin(80.0f, 150.0f, 80.0f, 25.0f));

    // EmailLoginPAnel
    // EmailVerticalBOx setOffset(80,153,80,88)
    // popupImage Offset(80,165,80,86.55)

    UCanvasPanelSlot *EmailLoginSlot = Cast<UCanvasPanelSlot>(EmailLoginVerticalBox->Slot);
    EmailLoginSlot->SetAnchors(FAnchors(0, 0, 1, 1));
    EmailLoginSlot->SetOffsets(FMargin(80.0f, 153.0f, 80.0f, 88.0f));

    UCanvasPanelSlot *PopUPBGImageSlot = Cast<UCanvasPanelSlot>(PopUPBG->Slot);
    PopUPBGImageSlot->SetAnchors(FAnchors(0, 0, 1, 1));
    PopUPBGImageSlot->SetOffsets(FMargin(80.0f, 165.0f, 80.0f, 86.55f));

    // AccountVERIFY EMAIL VE_Image SetAnchor(0,0,1,1)
    // OFFset(80,919.0,80,727)

    // VerticalBox Anchor(0,0,1,1)
    // Offset(80,680.24,80.0,-184)
    // RenderTransfrom(0,-354)

    UCanvasPanelSlot *AccountRecoverySlot = Cast<UCanvasPanelSlot>(AccountRecoveryVerticalBoxs->Slot);

    AccountRecoverySlot->SetAnchors(FAnchors(0, 0, 1, 1));
    AccountRecoverySlot->SetOffsets(FMargin(80.0f, 680.24f, 80.0f, -184.0f));

    FWidgetTransform AccountRecoveryTransform;
    AccountRecoveryTransform.Translation.X = 0.0f;
    AccountRecoveryTransform.Translation.Y = -354.0f;
    AccountRecoveryTransform.Scale = FVector2D(1, 1);
    AccountRecoveryTransform.Angle = 0.0f;

    AccountRecoveryVerticalBoxs->SetRenderTransform(AccountRecoveryTransform);

    UCanvasPanelSlot *AccuntVerifyPopupSlot = Cast<UCanvasPanelSlot>(AccuntVerifyPopupImages->Slot);
    AccuntVerifyPopupSlot->SetAnchors(FAnchors(0, 0, 1, 1));
    AccuntVerifyPopupSlot->SetOffsets(FMargin(80.0f, 323.0f, 80.0f, 173.0f));
  }
  else
  {
    UE_LOG(LogTemp, Display, TEXT(" Game Potrait------>>"));
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, "Game Potrait------>>");

    FWidgetTransform Transform;
    Transform.Translation.X = 0.0f;
    Transform.Translation.Y = 0.0f;
    Transform.Scale = FVector2D(1, 1);
    Transform.Angle = 0.0f;

    IconPanel->SetRenderTransform(Transform);

    UCanvasPanelSlot *Canvas = Cast<UCanvasPanelSlot>(ButtonsVerticalBox->Slot);
    Canvas->SetAnchors(FAnchors(0, 0, 1, 1));
    Canvas->SetOffsets(FMargin(200, 0, 200, 50));

    // InputFieldsVerticalBox setOffset(70,417.47,70,263.17)
    // Canvas->SetAnchors(FAnchors(0, 0, 1, 1));
    //  WhiteBGImageSlotSetOFfset(80,419,80,271.18)

    UCanvasPanelSlot *CreateAccountInputFieldSlot = Cast<UCanvasPanelSlot>(InputFieldsVerticalBox->Slot);
    CreateAccountInputFieldSlot->SetAnchors(FAnchors(0, 0, 1, 1));
    CreateAccountInputFieldSlot->SetOffsets(FMargin(70.0f, 417.47f, 70.0f, 263.17f));

    UCanvasPanelSlot *WhiteBGImageSlot = Cast<UCanvasPanelSlot>(WhiteBGImage->Slot);
    WhiteBGImageSlot->SetAnchors(FAnchors(0, 0, 1, 1));
    WhiteBGImageSlot->SetOffsets(FMargin(80.0f, 419.0f, 80.0f, 271.18f));

    // EmailLoginPAnel
    // EmailVerticalBOx setOffset(80,553.86,80,440.75)
    // popupImage Offset(80,553.86,80,440.75)

    UCanvasPanelSlot *EmailLoginSlot = Cast<UCanvasPanelSlot>(EmailLoginVerticalBox->Slot);
    EmailLoginSlot->SetAnchors(FAnchors(0, 0, 1, 1));
    EmailLoginSlot->SetOffsets(FMargin(80.0f, 550.0f, 80.0f, 445.25f));

    UCanvasPanelSlot *PopUPBGImageSlot = Cast<UCanvasPanelSlot>(PopUPBG->Slot);
    PopUPBGImageSlot->SetAnchors(FAnchors(0, 0, 1, 1));
    PopUPBGImageSlot->SetOffsets(FMargin(80.0f, 550.0f, 80.0f, 445.25f));

    // AccountVERIFY EMAIL VE_Image SetAnchor(0,0,1,1)
    // OFFset(80,672.9,80,736.47)

    // VerticalBox Anchor(0,0,1,1)
    // Offset(80,666.97,80.0,723.19)
    // RenderTransfrom(0,-325)

    UCanvasPanelSlot *AccountRecoverySlot = Cast<UCanvasPanelSlot>(AccountRecoveryVerticalBoxs->Slot);

    AccountRecoverySlot->SetAnchors(FAnchors(0, 0, 1, 1));
    AccountRecoverySlot->SetOffsets(FMargin(80.0f, 666.97f, 80.0f, 723.19f));

    FWidgetTransform AccountRecoveryTransform;
    AccountRecoveryTransform.Translation.X = 0.0f;
    AccountRecoveryTransform.Translation.Y = 0.0f;
    AccountRecoveryTransform.Scale = FVector2D(1, 1);
    AccountRecoveryTransform.Angle = 0.0f;

    AccountRecoveryVerticalBoxs->SetRenderTransform(AccountRecoveryTransform);

    UCanvasPanelSlot *AccuntVerifyPopupSlot = Cast<UCanvasPanelSlot>(AccuntVerifyPopupImages->Slot);
    AccuntVerifyPopupSlot->SetAnchors(FAnchors(0, 0, 1, 1));
    AccuntVerifyPopupSlot->SetOffsets(FMargin(80.0f, 672.91f, 80.0f, 736.47f));
  }
}

void UAuthenticationPanel::OpenSettingPanel()
{
  this->SetVisibility(ESlateVisibility::Hidden);
  APIEvents->ShowPanel(EUIPanels::CLIENTSETTING, true);
  APIEvents->HideLoading();
}

void UAuthenticationPanel::SetDefaultIdIfNotSet()
{
  FString platform = CommonFunctionHolder->GetPlatformAsString();
  FUserAvatar useravatar =  UserDetailHolder->UserDetails.userAvatars[0];
  CommonFunctionHolder->UpdateDefaultAvatarID(useravatar.AvatarID, [this, platform, useravatar] {
  CommonFunctionHolder->GenerateMesh( useravatar.AvatarID, [this, platform](FGenerateAvatarMeshResponse result) {
  CommonFunctionHolder->GetUserAccountInfo([this](FGetUserAccountInfoResult info) {
  CommonFunctionHolder->GetUserAllAvatars([this] {
  CommonFunctionHolder->GetCommonUserInventory([this] {
  CommonFunctionHolder->LoadCurrentAvatarData([this] {
              if (AvatarHandler->TypeOfMontization == EMonitizeType::NonMonitize) 
              {
                OpenCustomizeNonMonitize();
              }
              else
              {
                OpenHomePanel(); 
              }
            });
          });
        });
      });
    });
  });
}

void UAuthenticationPanel::OpenCustomizeNonMonitize()
{
  if(AvatarHandler->customizeAvatarLoader->spawnedHeadActor == nullptr)
  {
    AvatarHandler->customizeAvatarLoader->LoadHeadModel([this] 
    {
      AvatarHandler->customizeAvatarLoader->ResetData();
      AvatarHandler->customizeAvatarLoader->ResetToCurrentSelectedModel([this] 
      {
        APIEvents->HideLoading();
        AvatarHandler->ForCustomizeAvatar = AvatarHandler->customizeAvatarLoader;
        APIEvents->ShowPanel(EUIPanels::CUSTOMIZEFULL, true);
        APIEvents->OnChangeCamera.Broadcast(CameraPanels::CustomizeAvatar_FullBody);
        this->SetVisibility(ESlateVisibility::Hidden);
      });
    });
  }
}

void UAuthenticationPanel::OpenHomePanel()
{
  APIEvents->HideLoading();
  this->SetVisibility(ESlateVisibility::Hidden);
  APIEvents->ShowPanel(EUIPanels::HOME, true);
  APIEvents->OnChangeCamera.Broadcast(CameraPanels::Lobby);
}