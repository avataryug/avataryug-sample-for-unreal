// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonModels.h"
#include "TimerManager.h"
#include "Engine/World.h" 
#include "JsonObjectConverter.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/ContentWidget.h"
#include "Components/TextBlock.h"
#include "Components/SizeBox.h"
#include "Components/CheckBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/EditableTextBox.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/VerticalBox.h"
#include "Components/CanvasPanelSlot.h"
#include "Internationalization/Regex.h"
#include "AuthenticationAPI/AuthenticationModels.h"
#include <regex>
#include "DefaultAPI/DefaultModels.h"
#include "DefaultAPI/DefaultAPI.h"
#include "AuthenticationAPI/AuthenticationHandler.h"
#include "AuthenticationAPI/AuthenticationRequest.h"
#include "UserItemManagementAPI/UserItemManagementModels.h"
#include "UserItemManagementAPI/UserItemManagementRequest.h"
#include "UserAccountManagementAPI/UserAccountManagementAPI.h"
#include "UserAccountManagementAPI/UserAccountManagementModels.h"
#include "UserAccountManagementAPI/UserAccountManagementRequest.h"
#include "UserAccountManagementAPI/UserAccountManagementHandler.h"
#include "UserItemManagementAPI/UserItemManagementHandler.h"
#include "Kismet/GameplayStatics.h"
#include "../HomePanel/HomePanel.h"
#include "../../Utilitys/APIEvents.h"
#include "../../DataHolders/CommonFunction.h"
#include "../../DataHolders/AvatarSync.h"
#include "../../Utilitys/Utilitys.h"
#include "../../DataHolders/UserDetailHolder.h"
#include "../../AvatarLoader/AvatarHandler.h"
#include "../../DataHolders/UserInventoryHolder.h"
#include "AuthenticationPanel.generated.h"

/**
 *
 */
UCLASS()
class AVATARYUGDEMO_API UAuthenticationPanel : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool NonVerifiedtoggleState = false;

