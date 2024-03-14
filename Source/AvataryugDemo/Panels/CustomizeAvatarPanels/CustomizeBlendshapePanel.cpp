// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomizeBlendshapePanel.h"

void UCustomizeBlendshapePanel::NativeConstruct()
{
    Super::NativeConstruct();

    if (APIEvents == nullptr)
    {
        AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AAPIEvents::StaticClass());
        APIEvents = Cast<AAPIEvents>(FoundActor);
        if (APIEvents == nullptr)
        {
            APIEvents = GetWorld()->SpawnActor<AAPIEvents>();
        }
    }
    if (AvatarHandler == nullptr)
    {
        AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AAvatarHandler::StaticClass());
        AvatarHandler = Cast<AAvatarHandler>(FoundActor);
    }

    HorizontalSlider->OnValueChanged.RemoveDynamic(this, &UCustomizeBlendshapePanel::OnHorizontalValueChange);
    HorizontalSlider->OnValueChanged.AddDynamic(this, &UCustomizeBlendshapePanel::OnHorizontalValueChange);
    
    VerticalSlider->OnValueChanged.RemoveDynamic(this, &UCustomizeBlendshapePanel::OnVerticalValueChange);
    VerticalSlider->OnValueChanged.AddDynamic(this, &UCustomizeBlendshapePanel::OnVerticalValueChange);
    
    HorizontalSlider->SetMinValue(-1);
    HorizontalSlider->SetMaxValue(1);

    VerticalSlider->SetMinValue(-1);
    VerticalSlider->SetMaxValue(1);

    BackButton->OnClicked.RemoveDynamic(this, &UCustomizeBlendshapePanel::OnBackButtonClick);
    BackButton->OnClicked.AddDynamic(this, &UCustomizeBlendshapePanel::OnBackButtonClick);

    ProceedButton->OnClicked.RemoveDynamic(this, &UCustomizeBlendshapePanel::OnProcessButtonClick);
    ProceedButton->OnClicked.AddDynamic(this, &UCustomizeBlendshapePanel::OnProcessButtonClick);

    FrontHeadButton->OnClicked.RemoveDynamic(this, &UCustomizeBlendshapePanel::OnFrontHeadButtonClick);
    FrontHeadButton->OnClicked.AddDynamic(this,&UCustomizeBlendshapePanel::OnFrontHeadButtonClick);

    SideHeadButton->OnClicked.RemoveDynamic(this, &UCustomizeBlendshapePanel::OnSideHeadButtonClick);
    SideHeadButton->OnClicked.AddDynamic(this, &UCustomizeBlendshapePanel::OnSideHeadButtonClick);

    ShowHideModels->OnCheckStateChanged.RemoveDynamic(this, &UCustomizeBlendshapePanel::OnShowHideModels);
    ShowHideModels->OnCheckStateChanged.AddDynamic(this, &UCustomizeBlendshapePanel::OnShowHideModels);

    ShowHideModels->SetIsChecked(true);

    // OnBlendshapePoint.RemoveDynamic(this, &UCustomizeBlendshapePanel::OnclickBlendshapePoint);
    // OnBlendshapePoint.AddDynamic(this, &UCustomizeBlendshapePanel::OnclickBlendshapePoint);
    APIEvents->OnBlendshapePoint.AddDynamic(this, &UCustomizeBlendshapePanel::OnclickBlendshapePoint);

     VerticalSlider->SetVisibility(ESlateVisibility::Hidden);
    HorizontalSlider->SetVisibility(ESlateVisibility::Hidden);
   
}

