// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AvataryugData.generated.h"

/**
 * 
 */
UCLASS()
class AVATARYUGDEMO_API UAvataryugData : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	// TArray<FString> BlendshapeCategory = { "FaceShape", "EyeShape", "EyebrowShape", "NoseShape", "LipShape", "EarShape" };
 public:	   
	UFUNCTION()
    bool IsCommonGender(const FString& category)
    {
		if(category == "Top" || category == "Bottom" || category == "Outfit")
		{
			return false;
		}
        return true;
    }

	TArray<FString> bodytattos = {"FrontBodyTattoo","BackBodyTattoo","RightArmTattoo","LeftArmTattoo",
	"FrontRightLegTattoo","FrontLeftLegTattoo","BackRightLegTattoo","BackLeftLegTattoo",
	"RightHandTattoo","LeftHandTattoo","RightFootTattoo","LeftFootTattoo"
    };

	TArray<FString> CategoryForColorPanel = { "Hair", "Eyebrow", "Lips", "Facialhair"};
	UFUNCTION()
    bool IsCategoryForColorPanel(const FString& category)
    {
		return CategoryForColorPanel.Contains(category);
	}

	TArray<FString> BlendshapeCategory = { "FaceShape", "EyeShape", "EyebrowShape", "NoseShape","LipShape","EarShape"};
	
	UFUNCTION()
    bool IsBlendshapeCategory(const FString& category)
    {
		return BlendshapeCategory.Contains(category);
	}

	TArray<FString> HeadCategory = { "Hair", "Facialhair", "Headwear", "Eyewear"};

	UFUNCTION()
    bool IsHeadCategoty(const FString& category)
    {
		return HeadCategory.Contains(category);
	}

	TArray<FString> Head2DCategory = { "Eyebrow", "Eyeball", "Lips"};
	UFUNCTION()
    bool IsHead2DCategoty(const FString& category)
    {
		return Head2DCategory.Contains(category);
	}

	TArray<FString> FaceAccessary = { "Mouthwear", "Earwear", "Eyebrowswear", "Facewear", "Neckwear", "Nosewear" };
	UFUNCTION()
    bool IsFacewearAccessary(const FString& category)
    {
		return FaceAccessary.Contains(category);
	}

	UPROPERTY()
	TArray<FString> BodyTattoCategory = {"LeftHandTattoo","RightHandTattoo","LeftArmTattoo","RightArmTattoo",
	"LeftFootTattoo","RightFootTattoo","FrontLeftLegTattoo","FrontRightLegTattoo","BackBodyTattoo","FrontBodyTattoo",
	"BackLeftLegTattoo","BackRightLegTattoo","HeadTattoo"};

	UFUNCTION()
    bool IsBodyTattooCategory(const FString& category)
    {
		return BodyTattoCategory.Contains(category);
	}

	UPROPERTY()
	TArray<FString> BodyPartCategory ={ "Top","Bottom","Outfit", "Footwear","Handwear","Wristwear"};

	UFUNCTION()
    bool IsBodyPartCategory(const FString& category)
    {
		return BodyPartCategory.Contains(category);
	}	

	UPROPERTY()
	TArray<FString> HeadInventoryCategory = { "All","SkinTone","Hair","Eyebrow","Eyeball","Lips","Facialhair","Headwear",
    "Eyewear","Mouthwear","Earwear","Eyebrowswear","Facewear","Neckwear","Nosewear"};

	UPROPERTY()
	TArray<FString> FullInventoryCategory ={ "All","Top","Bottom","Outfit","Footwear","Handwear","Wristwear",
    "LeftHandTattoo","RightHandTattoo","LeftArmTattoo","RightArmTattoo","LeftFootTattoo","RightFootTattoo","FrontLeftLegTattoo",
    "FrontRightLegTattoo","BackBodyTattoo","BackLeftLegTattoo","BackRightLegTattoo","SkinTone","HeadTattoo"
    };

};
