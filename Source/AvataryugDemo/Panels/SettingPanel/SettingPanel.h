// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuthenticationAPI/AuthenticationHandler.h"
#include "AuthenticationAPI/AuthenticationModels.h"
#include "AuthenticationAPI/AuthenticationRequest.h"
#include "AuthenticationAPI/AuthenticationAPI.h"
#include "CommonModels.h"

#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"
#include "UserAccountManagementAPI/UserAccountManagementModels.h"
#include "UserAccountManagementAPI/UserAccountManagementRequest.h"
#include "DefaultAPI/DefaultHandler.h"
#include "DefaultAPI/DefaultModels.h"
#include "DefaultAPI/DefaultAPI.h"
#include "DefaultAPI/DefaultRequest.h"
#include "../../DataHolders/UserDetailHolder.h"
#include "../../Utilitys/APIEvents.h"
#include "SettingPanel.generated.h"

/**
 *
 */
UCLASS()
class AVATARYUGDEMO_API USettingPanel : public UUserWidget
{
	GENERATED_BODY()

protected:
	void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UButton *Settings_BackButton;

	UPROPERTY(meta = (BindWidget))
	class UButton *UpdateDisplayNameButton;

	UPROPERTY(meta = (BindWidget))
	class UButton *AddDisplayNameButton;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox *EnterAddDisplayNameField;

	UPROPERTY(meta = (BindWidget))
	class UButton *LinkIOSDeviceButton;

	UPROPERTY(meta = (BindWidget))
	class UButton *LinkFaceBookButton;

	UPROPERTY(meta = (BindWidget))
	class UButton *LinkCustomIDButton;

	UPROPERTY(meta = (BindWidget))
	class UButton *LinkAppleButton;

	UPROPERTY(meta = (BindWidget))
	class UButton *LinkAndroiddeviceIDButton;

	UPROPERTY(meta = (BindWidget))
	class UButton *LinkGoggleButton;

	UPROPERTY(meta = (BindWidget))
	class UButton *DeleteUserButton;

	UPROPERTY(meta = (BindWidget))
	class UButton *LogoutButton;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel *AddEmailPasswordPanel;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel *AddDisplayNamePanel;

	UPROPERTY(meta = (BindWidget))
	class UButton *CloseButtonDisplayName;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock *LinkIOSText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock *LinkFBText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock *LinkCustomText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock *LinkAppleText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock *LinkAndroidDeviceText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock *LinkGoggleText;

	UPROPERTY(meta = (BindWidget))
	class UScrollBox *ButtonsScrollBox;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel *Setting_ChangePasswordPoPup;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel *Setting_AddDisplayNamePopUp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isLinkedGoggle = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isLoginCustomID = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isFacebookLogin = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isAndroidDeviceID = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isLinkApple = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isLinkIOSDeviceID = false;

	UFUNCTION()
	void OnClickUpdateDisplayName();

	UFUNCTION()
	void OnClickChangePassword();
	//=============UNLINK CUSTOM=================
	FOnUnlinkCustomIDResult OnUnlinkCustomIDResult;

	UFUNCTION()
	void UnLinkCustomIDReply(FUnlinkCustomIDResult result);

	FOnApiException OnUnlinkCustomIException;

	UFUNCTION()
	void UnLinkCustomIDError(FApiException result);

	UFUNCTION()
	void OnClickLinkCustom();

	UFUNCTION()
	void OnClicksettingBackButton();

	//==================LINK CUSTOM================

	// FOnLoginWithCustomIDResult LoginCustomIDResult;

	// UFUNCTION()
	// void OnLoginCustomIdReply(FLoginWithCustomIDResult result);

	// FOnApiException CustomIdApiException;

	// UFUNCTION()
	// void OnLoginCustomIdError(FApiException result);

	//---------------NEW------------------
	FOnLinkCustomIDResult LinkCustomIDResult;

