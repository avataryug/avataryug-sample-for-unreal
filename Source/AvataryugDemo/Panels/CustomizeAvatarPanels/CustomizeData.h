
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../../DataHolders/EconomyItemHolder.h"
#include "GameStructs.h"
#include "AvatarPresetsAPI/AvatarPresetsModel.h"
#include "CustomizeData.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnClickSubCategory, FString, subCategory);

UCLASS()
class UCustomizeListData : public UObject
{
      GENERATED_BODY()
public:
      UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
      int StartIndex;
      UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
      int TotalCount;
      UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
      TArray<FEconomyItems> currentSelectedItems;
      UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
      TArray<FExpression> expressionLists;
      UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
      FString dataType;
      UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
      TArray<FClip> clipLists;
      UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
      TArray<FGetAvatarPresetsResultDataInner> PresetAvatarLists;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    TArray<FUserAvatar> userAvatars;
      

};

UCLASS()
class UCustomizeSubCatListData : public UObject
{
      GENERATED_BODY()
public:
      UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
      int Index;
      UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
      FString Category;
      UPROPERTY(BlueprintReadWrite, Category = "Avataryug")
      FOnClickSubCategory ClickSubCategory;
};

UCLASS()
class AVATARYUGDEMO_API UCustomizeData : public UObject
{
      GENERATED_BODY()
};
