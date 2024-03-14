// Fill out your copyright notice in the Description page of Project Settings.

#include "LoadTextureFromURL.h"
#include "Http.h"
#include "AvataryugRuntimeSetting.h"
#include "ImageUtils.h"
#define UI UI_ST
THIRD_PARTY_INCLUDES_START
#include "openssl/evp.h"
THIRD_PARTY_INCLUDES_END
#undef UI

void ULoadTextureFromURL::LoadTexture(FString url, FOnReceiveTexture texturecallback)
{
    FHttpRequestRef request = FHttpModule::Get().CreateRequest();
    request->SetVerb("GET");
    request->SetURL(url);
    request->OnProcessRequestComplete().BindLambda([](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bConnectedSuccessfully, FOnReceiveTexture texturecallback)
                                                   {
    if (bConnectedSuccessfully && HttpResponse.IsValid())
    {
        TArray<uint8> ImageData = HttpResponse->GetContent();
        UTexture2D *textures = FImageUtils::ImportBufferAsTexture2D(ImageData);
        texturecallback.ExecuteIfBound(textures);
        } },
                                                   texturecallback);
    request->ProcessRequest();
}
void ULoadTextureFromURL::LoadByte(FString url,
                                   TFunction<void(TArray<uint8>)> result) {

   FHttpRequestRef request = FHttpModule::Get().CreateRequest();
    request->SetVerb("GET");
    request->SetURL(url);
    request->OnProcessRequestComplete().BindLambda([](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bConnectedSuccessfully, TFunction<void(TArray<uint8>)> result)
                                                   {
    if (bConnectedSuccessfully && HttpResponse.IsValid())
    {
        TArray<uint8> bytedata = HttpResponse->GetContent();
        if(result){
            result(bytedata);
        }
    } },
                                                   result);
    request->ProcessRequest();
}
void ULoadTextureFromURL::LoadByte(FString url, FOnReceiveData datacallback)
{
    FHttpRequestRef request = FHttpModule::Get().CreateRequest();
    request->SetVerb("GET");
    request->SetURL(url);
    request->OnProcessRequestComplete().BindLambda([](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bConnectedSuccessfully, FOnReceiveData datacallback)
                                                   {
    if (bConnectedSuccessfully && HttpResponse.IsValid())
    {
        TArray<uint8> Data = HttpResponse->GetContent();
        datacallback.ExecuteIfBound(Data);
    } },
                                                   datacallback);
    request->ProcessRequest();
}

TArray<uint8> ULoadTextureFromURL::GetModelByte(TArray<uint8> inputdata)
{
    FString keys = GetDefault<UAvataryugRuntimeSetting>()->SecrectKey;
    FString ivs = GetDefault<UAvataryugRuntimeSetting>()->SecrectIV;
    TArray<uint8> bytekey = StringToByteArray(keys);
    TArray<uint8> byteiv = StringToByteArray(ivs);

    return decryptAES(inputdata, bytekey, byteiv);
}

TArray<uint8> ULoadTextureFromURL::StringToByteArray(const FString &Key)
{
    TArray<uint8> ByteArray;
    const int32 KeyLen = Key.Len();

    if (KeyLen % 2 != 0)
    {
        // The input string must have an even number of characters
        return ByteArray;
    }

    ByteArray.Init(0, KeyLen / 2);
    for (int32 i = 0; i < KeyLen; i += 2)
    {
        FString Substring = Key.Mid(i, 2);
        char *EndPtr;
        uint8 ByteValue = (uint8)strtoul(TCHAR_TO_ANSI(*Substring), &EndPtr, 16);
        ByteArray[i / 2] = ByteValue;
    }

    return ByteArray;
}
TArray<uint8> ULoadTextureFromURL::decryptAES(const TArray<uint8> &CipherText, const TArray<uint8> &Key, const TArray<uint8> &IV)
{
    if (CipherText.Num() == 0 || Key.Num() == 0 || IV.Num() == 0)
    {
        return CipherText;
    }

    // Set up variables for decryption
    int32 InputSize = CipherText.Num();

    // Initialize OpenSSL context
    const EVP_CIPHER *Cipher = EVP_aes_128_cbc();
    EVP_CIPHER_CTX *Context = EVP_CIPHER_CTX_new();
    EVP_CIPHER_CTX_init(Context);

    // Set up decryption
    EVP_DecryptInit_ex(Context, Cipher, nullptr, Key.GetData(), IV.GetData());

    // Allocate space for output buffer
    TArray<uint8> OutData;
    OutData.SetNumZeroed(InputSize + EVP_MAX_BLOCK_LENGTH);

    // Decrypt data
    int OutLength = 0;
    EVP_DecryptUpdate(Context, OutData.GetData(), &OutLength, CipherText.GetData(), InputSize);
    OutData.SetNum(OutLength);

    // Finalize decryption and remove padding
    int FinalOutLength = 0;
    EVP_DecryptFinal_ex(Context, OutData.GetData() + OutLength, &FinalOutLength);
    OutData.SetNum(OutLength + FinalOutLength);
    OutData = unpad(OutData, AES_BLOCK_SIZE);

    // Clean up OpenSSL context
    EVP_CIPHER_CTX_free(Context);

    return OutData;
}

TArray<uint8> ULoadTextureFromURL::unpad(const TArray<uint8> &Data, int BlockSize)
{
    if (Data.Num() == 0 || BlockSize == 0)
    {
        return Data;
    }

    // Calculate padding value
    uint8 PaddingValue = Data.Last();
    if (PaddingValue <= 0 || PaddingValue > BlockSize)
    {
        return Data;
    }

    // Check if padding is valid
    int PaddingStart = Data.Num() - PaddingValue;
    for (int i = PaddingStart; i < Data.Num(); i++)
    {
        if (Data[i] != PaddingValue)
        {
            return Data;
        }
    }

    // Remove padding
    TArray<uint8> UnpaddedData;
    UnpaddedData.Append(Data.GetData(), PaddingStart);

    return UnpaddedData;
}

void ULoadTextureFromURL::LoadByte(FString url, TFunction<void(UTexture2D *)> result)
{
    FHttpRequestRef request = FHttpModule::Get().CreateRequest();
    request->SetVerb("GET");
    request->SetURL(url);
    request->OnProcessRequestComplete().BindLambda([](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bConnectedSuccessfully, TFunction<void(UTexture2D *)> result)
                                                   {
    if (bConnectedSuccessfully && HttpResponse.IsValid())
    {
        TArray<uint8> ImageData = HttpResponse->GetContent();
        UTexture2D *textures = FImageUtils::ImportBufferAsTexture2D(ImageData);
        if(result){
            result(textures);
        }
    } },
                                                   result);
    request->ProcessRequest();
}