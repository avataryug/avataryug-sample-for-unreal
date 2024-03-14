// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../../../AvatarLoader/AvatarHandler.h"
#include "../../../DataHolders/ColorListData.h"
#include "Components/Button.h"
#include "Components/ListView.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CanvasPanel.h"
#include "Components/Slider.h"
#include "AvataryugFunctionLibrary.h"
#include "../../../DataHolders/CurrentAvatarChanges.h"
#include "ColorPickerWidget.generated.h"

/**
 *
 */
UCLASS()
class AVATARYUGDEMO_API UColorPickerWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class USlider *HueSlider;
	UPROPERTY(meta = (BindWidget))
	class USlider *SaturationSlider;
	UPROPERTY(meta = (BindWidget))
	class USlider *ValueSlider;

	UPROPERTY(meta = (BindWidget))
	class UListView *FixedColorListView;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel *CustomColorPanel;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel *FixedColorPanel;

	UPROPERTY()
  	ACurrentAvatarChanges *CurrentAvatarChanges;

	UPROPERTY()
	float HueValue;
	UPROPERTY()
	float SaturationValue;
	UPROPERTY()
	float ValueValue;

	UPROPERTY()
	FLinearColor OutColor;

	UPROPERTY()
	FLinearColor SliderCol;
	UFUNCTION()
	void OnHueValueChange(float value);
	UFUNCTION()
	void OnSaturationValueChange(float value);
	UFUNCTION()
	void OnValueSliderChange(float value);