	UFUNCTION()
	void LinkCustomIDReply(FLinkCustomIDResult result);

	FOnApiException OnLinkCustomIDApiException;

	UFUNCTION()
	void LinkCustomIDError(FApiException result);

	//=================== UNLINK ANDROID===========================
	UFUNCTION()
	void OnClickLinkAndrtoidDeviceID();

	FOnUnlinkAndroidDeviceIDResult UnlinkAndroidDeviceIDResult;

	UFUNCTION()
	void UnlinkAndroidDeviceIDReply(FUnlinkAndroidDeviceIDResult result);

	FOnApiException UnlinkAndroidDeviceIDApiException;

	UFUNCTION()
	void UnlinkAndroidDeviceIDError(FOnApiException result);

	//=================== LINK ANDROID===========================
	// FOnLoginWithAndroidDeviceIDResult LoginWithAndroidResult;

	// UFUNCTION()
	// void OnLoginAndroidIDReply(FLoginWithAndroidDeviceIDResult result);

	// FOnApiException OnLoginWithAndroidIDException;

	// UFUNCTION()
	// void OnLoginAndroidIDError(FApiException result);

	//-----------------NEw Android---------------
	FOnLinkAndroidDeviceIDResult LinkAndroidDeviceIDResult;

	UFUNCTION()
	void LinkAndroidDeviceIDReply(FLinkAndroidDeviceIDResult result);

	FOnApiException LinkAndroidDeviceIDApiException;

	UFUNCTION()
	void LinkAndroidIDError(FApiException result);

	//=================== UNLINK IOS DEVICE===========================
	UFUNCTION()
	void OnClickLinkIOSDeviceID();

	FOnUnlinkIOSDeviceIDResult OnUnlinkIOSDeviceIDResult;

	UFUNCTION()
	void OnUnlinkIOSDeviceIDReply(FUnlinkIOSDeviceIDResult result);

	FOnApiException UnlinkIOSDeviceIDApiException;

	UFUNCTION()
	void OnUnlinkIOSDeviceIDError(FApiException result);

	//=================== LINK IOS DEVICE===========================

	// FOnLoginWithIOSDeviceIDResult LoginWithIOSDeviceIDResult;

	// UFUNCTION()
	// void LoginIOSDeviceIDReply(FLoginWithIOSDeviceIDResult result);

	// FOnApiException LoginWithIOSDeviceIDApiException;

	// UFUNCTION()
	// void OnLoginIOSDeviceIDError(FApiException result);

	//-----------------NEW IOS DEVICE------

	FOnLinkIOSDeviceIDResult NewLinkIOSDeviceIDResult;
	// FOnLinkIOSDeviceIDResult
	UFUNCTION()
	void LinkIOSDeviceIDReply(FLinkIOSDeviceIDResult result);

	FOnApiException NewLinkIOSDeviceIDApiException;

	UFUNCTION()
	void LinkIOSDeviceIDError(FApiException result);

	//=================== LINK GOGGLE ACCOUNT===========================
	UFUNCTION()
	void OnClickLinkGoggleAccount();

	FOnLinkGoogleAccountResult LinkWithGoogleResult;

	UFUNCTION()
	void LinkGoggleAccountReply(FLinkGoogleAccountResult result);

	FOnApiException LinkWithGoogleApiException;

	UFUNCTION()
	void LinkGoggleAccountError(FApiException result);

	FOnUnlinkGoogleAccountResult UnlinkGoogleAccounResult;

	UFUNCTION()
	void UnLinkGoggleAccountReply(FUnlinkGoogleAccountResult result);

	FOnApiException UnLinkWithGoogleApiException;

	UFUNCTION()
	void UnLinkGoggleAccountError(FApiException result);
	//=================== LINK Apple===========================
	UFUNCTION()
	void OnClickLinkApple();

	FOnLinkAppleResult OnLinkAppleResult;