void UCustomizeBlendshapePanel::OnShowHideModels(bool bNewValue)
{
    // AvatarLoader->ShowHideItems(bNewValue);
    if(bNewValue)
    {
        UE_LOG(LogTemp,Display,TEXT("SHOW FACE ITEMS---->>"));
        if(AvatarHandler->ForCustomizeAvatar != nullptr)
        {
            UE_LOG(LogTemp,Display,TEXT("AVATAR LOADER IS PRESENT---->>"));
            AvatarHandler->ForCustomizeAvatar->ShowHideItems(bNewValue);
        }

    }
    if(!bNewValue)
    {
        UE_LOG(LogTemp,Display,TEXT("HIDE FACE ITEMS---->>"));
        /* Removed this Avatar Loader $$ 
        if (AvatarLoader == nullptr)
        {
            AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AAvatarLoader::StaticClass());
            AvatarLoader = Cast<AAvatarLoader>(FoundActor);
            if (AvatarLoader == nullptr)
            {
                AvatarLoader = GetWorld()->SpawnActor<AAvatarLoader>();
            }
        }
        
        if(AvatarLoader != nullptr)
        {
            UE_LOG(LogTemp,Display,TEXT("AVATAR LOADER IS PRESENT---->>"));
            // AvatarLoader->ShowHideItems(bNewValue);
            AvatarLoader->ShowHideItems(bNewValue);
        }
        */
        if (AvatarHandler == nullptr)
        {
            AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AAvatarHandler::StaticClass());
            AvatarHandler = Cast<AAvatarHandler>(FoundActor);
            if (AvatarHandler == nullptr)
            {
                AvatarHandler = GetWorld()->SpawnActor<AAvatarHandler>();
            }
        }
        if(AvatarHandler != nullptr)
        {
            UE_LOG(LogTemp,Display,TEXT("AVATAR LOADER IS PRESENT---->>"));
            // AvatarLoader->ShowHideItems(bNewValue);
            if(AvatarHandler->ForCustomizeAvatar != nullptr)
            {
                UE_LOG(LogTemp,Display,TEXT("AVATAR LOADER IS PRESENT---->>"));
                AvatarHandler->ForCustomizeAvatar->ShowHideItems(bNewValue);
            }
        }
    }
}