public:
	UPROPERTY()
	FString SelectedColorCat;
	UPROPERTY()
	UMaterialInstanceDynamic *DynamicMat;
	UFUNCTION()
	void SetColorPickerStartValue(FLinearColor startColor, FString mainCat);

	UFUNCTION()
	void OnClickFixedColorButton(FString categorys);
	UFUNCTION()
	void OnClickCustomColorButton(FString categorys);
	UFUNCTION()
	void OnClickOkButton();

	UPROPERTY()
	AAvatarHandler *AvatarHandler;

	TArray<FString> eyebrowColors =
		{
			"#000000", "#0D0D0D", "#191919", "#262626", "#333333", "#404040", "#4D4D4D", "#595959", "#666666",
			"#737373", "#808080", "#8C8C8C", "#999999", "#A6A6A6", "#B3B3B3", "#BFBFBF", "#CCCCCC", "#D9D9D9",
			"#E6E6E6", "#F2F2F2", "#FFFFFF", "#C07C63", "#CC8973", "#D99684", "#E6A395", "#F2B0A5", "#FFBDB6",
			"#C39F85", "#CFAB96", "#DBB7A7", "#E7C3B8", "#F3CFC9", "#FFDBDA", "#B58A68", "#C19675", "#CEA282",
			"#D9AE8F", "#E5B99C", "#F1C4A9", "#FFD0B6", "#C6B48C", "#D2BF99", "#DEDAA5", "#EAE5B2", "#F6F0BF",
			"#FFFFCC", "#F2E8A9", "#F9F1B6", "#FFFFC4", "#FFFFD2", "#FFFFDF", "#FFFFEC", "#5F4031", "#6B4C3A",
			"#775845", "#826350", "#8E6E5B", "#9A7A67", "#A58672", "#B0927E", "#BC9E89", "#C8AA95", "#D4B6A0",
			"#E0C1AC", "#ECCDB7", "#F8D9C3", "#FFE4CE", "#331E12", "#403026", "#4D3A3B", "#5A444F", "#674F63",
			"#745A77", "#81658B", "#8E70A0", "#9B7BB4", "#A886C9", "#B591DD", "#C29CF2", "#CFA7FF"};
	TArray<FString> hairColors =
		{
			"#000000", "#0D0D0D", "#191919", "#262626", "#333333", "#404040", "#4D4D4D", "#595959", "#666666",
			"#737373", "#808080", "#8C8C8C", "#999999", "#A6A6A6", "#B3B3B3", "#BFBFBF", "#CCCCCC", "#D9D9D9",
			"#E6E6E6", "#F2F2F2", "#FFFFFF", "#C07C63", "#CC8973", "#D99684", "#E6A395", "#F2B0A5", "#FFBDB6",
			"#C39F85", "#CFAB96", "#DBB7A7", "#E7C3B8", "#F3CFC9", "#FFDBDA", "#B58A68", "#C19675", "#CEA282",
			"#D9AE8F", "#E5B99C", "#F1C4A9", "#FFD0B6", "#C6B48C", "#D2BF99", "#DEDAA5", "#EAE5B2", "#F6F0BF",
			"#FFFFCC", "#F2E8A9", "#F9F1B6", "#FFFFC4", "#FFFFD2", "#FFFFDF", "#FFFFEC", "#5F4031", "#6B4C3A",
			"#775845", "#826350", "#8E6E5B", "#9A7A67", "#A58672", "#B0927E", "#BC9E89", "#C8AA95", "#D4B6A0",
			"#E0C1AC", "#ECCDB7", "#F8D9C3", "#FFE4CE", "#331E12", "#403026", "#4D3A3B", "#5A444F", "#674F63",
			"#745A77", "#81658B", "#8E70A0", "#9B7BB4", "#A886C9", "#B591DD", "#C29CF2", "#CFA7FF"};
	TArray<FString> lipsColor =
		{
			"#FFB6C1", "#ffcecf", "#ffbec2", "#f69e9e", "#f98d8b", "#fa7b7a", "#ff7e82", "#e55a5b", "#d74b4b",
			"#c33d3c", "#bc3031", "#db948c", "#d97d76", "#d17369", "#c0655c", "#be5854", "#ae4c47", "#ab4948",
			"#7c2d2e", "#622625", "#4d1d1b", "#f69ae5", "#fb63b8", "#ff3090", "#fa006e", "#e00050", "#fc0001",
			"#d40000", "#ae0001", "#9a0000", "#dedede", "#8e8e8e", "#797979", "#434343", "#0d0d0d", "#79c687",
			"#4cb15f", "#409550", "#2f6c3a", "#204928", "#FFC0CB", "#FF69B4", "#FF1493", "#FFB6C1", "#FF7F50",
			"#FF4500", "#FF0000", "#DC143C", "#C71585", "#B22222", "#8B0000", "#FFA07A", "#FA8072", "#E9967A",
			"#FF8C00", "#FF7F00", "#FFD700", "#FFFF00", "#FFDAB9", "#FFE4E1", "#FFA500", "#FF6347", "#FFA07A",
			"#E9967A", "#FF1493", "#FF69B4", "#FFC0CB", "#FF69B4", "#FF1493", "#FF00FF", "#8A2BE2", "#800080",
			"#4B0082", "#483D8B", "#6A5ACD", "#7B68EE", "#4169E1", "#0000FF", "#0000CD", "#00008B", "#000080", "#00008B"};
	TArray<FString> facialHairColor =
		{
			"#000000", "#0D0D0D", "#191919", "#262626", "#333333", "#404040", "#4D4D4D", "#595959", "#666666",
			"#737373", "#808080", "#8C8C8C", "#999999", "#A6A6A6", "#B3B3B3", "#BFBFBF", "#CCCCCC", "#D9D9D9",
			"#E6E6E6", "#F2F2F2", "#FFFFFF", "#C07C63", "#CC8973", "#D99684", "#E6A395", "#F2B0A5", "#FFBDB6",
			"#C39F85", "#CFAB96", "#DBB7A7", "#E7C3B8", "#F3CFC9", "#FFDBDA", "#B58A68", "#C19675", "#CEA282",
			"#D9AE8F", "#E5B99C", "#F1C4A9", "#FFD0B6", "#C6B48C", "#D2BF99", "#DEDAA5", "#EAE5B2", "#F6F0BF",
			"#FFFFCC", "#F2E8A9", "#F9F1B6", "#FFFFC4", "#FFFFD2", "#FFFFDF", "#FFFFEC", "#5F4031", "#6B4C3A",
			"#775845", "#826350", "#8E6E5B", "#9A7A67", "#A58672", "#B0927E", "#BC9E89", "#C8AA95", "#D4B6A0",
			"#E0C1AC", "#ECCDB7", "#F8D9C3", "#FFE4CE", "#331E12", "#403026", "#4D3A3B", "#5A444F", "#674F63",
			"#745A77", "#81658B", "#8E70A0", "#9B7BB4", "#A886C9", "#B591DD", "#C29CF2", "#CFA7FF"};
};
