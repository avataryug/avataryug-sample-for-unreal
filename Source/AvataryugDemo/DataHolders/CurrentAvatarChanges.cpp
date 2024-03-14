// Fill out your copyright notice in the Description page of Project Settings.

#include "CurrentAvatarChanges.h"
#include "GameStructs.h"

// Sets default values
ACurrentAvatarChanges::ACurrentAvatarChanges()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACurrentAvatarChanges::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACurrentAvatarChanges::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool ACurrentAvatarChanges::IsItemPresent(FString Id)
{
	// UE_LOG(LogTemp, Display,TEXT("======> BP AvatarHandler->currentProps.Props.Num()%d"),currentProps.props.Num());
	bool IsPresent = false;
	if (currentProps.props.Num() > 0)
	{
		// Assuming currentProps.props is an array or TArray of items
		for (const FProp &Item : currentProps.props)
		{
			if (Item.ID == Id)
			{
				IsPresent = true;
				break;
			}
		}
	}
	// if(!Id.IsEmpty())
	// {
	// 	for (int i = 0; i < currentProps.props.Num(); i++)
	// 	{
	// 		if (currentProps.props[i].ID == Id)
	// 		{
	// 			IsPresent = true;
	// 			break;
	// 		}

	// 	}
	// }
	return IsPresent;
}

bool ACurrentAvatarChanges::IsPresent(FString id)
{
	bool isPresent = false;
	for (int i = 0; i < changedProps.props.Num(); i++)
	{
		if (changedProps.props[i].ID == id)
		{
			isPresent = true;
			break;
		}
	}
	return isPresent;
}

void ACurrentAvatarChanges::ChangeBlendshapeValue(FBlendShapeValue blendShape)
{
	for (int i = 0; i < changeBlendShapes.Num(); i++)
	{
		if (changeBlendShapes[i].shapekeys == blendShape.shapekeys)
		{
			changeBlendShapes[i].value = blendShape.value;
		}
	}
}

void ACurrentAvatarChanges::AddChangeProps(TArray<FEconomyItems> Items)
{
	changedProps.props.Empty();

	for (const FEconomyItems &Item : Items)
	{
		FProp NewProp;
		// Set the properties of the new Prop
		NewProp.CoreBucket = Item.coreBucket;
		NewProp.ID = Item.iD;
		if (!IsPresent(Item.iD))
		{
			changedProps.props.Add(NewProp);
		}
	}
}

void ACurrentAvatarChanges::Logout()
{
	currentProps = FProps();
	TArray<FBlendShapeValue> CurrentBlendShapes; // Declare a new TArray
	currentBlendShapes = CurrentBlendShapes;
	currentpropColors = FPropColors();
	changedProps = FProps(); // Assuming changedProps is a USTRUCT or UObject
	TArray<FBlendShapeValue> ChangeBlendShapes;
	changeBlendShapes = ChangeBlendShapes; // Assuming changeblendShapes is a TArray
	changePropColors = FPropColors();
}

void ACurrentAvatarChanges::ResetChanges()
{
	FProps tempprop = currentProps;
	changedProps = tempprop;

	TArray<FBlendShapeValue> tempblend;
	changeBlendShapes = tempblend;

	FPropColors tempPropColors;
	changePropColors = tempPropColors;
}
float ACurrentAvatarChanges::IsPresentInChangedShape(FString ShapeKey)
{
	float isPresent = 0;
	for (const FBlendShapeValue &item : changeBlendShapes) // Assuming CurrentBlendShapes is a TArray
	{
		if (item.shapekeys == ShapeKey)
		{
			isPresent = item.value;
			break;
		}
	}

	return isPresent;
}
bool ACurrentAvatarChanges::isPresentInCurrent(FString id)
{
	bool isPresent = false;
	for (const FProp &Item : currentProps.props)
	{
		if (Item.ID == id)
		{
			isPresent = true;
			break;
		}
	}
	return isPresent;
}

bool ACurrentAvatarChanges::isPresentInCurrentShape(FBlendShapeValue blendShape)
{
	bool isPresent = false;
	for (const FBlendShapeValue &Item : currentBlendShapes) // Assuming CurrentBlendShapes is a TArray
	{
		if (Item.shapekeys == blendShape.shapekeys)
		{
			if (Item.value != blendShape.value)
			{
				isPresent = true;
				break;
			}
		}
	}
	return isPresent;
}
void ACurrentAvatarChanges::OnChangeSkinColor(FString category, FLinearColor OutColor)
{
	FLinearColor outColor = OutColor;
	FLinearColor tempcat = OutColor;

	if (category == "Hair")
	{
		FString HexColor = FString::Printf(TEXT("#%02X%02X%02X"), FMath::RoundToInt(outColor.R * 255), FMath::RoundToInt(outColor.G * 255), FMath::RoundToInt(outColor.B * 255));
		changePropColors.HairColor = HexColor;
	}
	if (category == "Facialhair")
	{
		// HeadDynamicMaterial->SetVectorParameterValue(FName(TEXT("BeardColor")), OutColor);
		FString HexColor = FString::Printf(TEXT("#%02X%02X%02X"), FMath::RoundToInt(outColor.R * 255), FMath::RoundToInt(outColor.G * 255), FMath::RoundToInt(outColor.B * 255));
		changePropColors.FacialHairColor = HexColor;
	}
	if (category == "Eyebrow")
	{
		FString HexColor = FString::Printf(TEXT("#%02X%02X%02X"), FMath::RoundToInt(outColor.R * 255), FMath::RoundToInt(outColor.G * 255), FMath::RoundToInt(outColor.B * 255));
		changePropColors.EyebrowColor = HexColor;
	}
	if (category == "Lips")
	{
		FString HexColor = FString::Printf(TEXT("#%02X%02X%02X"), FMath::RoundToInt(outColor.R * 255), FMath::RoundToInt(outColor.G * 255), FMath::RoundToInt(outColor.B * 255));
		changePropColors.LipColor = HexColor;
	}
}