	UFUNCTION()
	void OnLinkAppleReply(FLinkAppleResult result);

	FOnApiException OnLinkAppleApiException;

	UFUNCTION()
	void OnLinkAppleError(FApiException result);

	FOnUnlinkAppleResult UnlinkAppleResult;

	UFUNCTION()
	void UnLinkAppleReply(FUnlinkAppleResult result);

	FOnApiException OnUnLinkAppleApiException;

	UFUNCTION()
	void UnlinkAppleError(FApiException result);

	//=====================LINK FB ACCOUNT=======================

	UFUNCTION()
	void OnClickLinkFacebookAccount();

	FOnLinkFacebookAccountResult OnLinkFacebookAccountResult;

	UFUNCTION()
	void OnLinkFacebookAccountReply(FLinkFacebookAccountResult result);

	FOnApiException OnLinkFacebookAccountApiException;

	UFUNCTION()
	void OnLinkFacebookAccountError(FApiException result);

	FOnUnlinkFacebookAccountResult OnUnlinkFacebookAccountResult;

	UFUNCTION()
	void OnUnlinkFacebookAccountReply(FUnlinkFacebookAccountResult result);

	FOnApiException OnUnlinkFacebookAccountApiException;

	UFUNCTION()
	void OnUnlinkFacebookAccountError(FApiException result);

	//================END LINK FB ACCOUNT==========================

	//=====================DELETE USER=========================

	UFUNCTION()
	void OnClickDeleteUser();

	FOnDeleteUserResponse OnDeleteUserResponse;

	UFUNCTION()
	void OnDeleteUserReply(FDeleteUserResponse result);

	FOnApiException OnDeleteUserApiException;

	UFUNCTION()
	void OnDeleteUserResponseError(FApiException result);

	//=================END===DELETE USER=======================

	//=================Add DISPLAY NAME=======================

	UFUNCTION()
	void OnClickAddDisplayName();

	UPROPERTY(meta = (BindWidget))
	class UTextBlock *AddDisplayNameErrorText;

	UFUNCTION()
	void EnterAddDisplayNameTextChanged(const FText &Text);

	FOnUpdateUserProjectDisplayNameResult OnUpdateUserProjectDisplayNameResult;

	UFUNCTION()
	void OnUpdateUserProjectDisplayNameReply(FUpdateUserProjectDisplayNameResult result);

	FOnApiException OnUpdateUserProjectDisplayNameApiException;

	UFUNCTION()
	void OnUpdateUserProjectDisplayNameError(FApiException result);

	//=================END DISPLAY NAME=======================
	//=================CHANGE PASSWORD =======================
	UPROPERTY(meta = (BindWidget))
	class UButton *ChangePasswordButton;

	UPROPERTY(meta = (BindWidget))
	class UButton *CloseChangepassword_Button;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox *CP_EnterOldPasswordField;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox *CP_EnterNewPasswordField;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox *CP_EnterConfirmPasswordField;

	UPROPERTY(meta = (BindWidget))
	class UButton *CP_ChangePasswordButton;

	UFUNCTION()
	void OnClickUpddateEmailPassword();

	FOnChangePasswordResponse OnChangePasswordResult;

	UFUNCTION()
	void OnChangePasswordReply(FChangePasswordResponse Result);

	FOnApiException OnChangePasswordApiException;

	UFUNCTION()
	void OnChangePasswordError(FApiException result);
	UFUNCTION()
	void OnSettingScreenOrientation(bool isLandscape);

	//=================END==CHANGE PASSWORD =======================

public:
	UFUNCTION()
	void OnClickCloseUpdateDisplayName();

	UFUNCTION()
	void OnClickCloseChangePassword();

	UFUNCTION()
	void LoadSettingPanelData();

	AUserDetailHolder *UserDetailHolder;

	AAPIEvents *APIEvents;

	UFUNCTION()
	void OnClickLogout();
};