void UCustomizeBlendshapePanel::LoadBlendPanel()
{
         VerticalSlider->SetVisibility(ESlateVisibility::Hidden);
    HorizontalSlider->SetVisibility(ESlateVisibility::Hidden);
   AvatarHandler->ForCustomizeAvatar->DestroySpawnCustomizePoint();
   AvatarHandler->stopRotate =true;
    if (AvatarHandler->ForCustomizeAvatar->Blendshapecat == "FaceShape")
    {
      UE_LOG(LogTemp, Display, TEXT("FaceShape---Point Data-->>>>"));
        TArray<FFacePoint> points = ULocalDataFunctionLibrary::GetFaceShape();
        for (int i = 0; i < points.Num(); i++)
        {
               
            AvatarHandler->ForCustomizeAvatar->SpawnCustomizePoint(points[i]);
        }
    }
    if (AvatarHandler->ForCustomizeAvatar->Blendshapecat == "NoseShape")
    {
        TArray<FFacePoint> points = ULocalDataFunctionLibrary::GetNoseShape();
        for (int i = 0; i < points.Num(); i++)
        {
           AvatarHandler->ForCustomizeAvatar->SpawnCustomizePoint(points[i]);
        }
    }
    if (AvatarHandler->ForCustomizeAvatar->Blendshapecat == "EyebrowShape")
    {
        TArray<FFacePoint> points = ULocalDataFunctionLibrary::GetEyebrowShape();
        for (int i = 0; i < points.Num(); i++)
        {
           AvatarHandler->ForCustomizeAvatar->SpawnCustomizePoint(points[i]);
        }
    }
    if (AvatarHandler->ForCustomizeAvatar->Blendshapecat == "EyeShape")
    {
        TArray<FFacePoint> points = ULocalDataFunctionLibrary::GetEyeShape();
        for (int i = 0; i < points.Num(); i++)
        {
            AvatarHandler->ForCustomizeAvatar->SpawnCustomizePoint(points[i]);
        }
    }
    if (AvatarHandler->ForCustomizeAvatar->Blendshapecat == "LipShape")
    {
        TArray<FFacePoint> points = ULocalDataFunctionLibrary::GetLipShape();
        for (int i = 0; i < points.Num(); i++)
        {
            AvatarHandler->ForCustomizeAvatar->SpawnCustomizePoint(points[i]);
        }
    }
    if (AvatarHandler->ForCustomizeAvatar->Blendshapecat == "EarShape")
    {
        TArray<FFacePoint> points = ULocalDataFunctionLibrary::GetEarshape();
        for (int i = 0; i < points.Num(); i++)
        {
            AvatarHandler->ForCustomizeAvatar->SpawnCustomizePoint(points[i]);
        }
    }
    OnFrontHeadButtonClick();
}
void UCustomizeBlendshapePanel::OnclickBlendshapePoint(FString name)
{
    UE_LOG(LogTemp, Warning, TEXT("OnclickBlendshapePoint---->>: %s"), *name);
    for (int i = 0 ; i < AvatarHandler->ForCustomizeAvatar->SpawnedFacePoints.Num(); i ++)
	{
		// if(AvatarHandler->ForCustomizeAvatar->SpawnedFacePoints[i]->HorizontalShape.Contains(name) ||  AvatarHandler->ForCustomizeAvatar->SpawnedFacePoints[i]->VerticalShape.Contains(name))
		// {
		// 	if (AvatarHandler->ForCustomizeAvatar->SpawnedFacePoints[i]->pointDynamicMaterial)
		// 	{
		// 		UE_LOG(LogTemp, Warning, TEXT("Hit Actor Name COlor Change to WHITEE---->>: %s"), *name);
		// 		AvatarHandler->ForCustomizeAvatar->SpawnedFacePoints[i]->pointDynamicMaterial->SetVectorParameterValue(TEXT("BasicColor"), FLinearColor(1.0f, 0.0f, 0.0f, 1.0f)); // Set the color to White
		// 		AvatarHandler->ForCustomizeAvatar->SpawnedFacePoints[i]->PlaneMesh->SetMaterial(0, AvatarHandler->ForCustomizeAvatar->SpawnedFacePoints[i]->pointDynamicMaterial);
		//     }
		// }
		// else
		// {
		// 	// UMaterialInstanceDynamic* NewDynamicMaterial = UMaterialInstanceDynamic::Create(HandlerInstance->ForCustomizeAvatar->SpawnedFacePoints[i]->PlaneMesh->GetMaterial(0), this);

		// 	if (AvatarHandler->ForCustomizeAvatar->SpawnedFacePoints[i]->pointDynamicMaterial)
		// 	{
		// 		UE_LOG(LogTemp, Warning, TEXT("Hit Actor Name COlor Change to WHITEE---->>: %s"), *name);
		// 		AvatarHandler->ForCustomizeAvatar->SpawnedFacePoints[i]->pointDynamicMaterial->SetVectorParameterValue(TEXT("BasicColor"), FLinearColor(0.0f, 0.0f, 0.0f, 1.0f)); // Set the color to White
		// 		AvatarHandler->ForCustomizeAvatar->SpawnedFacePoints[i]->PlaneMesh->SetMaterial(0, AvatarHandler->ForCustomizeAvatar->SpawnedFacePoints[i]->pointDynamicMaterial);
		//     }
	    // }

        if(AvatarHandler->ForCustomizeAvatar->SpawnedFacePoints[i]->PointsName == name)
        {
            if (AvatarHandler->ForCustomizeAvatar->SpawnedFacePoints[i]->pointDynamicMaterial)
			{
				UE_LOG(LogTemp, Warning, TEXT("Hit Actor Name COlor Change to WHITEE---->>: %s"), *name);
				AvatarHandler->ForCustomizeAvatar->SpawnedFacePoints[i]->pointDynamicMaterial->SetVectorParameterValue(TEXT("BasicColor"), FLinearColor(1.0f, 0.0f, 0.0f, 1.0f)); // Set the color to White
				AvatarHandler->ForCustomizeAvatar->SpawnedFacePoints[i]->PlaneMesh->SetMaterial(0, AvatarHandler->ForCustomizeAvatar->SpawnedFacePoints[i]->pointDynamicMaterial);
		    }
        }
        else
        {
            if (AvatarHandler->ForCustomizeAvatar->SpawnedFacePoints[i]->pointDynamicMaterial)
			{
				UE_LOG(LogTemp, Warning, TEXT("Hit Actor Name COlor Change to WHITEE---->>: %s"), *name);
				AvatarHandler->ForCustomizeAvatar->SpawnedFacePoints[i]->pointDynamicMaterial->SetVectorParameterValue(TEXT("BasicColor"), FLinearColor(0.0f, 0.0f, 0.0f, 1.0f)); // Set the color to White
				AvatarHandler->ForCustomizeAvatar->SpawnedFacePoints[i]->PlaneMesh->SetMaterial(0, AvatarHandler->ForCustomizeAvatar->SpawnedFacePoints[i]->pointDynamicMaterial);
		    }
        }
	}
    VerticalKeyValue = "";
    HorizontalKeyValue = "";
    // FString pointsarray = name;
    TArray<FString> arrays = UKismetStringLibrary::ParseIntoArray(name, TEXT("+"), true);
    FString Verticalblendname = arrays[0];
 
    if(Verticalblendname.Contains("_10"))
    {
        UE_LOG(LogTemp,Display,TEXT("GOT THE _10"));
       Verticalblendname =  Verticalblendname.Replace(TEXT("_10"), TEXT(""));
    }
       VerticalKeyValue = Verticalblendname;

    UE_LOG(LogTemp, Display, TEXT("BLENDSHAPE VERTICAL NAME  ---->>>%s"),*Verticalblendname);
    if(arrays.Num() > 1)
    {
        FString Horizontalblendname = arrays[1];
        HorizontalKeyValue = Horizontalblendname;
        UE_LOG(LogTemp, Display, TEXT("BLENDSHAPE HORIZONTAL NAME ---->>>%s"),*Horizontalblendname);
    }
    VerticalSlider->SetVisibility(ESlateVisibility::Hidden);
       HorizontalSlider->SetVisibility(ESlateVisibility::Hidden);
    if(VerticalKeyValue != "")
    {
       VerticalSlider->SetVisibility(ESlateVisibility::Visible);
    }
    if(HorizontalKeyValue!= "")
    {
      HorizontalSlider->SetVisibility(ESlateVisibility::Visible);
    }
}
void UCustomizeBlendshapePanel::OnBackButtonClick() {
  AvatarHandler->stopRotate =false;
      for (int i = 0; i < changedShape.Num(); i++)
      {
        AvatarHandler->ForCustomizeAvatar->spawnedHeadActor->ClearBlendShapeWithname(changedShape[i].slideKey);
      }
      changedShape.Empty();
    this->SetVisibility(ESlateVisibility::Hidden);
    if (APIEvents != nullptr)
    {
        APIEvents->ShowPanel(EUIPanels::CUSTOMIZEHEAD,false);
        APIEvents->OnChangeCamera.Broadcast(CameraPanels::CustomizeAvatar_Head);
        AvatarHandler->ForCustomizeAvatar->DestroySpawnCustomizePoint();
    }
   
}
void UCustomizeBlendshapePanel::OnProcessButtonClick() 
{
    AvatarHandler->stopRotate =false;
    this->SetVisibility(ESlateVisibility::Hidden);
    if (APIEvents != nullptr)
    {
        APIEvents->ShowPanel(EUIPanels::CUSTOMIZEHEAD,false);
        APIEvents->OnChangeCamera.Broadcast(CameraPanels::CustomizeAvatar_Head);
        AvatarHandler->ForCustomizeAvatar->DestroySpawnCustomizePoint();
    }
  
}
void UCustomizeBlendshapePanel::OnFrontHeadButtonClick()
{
    AvatarHandler->ForCustomizeAvatar->ShowCustomizePoint("Front");
    APIEvents->OnChangeCamera.Broadcast(CameraPanels::CustomizeBlendShape_Front);
}