protected:
    UPROPERTY(meta = (BindWidget))
    class USizeBox *MainButtonParent;

	UPROPERTY(meta = (BindWidget))
	class UButton *SignUpButton;

	UPROPERTY(meta = (BindWidget))
	class UButton *ResendOTPButton;

	UPROPERTY(meta = (BindWidget))
	class UButton *OrientationButton;

	UFUNCTION()
	void ResendOTP();

	bool isClicked = false;

	UPROPERTY(meta = (BindWidget))
	class UButton *createAccountBackButton;

	UPROPERTY(meta = (BindWidget))
	class UButton *LoginEmailButton;

	UPROPERTY(meta = (BindWidget))
	class UButton *EmailLoginBackButton;

	// ------ Email Login Panels-----------------
	UPROPERTY(meta = (BindWidget))
	class UButton *ELP_LogInButton;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox *ELP_EnterEmailInputField;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox *ELP_EnterPasswordInputField;

	UPROPERTY(meta = (BindWidget))
	class UButton *EmailLoginForgetPasswordButton;

	UPROPERTY(meta = (BindWidget))
	class UCheckBox *ELP_NonVerifiedToggle;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock *ELP_EnterEmailError;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock *ELP_EnterPasswordError;

	UPROPERTY(meta = (BindWidget))
	class UVerticalBox *EmailLoginVerticalBox;

	UPROPERTY(meta = (BindWidget))
	class UImage *PopUPBG;

	UFUNCTION()
	void OnNonVerifyToggleStateChanged(bool bNewState);

	FOnLoginWithEmailAddressResult LoginWithEmailAddressResult;

	UFUNCTION()
	void OnLoginWithEmailAddressReply(FLoginWithEmailAddressResult result);

	FOnApiException LoginEmailAddressApiException;

	UFUNCTION()
	void OnLoginWithEmailAddressError(FApiException result);

	UFUNCTION()
	void OnClickELP_LogInButton();

	UFUNCTION()
	void ELP_EnterEmailTextChanged(const FText &Text);

	UFUNCTION()
	void ELP_EnterPasswordTextChanged(const FText &Text);
	//-------------------------------------------

	//----------ACCOUNT RECOVER PANEL----------
	UPROPERTY(meta = (BindWidget))
	class UButton *VerifyEmailButton;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox *VerifyEmailInputField;

	UFUNCTION()
	void OnClickVerifyEmailButton();

	FOnSendAccountRecoveryEmailResponse SendAccoundRecoveryResponse;

	UFUNCTION()
	void OnSendAccountRecoveryEmailReply(FSendAccountRecoveryEmailResponse result);

	FOnApiException OnSendAccountRecoveryEmailException;

	UFUNCTION()
	void OnSendRecoveryEmailError(FApiException result);

	UPROPERTY(meta = (BindWidget))
	class UVerticalBox *AccountRecoveryVerticalBoxs;

	UPROPERTY(meta = (BindWidget))
	class UImage *AccuntVerifyPopupImages;
	//-------------------------------------------

	//----------VERIFY USER WITH EMAIL PANEL----------

	FOnSendAccountRecoveryEmailResponse SendVerifyUserResponse;

	UFUNCTION()
	void OnVerifyUserReply(FSendAccountRecoveryEmailResponse result);

	FOnApiException OnVerifyUserEmailException;

	UFUNCTION()
	void OnVerifyUserError(FApiException result);

	//----------END VERIFY USER WITH EMAIL PANEL----------

	//--------------LOGIN WITH ANDROID---------------

	UPROPERTY(meta = (BindWidget))
	class UButton *LoginAndroidButton;

	FOnLoginWithAndroidDeviceIDResult LoginWithAndroidResult;

	UFUNCTION()
	void OnLoginWithAndroidIDReply(FLoginWithAndroidDeviceIDResult result);

	FOnApiException OnLoginWithAndroidIDException;

	UFUNCTION()
	void OnLoginWithAndroidIDError(FApiException result);

	UFUNCTION()
	void OnClickLoginWithAndroidID();

	//----------END----LOGIN WITH ANDROID--------

	//-----------LOGIN WITH IOS DEVICE ID------------
	UPROPERTY(meta = (BindWidget))
	class UButton *LoginIOSDeviceIDButton;

	FOnLoginWithIOSDeviceIDResult LoginWithIOSDeviceIDResult;

	UFUNCTION()
	void OnLoginWithIOSDeviceIDReply(FLoginWithIOSDeviceIDResult result);

	FOnApiException OnLoginWithIOSDeviceIDException;

	UFUNCTION()
	void OnLoginWithIOSDeviceIDError(FApiException result);

	UFUNCTION()
	void OnClickLoginWithIOSDeviceID();

	//----------END----LOGIN WITH IOS DEVICE ID--------

	//--------------VerifyWithOTP-------------------------------

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel *VerifyUserWithOTPPanel;

	UPROPERTY(meta = (BindWidget))
	class UButton *VerifyOTPsButton;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox *VerifyWithOtpInputField;

	UFUNCTION()
	void OnClickVerifyOTP();

	FOnVerifyUserWithEmailResponse OnVerifyUserWithEmailResult;

	UFUNCTION()
	void OnVerifyWithEmailReply(FVerifyUserWithEmailResponse result);

	FOnApiException OnVerifyWithEmailException;

	UFUNCTION()
	void OnVerifyWithEmailError(FApiException result);

	//-------------ENd-VerifyWITHOtp----------------------------

	//-------------------SIGN IN ACCOUNT------------------------

	UPROPERTY(meta = (BindWidget))
	class UButton *CreateAccountSignInButton;

	FOnRegisterUserResponse RegisterUserResult;

	UFUNCTION()
	void OnRegisterUserWithEmailReply(FRegisterUserResponse result);

	FOnApiException OnRegisterUserWithEmailException;

	UFUNCTION()
	void OnRegisterUserWithEmailError(FApiException result);

	UFUNCTION()
	void OnClickCreateAccountSignInButton();

	//----------------END-SIGN IN ACCOUNT-----------------------
	UPROPERTY(meta = (BindWidget))
	class UButton *AccountRecoveryBackButton;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel *HomePanel;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel *IconPanel;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel *CreateAccountPanel;

	UPROPERTY(meta = (BindWidget))
	class UVerticalBox *InputFieldsVerticalBox;

	UPROPERTY(meta = (BindWidget))
	class UImage *WhiteBGImage;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel *EmailLoginPanel;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel *AccountRecoveryWithEmailPanel;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox *DisplayNameInputField;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock *DisplayNameError;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox *EmailInputField;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock *EmailError;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox *PasswordInputField;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock *PasswordError;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox *ConfiremPasswordInputField;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock *ConfirmPasswordError;

	UPROPERTY(meta = (BindWidget))
	class UCheckBox *VerifyToggle;

	UPROPERTY(meta = (BindWidget))
	class UVerticalBox *ButtonsVerticalBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool VerifytoggleState = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString passwordText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString DisplayNameText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString EmailIDText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString TempEmailID;
	void NativeConstruct() override;

	UFUNCTION()
	void OnClickSignUpButton();

	UFUNCTION()
	void OnClickcreateAccountBackButton();

	UFUNCTION()
	void OnClickLoginEmailButton();

	UFUNCTION()
	void OnClickEmailLoginBackButton();

	UFUNCTION()
	void OnClickEmailLoginForgetPasswordButton();

	UFUNCTION()
	void OnClickAccountRecoveryBackButton();

	UFUNCTION()
	void OnDisplayNameTextChanged(const FText &Text);

	UFUNCTION()
	void OnEmailIDTextChanged(const FText &Text);

	UFUNCTION()
	void OnPasswordTextChanged(const FText &Text);

	UFUNCTION()
	void OnConfirmPasswordTextChanged(const FText &Text);

	UFUNCTION()
	void OnVerifyToggleStateChanged(bool bNewState);
	//----------------------LOGIN WITH CUSTOM--ID-------------------------

	UPROPERTY(meta = (BindWidget))
	class UButton *LoginCustomIDButton;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox *CustomIDTextField;

	FOnLoginWithCustomIDResult LoginWithCustomIDResult;

	UFUNCTION()
	void OnLoginWithCustomIdReply(FLoginWithCustomIDResult result);

	FOnApiException CustomIdApiException;

	UFUNCTION()
	void OnLoginWithCustomIdError(FApiException result);

	UFUNCTION()
	void OnClickLoginWithCustomID();

	//---------------------------------------------------------------------

	//--------------------------CHANGE PASSWORD----------------------------

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel *ChangePasswordPanel;

	UPROPERTY(meta = (BindWidget))
	class UButton *changePasswordBackButton;

	UPROPERTY(meta = (BindWidget))
	class UButton *ChangePasswordButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString VerifiedEmailsIDs;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox *EnterTheOtpInputField;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox *NewUpdatePasswordsInputField;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox *ConfirmUpdatePasswordInputField;

	UFUNCTION()
	void OnClickUpdatePassword();

	UFUNCTION()
	void OnClickchangePasswordBackButton();

	FOnUpdateEmailPasswordResponse UpdatePasswordResult;

	UFUNCTION()
	void OnUpdatePasswordReply(FUpdateEmailPasswordResponse result);

	FOnApiException OnUpdateEmailPasswordApiException;

	UFUNCTION()
	void OnUpdateEmailPasswordError(FApiException result);

	UFUNCTION()
	void LoginSuccess();

	//----------------------------------------------------------------------

	//-----------------------HOME PANE---------------------------------
	//-----------------------------------------------------------------

	UFUNCTION()
	void OnLoginComplete();

	AAPIEvents *APIEvents;

	UFUNCTION()
	void SetUserDetailAfterLogin(FLoginWithAndroidDeviceIDResultData data);

	UFUNCTION()
	void LoginComplete();

	AUserDetailHolder *UserDetailHolder;

	FOnGetUserInventoryResult OnGetUserInventoryResult;
	UFUNCTION()
	void GetUserInventoryResult(FGetUserInventoryResult result);
	FOnApiException OnInventoryApiError;
	UFUNCTION()
	void InventoryApiError(FApiException error);

	AUserInventoryHolder *UserInventoryHolder;

	UPROPERTY()
	ACommonFunction *CommonFunctionHolder;

	UPROPERTY()
	AAvatarHandler *AvatarHandler;

	// Get User Account info
	UPROPERTY()
	FOnGetUserAccountInfoResult OnGetUserAccountInfoResult;
	UFUNCTION()
	void OnReceiveGetUserAccountInfoResult(FGetUserAccountInfoResult result);
	UPROPERTY()
	FOnApiException OnGetUserAccountInfoError;
	UFUNCTION()
	void OnReceiveGetUserAccountInfoError(FApiException error);
	// Get user all avatars
	UPROPERTY()
	FOnGetUsersAllAvatarsResult GetUsersAllAvatarsResult;
	UFUNCTION()
	void OnGetUsersAllAvatarsResult(FGetUsersAllAvatarsResult result);
	UPROPERTY()
	FOnApiException GetUsersAllAvatarsError;
	UFUNCTION()
	void OnGetUsersAllAvatarsError(FApiException error);

	UFUNCTION()
	void OnclickChangeOrientationButton();

	UFUNCTION()
	void ScreenOrientation(bool isLandscape);

        const FString MatchEmailPattern =
            TEXT("^((([a-zA-Z0-9_\\-\\.]+)@([a-zA-Z0-9_\\-\\.]+)\\.([a-zA-Z]{2,"
                 "5})){1})$");

        void OpenSettingPanel();
        void SetDefaultIdIfNotSet() ;
		void OpenCustomizeNonMonitize();
                void OpenHomePanel();

       void           GetReference();

  void SetButtonEvents();

  void SubscribeEvents();

  void SetInitialDetails();
};
