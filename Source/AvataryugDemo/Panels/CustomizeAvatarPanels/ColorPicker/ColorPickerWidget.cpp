// Fill out your copyright notice in the Description page of Project Settings.

#include "ColorPickerWidget.h"

void UColorPickerWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (AvatarHandler == nullptr)
    {
        AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AAvatarHandler::StaticClass());
        AvatarHandler = Cast<AAvatarHandler>(FoundActor);
    }

    if (CurrentAvatarChanges == nullptr)
    {
        AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), ACurrentAvatarChanges::StaticClass());
        CurrentAvatarChanges = Cast<ACurrentAvatarChanges>(FoundActor);
        if (CurrentAvatarChanges == nullptr)
        {
            CurrentAvatarChanges = GetWorld()->SpawnActor<ACurrentAvatarChanges>();
        }
    }

    HueSlider->OnValueChanged.RemoveDynamic(this, &UColorPickerWidget::OnHueValueChange);
    HueSlider->OnValueChanged.AddDynamic(this, &UColorPickerWidget::OnHueValueChange);

    SaturationSlider->OnValueChanged.RemoveDynamic(this, &UColorPickerWidget::OnSaturationValueChange);
    SaturationSlider->OnValueChanged.AddDynamic(this, &UColorPickerWidget::OnSaturationValueChange);

    ValueSlider->OnValueChanged.RemoveDynamic(this, &UColorPickerWidget::OnValueSliderChange);
    ValueSlider->OnValueChanged.AddDynamic(this, &UColorPickerWidget::OnValueSliderChange);

    HueSlider->SetValue(0);
    SaturationSlider->SetValue(1);
    ValueSlider->SetValue(1);

    HueValue = 0;
    SaturationValue = 1;
    ValueValue = 1;

    UObject *slidermat = SaturationSlider->WidgetStyle.NormalBarImage.GetResourceObject();
    UMaterialInterface *mat = CastChecked<UMaterialInterface>(slidermat);
    DynamicMat = UMaterialInstanceDynamic::Create(mat, this);
    SaturationSlider->WidgetStyle.NormalBarImage.SetResourceObject(DynamicMat);
    SaturationSlider->WidgetStyle.HoveredBarImage.SetResourceObject(DynamicMat);
    DynamicMat->SetVectorParameterValue(FName("Color"), FLinearColor(1, 0, 0, 1));
    UAvataryugFunctionLibrary::HSVToLinearColor(HueValue, 1, 1, SliderCol);
    DynamicMat->SetVectorParameterValue(FName("Color"), SliderCol);
}

void UColorPickerWidget::OnClickFixedColorButton(FString categorys)
{
    SelectedColorCat = categorys;
    CustomColorPanel->SetVisibility(ESlateVisibility::Hidden);
    FixedColorPanel->SetVisibility(ESlateVisibility::Visible);
    if (FixedColorListView)
    {
        FixedColorListView->ClearListItems();
    }
    if (SelectedColorCat == "Hair")
    {
        float floatValue = hairColors.Num();
        float contaientGridCount = floatValue / 4;
        int myCeilInt = FMath::CeilToInt(contaientGridCount);
        for (int i = 0; i < myCeilInt; i++)
        {
            UColorListData *item = NewObject<UColorListData>();
            item->StartIndex = 4 * i;
            item->TotalCount = hairColors.Num();
            item->m_Colors = hairColors;
            item->category = SelectedColorCat;
            FixedColorListView->AddItem(item);
        }
    }
    if (SelectedColorCat == "Facialhair")
    {
        float floatValue = facialHairColor.Num();
        float contaientGridCount = floatValue / 4;
        int myCeilInt = FMath::CeilToInt(contaientGridCount);
        for (int i = 0; i < myCeilInt; i++)
        {
            UColorListData *item = NewObject<UColorListData>();
            item->StartIndex = 4 * i;
            item->TotalCount = facialHairColor.Num();
            item->m_Colors = facialHairColor;
            item->category = SelectedColorCat;
            FixedColorListView->AddItem(item);
        }
    }
    if (SelectedColorCat == "Eyebrow")
    {
        float floatValue = eyebrowColors.Num();
        float contaientGridCount = floatValue / 4;
        int myCeilInt = FMath::CeilToInt(contaientGridCount);
        for (int i = 0; i < myCeilInt; i++)
        {
            UColorListData *item = NewObject<UColorListData>();
            item->StartIndex = 4 * i;
            item->TotalCount = eyebrowColors.Num();
            item->m_Colors = eyebrowColors;
            item->category = SelectedColorCat;
            FixedColorListView->AddItem(item);
        }
    }
    if (SelectedColorCat == "Lips")
    {
        float floatValue = lipsColor.Num();
        float contaientGridCount = floatValue / 4;
        int myCeilInt = FMath::CeilToInt(contaientGridCount);
        for (int i = 0; i < myCeilInt; i++)
        {
            UColorListData *item = NewObject<UColorListData>();
            item->StartIndex = 4 * i;
            item->TotalCount = lipsColor.Num();
            item->m_Colors = lipsColor;
            item->category = SelectedColorCat;
            FixedColorListView->AddItem(item);
        }
    }
}