void UCustomizeBlendshapePanel::OnSideHeadButtonClick()
{
    APIEvents->OnChangeCamera.Broadcast(CameraPanels::CustomizeBlendShape_Side);
    AvatarHandler->ForCustomizeAvatar->ShowCustomizePoint("Side");
}

void UCustomizeBlendshapePanel::OnHorizontalValueChange(float value)
{
    AvatarHandler->ForCustomizeAvatar->ChangeBlendPointValue(HorizontalKeyValue,value);
    AddShape(value, HorizontalKeyValue);
}

void UCustomizeBlendshapePanel::OnVerticalValueChange(float value)
{
    AvatarHandler->ForCustomizeAvatar->ChangeBlendPointValue(VerticalKeyValue,value);
    AddShape(value, VerticalKeyValue);
}

void UCustomizeBlendshapePanel::AddShape(float value, FString key) {
  int index = -1;
  if(changedShape.Num() >0){
  for (int i = 0; i < changedShape.Num(); i++)
  {
    if (changedShape[i].slideKey == key) {
      index = i;
      break;
    }
  }
  if (index > -1) {
    changedShape[index].value = value;
    }
    else
      {
      FChangedShape shape = FChangedShape();
      shape.slideKey = key;
      shape.value = value;
        changedShape.Add(shape);
    }
  } else {
      FChangedShape shape = FChangedShape();
      shape.slideKey = key;
      shape.value = value;
        changedShape.Add(shape);
    }
}