void UColorPickerWidget::OnClickCustomColorButton(FString categorys)
{
    SelectedColorCat = categorys;
    CustomColorPanel->SetVisibility(ESlateVisibility::Visible);
    FixedColorPanel->SetVisibility(ESlateVisibility::Hidden);
    
    float hueVal = 0;
    float saturationVal = 0;
    float valueVal = 0;
    FLinearColor selectedColor;
    if (SelectedColorCat == "Hair")
    {
        UAvataryugFunctionLibrary::HexToLinearColor(CurrentAvatarChanges->changePropColors.HairColor, selectedColor);
        UAvataryugFunctionLibrary::LinearColorToHSV(selectedColor, hueVal, saturationVal,valueVal);
    }
    if (SelectedColorCat == "Facialhair")
    {
        UAvataryugFunctionLibrary::HexToLinearColor(CurrentAvatarChanges->changePropColors.FacialHairColor, selectedColor);
        UAvataryugFunctionLibrary::LinearColorToHSV(selectedColor, hueVal, saturationVal,valueVal);
    }
    if (SelectedColorCat == "Eyebrow")
    {
        UAvataryugFunctionLibrary::HexToLinearColor(CurrentAvatarChanges->changePropColors.EyebrowColor, selectedColor);
        UAvataryugFunctionLibrary::LinearColorToHSV(selectedColor, hueVal, saturationVal,valueVal);
    }
    if (SelectedColorCat == "Lips")
    {
        UAvataryugFunctionLibrary::HexToLinearColor(CurrentAvatarChanges->changePropColors.LipColor, selectedColor);
        UAvataryugFunctionLibrary::LinearColorToHSV(selectedColor, hueVal, saturationVal,valueVal);
    }
    HueSlider->SetValue(hueVal);
    SaturationSlider->SetValue(saturationVal);
    ValueSlider->SetValue(valueVal);


    UAvataryugFunctionLibrary::HSVToLinearColor(hueVal, 1, 1, SliderCol);
    DynamicMat->SetVectorParameterValue(FName("Color"), SliderCol);
    ValueSlider->SetSliderBarColor(SliderCol);
}

void UColorPickerWidget::OnClickOkButton()
{
    this->SetVisibility(ESlateVisibility::Hidden);
}

void UColorPickerWidget::OnHueValueChange(float value)
{
    HueValue = value * 360;
    UAvataryugFunctionLibrary::HSVToLinearColor(HueValue, SaturationValue, ValueValue, OutColor);
    UAvataryugFunctionLibrary::HSVToLinearColor(HueValue, 1, 1, SliderCol);
    DynamicMat->SetVectorParameterValue(FName("Color"), SliderCol);
    ValueSlider->SetSliderBarColor(SliderCol);
    AvatarHandler->ForCustomizeAvatar->SetBodyPartColor(OutColor, SelectedColorCat);
}

void UColorPickerWidget::OnSaturationValueChange(float value)
{
    SaturationValue = value;
    UAvataryugFunctionLibrary::HSVToLinearColor(HueValue, SaturationValue, ValueValue, OutColor);
    UAvataryugFunctionLibrary::HSVToLinearColor(HueValue, 1, 1, SliderCol);
    DynamicMat->SetVectorParameterValue(FName("Color"), SliderCol);
    ValueSlider->SetSliderBarColor(SliderCol);
    AvatarHandler->ForCustomizeAvatar->SetBodyPartColor(OutColor, SelectedColorCat);
}

void UColorPickerWidget::OnValueSliderChange(float value)
{
    ValueValue = value;
    UAvataryugFunctionLibrary::HSVToLinearColor(HueValue, SaturationValue, ValueValue, OutColor);
    UAvataryugFunctionLibrary::HSVToLinearColor(HueValue, 1, 1, SliderCol);
    DynamicMat->SetVectorParameterValue(FName("Color"), SliderCol);
    ValueSlider->SetSliderBarColor(SliderCol);
    AvatarHandler->ForCustomizeAvatar->SetBodyPartColor(OutColor, SelectedColorCat);
}

void UColorPickerWidget::SetColorPickerStartValue(FLinearColor startColor, FString mainCat)
{
}