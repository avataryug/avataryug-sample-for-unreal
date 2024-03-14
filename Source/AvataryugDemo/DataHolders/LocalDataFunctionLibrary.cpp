// Fill out your copyright notice in the Description page of Project Settings.


#include "LocalDataFunctionLibrary.h"
#include "Serialization/JsonSerializer.h"
#include "JsonObjectConverter.h"
#include "Dom/JsonObject.h"

TArray<FBodywearPointDetail> ULocalDataFunctionLibrary::GetBodyLocalPointList()
{
    TArray<FBodywearPointDetail> bodypoints;

    FBodywearPointDetail point;
    point.PointName = "upperbody_back";
    point.BoneName = "Spine2" ;
    point.Position = FVector(0,0,0);
    point.Rotation = FRotator(0, 0, 0);
    
    bodypoints.Add(point);

    point.BoneName = "LeftShoulder";
    point.PointName = "upperboddy_shoulder_left";
    point.Rotation = FRotator(0,0,0);
    point.Position = FVector(0, 0, 0);

    bodypoints.Add(point);

    point.BoneName = "LeftArm";
    point.PointName = "upperbody_arm_left";
    point.Rotation = FRotator(0,0,0);
    point.Position = FVector(0,0,0);

    bodypoints.Add(point);
       
    point.BoneName = "LeftForeArm";
    point.PointName = "upperbody_forearm_left";
    point.Rotation = FRotator(0,0,0);
    point.Position = FVector(0, 0, 0);

    bodypoints.Add(point);
       
    point.BoneName = "LeftForeArm";
    point.PointName = "upperbody_wrist_left";
    point.Rotation = FRotator(0.0,266.0,180);
    // point.Position = FVector(0.0f,266,180);
    point.Position = FVector(0.000416f,-0.231798f,-0.000198f);

    				// rotation(3.6,1.5,10.59) x= 3.6 , y = 1.5 , z = 12.4
				// UE_LOG(LogTemp, Display, TEXT("CameraPanels::CustomizeAvatar_Head"));
				// RotYaw = 0;
				// Camera->SetFieldOfView(40.0f);
				// NextLocation = FVector(42, -69, 91);
				// NextRotation = FRotator(1.5f, 12.4f, 3.6f);
   
    // point.Position = FVector(0,0,0);
    // point.Rotation = FRotator(0, 0,0);

    // point.Position = FVector(0,0,20.64);
    // point.Rotation = FRotator(-90, 0,-90);

    bodypoints.Add(point);

    point.BoneName = "RightShoulder";
    point.PointName = "upperboddy_shoulder_right" ;
    point.Rotation = FRotator(0,0,0);
    point.Position = FVector(0, 0, 0);

    bodypoints.Add(point);

    point.BoneName = "RightArm";
    point.PointName = "upperbody_arm_right";
    point.Rotation = FRotator(0,0,0);
    point.Position = FVector(0, 0, 0);

    bodypoints.Add(point);

    point.BoneName = "RightForeArm";
    point.PointName = "upperbody_forearm_right";
    point.Rotation = FRotator(0,0,0);
    point.Position = FVector(0, 0, 0);

    bodypoints.Add(point);
    
    point.BoneName = "RightForeArm";
    point.PointName = "upperbody_wrist_right" ;
    point.Rotation = FRotator(0,0,0);
    point.Position = FVector(0, 0, 0);

    bodypoints.Add(point);
      
    point.BoneName = "LeftUpLeg",
    point.PointName = "lowerbody_thigh_left" ,
    point.Rotation = FRotator(0,0,0);
    point.Position = FVector(0, 0, 0);

    bodypoints.Add(point);
    
    point.BoneName = "LeftLeg",
    point.PointName = "lowerbody_knee_left",
    point.Rotation = FRotator(0,0,0);
    point.Position = FVector(0, 0, 0);

    bodypoints.Add(point);
  
    point.BoneName = "LeftLeg",
    point.PointName = "lowerbody_leg_left",
    point.Rotation = FRotator(0,0,0);
    point.Position = FVector(0, 0, 0);

    bodypoints.Add(point);
     
    point.BoneName = "RightUpLeg",
    point.PointName = "lowerbody_thigh_right",
    point.Rotation = FRotator(0,0,0);
    point.Position = FVector(0, 0, 0);

    bodypoints.Add(point);
    
    point.BoneName = "RightLeg",
    point.PointName = "lowerbody_knee_right",
    point.Rotation = FRotator(0,0,0);
    point.Position = FVector(0,0,0);

    bodypoints.Add(point);

    point.BoneName = "RightLeg",
    point.PointName = "lowerbody_leg_right",
    point.Rotation = FRotator(0,0,0);
    point.Position = FVector(0, 0, 0);

    bodypoints.Add(point);
    
    return bodypoints;
}

TArray<FModelDataResponce> ULocalDataFunctionLibrary::GetDefaultModelList(FString gender) {

    TArray<FModelDataResponce> modeldataList;

    FModelDataResponce modeldataResp;
    modeldataResp.code = 0;
    modeldataResp.status = "";

    FModelData modeldata;
    if (gender == "1") 
    {
      
    modeldata.MainCatID = "Top";
    modeldata.CoreBucket = "upperbody_sleeve_short";
    modeldata.GlbPath =  "https://aystorage.b-cdn.net/standard/female_standard_top.glb",
    modeldata.ConflictingBuckets = "{\"conflits\":[{\"name\":\"upperbody_shoulder_left\"},{\"name\":\"upperbody_sleeveless\"},{\"name\":\"upperbody_arm_right\"},{\"name\":\"upperbody_shoulder_both\"},{\"name\":\"upperbody_back\"},{\"name\":\"upperbody_sleeve_full\"},{\"name\":\"upperbody_arm_left\"},{\"name\":\"upperbody_wrist_both\"},{\"name\":\"upperbody_arm_both\"},{\"name\":\"upperbody_stomach\"},{\"name\":\"upperbody_hand_right\"},{\"name\":\"upperbody_shoulder_right\"},{\"name\":\"upperbody_wrist_right\"},{\"name\":\"upperbody_forearm_right\"},{\"name\":\"upperbody_forearm_both\"},{\"name\":\"upperbody_forearm_left\"},{\"name\":\"upperbody_wrist_left\"},{\"name\":\"upperbody_chest\"},{\"name\":\"upperbody_sleeve_short\"},{\"name\":\"upperbody_hand_left\"},{\"name\":\"upperbody_front\"},{\"name\":\"fullbody_without_foot\"},{\"name\":\"fullbody_with_head_foot\"},{\"name\":\"fullbody_without_head\"},{\"name\":\"fullbody_without_head_foot\"}]}";
    modeldataResp.data = modeldata;
    modeldataList.Add(modeldataResp);

    modeldata.MainCatID = "Bottom";
    modeldata.CoreBucket = "lowerbody_without_foot";
    modeldata.GlbPath = "https://aystorage.b-cdn.net/standard/female_standard_bottom.glb";
    modeldata.ConflictingBuckets = "{\"conflits\":[{\"name\":\"lowerbody_foot_right\"},{\"name\":\"lowerbody_knee_right\"},{\"name\":\"lowerbody_without_foot\"},{\"name\":\"lowerbody_leg_both\"},{\"name\":\"lowerbody_knee_left\"},{\"name\":\"lowerbody_foot_left\"},{\"name\":\"lowerbody_leg_left\"},{\"name\":\"lowerbody_knee_both\"},{\"name\":\"lowerbody_leg_right\"},{\"name\":\"lowerbody_till_knee\"},{\"name\":\"lowerbody_thigh_both\"},{\"name\":\"lowerbody_thigh_right\"},{\"name\":\"lowerbody_thigh_left\"},{\"name\":\"fullbody_without_foot\"},{\"name\":\"fullbody_with_head_foot\"},{\"name\":\"fullbody_without_head\"},{\"name\":\"fullbody_without_head_foot\"}]}";
    modeldataResp.data = modeldata;
    modeldataList.Add(modeldataResp);

    modeldata.MainCatID = "Footwear";
    modeldata.CoreBucket = "lowerbody_foot_both";
    modeldata.GlbPath =  "https://aystorage.b-cdn.net/standard/standard_footwear.glb";
     modeldata.ConflictingBuckets = "{\"conflits\":[{\"name\":\"lowerbody_foot_both\"}]}";
    modeldataResp.data = modeldata;
    modeldataList.Add(modeldataResp);

    modeldata.MainCatID = "Handwear";
    modeldata.CoreBucket = "upperbody_hand_both";
    modeldata.GlbPath =   "https://aystorage.b-cdn.net/standard/standard_hand.glb";
    modeldata.ConflictingBuckets = "{\"conflits\":[{\"name\":\"upperbody_hand_both\"}]}";
    modeldataResp.data = modeldata;
    modeldataList.Add(modeldataResp);

    } 
    else 
    {
      
    modeldata.MainCatID = "Top";
    modeldata.CoreBucket = "upperbody_sleeve_short";
    modeldata.GlbPath = "https://aystorage.b-cdn.net/standard/male_standard_top.glb";
    modeldataResp.data = modeldata;
    modeldataList.Add(modeldataResp);

    modeldata.MainCatID = "Bottom";
    modeldata.CoreBucket = "lowerbody_without_foot";
    modeldata.GlbPath = "https://aystorage.b-cdn.net/standard/male_standard_bottom.glb";
    modeldata.ConflictingBuckets = "{\"conflits\":[{\"name\":\"lowerbody_foot_right\"},{\"name\":\"lowerbody_knee_right\"},{\"name\":\"lowerbody_without_foot\"},{\"name\":\"lowerbody_leg_both\"},{\"name\":\"lowerbody_knee_left\"},{\"name\":\"lowerbody_foot_left\"},{\"name\":\"lowerbody_leg_left\"},{\"name\":\"lowerbody_knee_both\"},{\"name\":\"lowerbody_leg_right\"},{\"name\":\"lowerbody_till_knee\"},{\"name\":\"lowerbody_thigh_both\"},{\"name\":\"lowerbody_thigh_right\"},{\"name\":\"lowerbody_thigh_left\"},{\"name\":\"fullbody_without_foot\"},{\"name\":\"fullbody_with_head_foot\"},{\"name\":\"fullbody_without_head\"},{\"name\":\"fullbody_without_head_foot\"}]}";
    modeldataResp.data = modeldata;
    modeldataList.Add(modeldataResp);

    modeldata.MainCatID = "Footwear";
    modeldata.CoreBucket = "lowerbody_foot_both";
    modeldata.GlbPath = "https://aystorage.b-cdn.net/standard/standard_footwear.glb";
    modeldata.ConflictingBuckets = "{\"conflits\":[{\"name\":\"lowerbody_foot_both\"}]}";
    modeldataResp.data = modeldata;
    modeldataList.Add(modeldataResp);

    modeldata.MainCatID = "Handwear";
    modeldata.CoreBucket = "upperbody_hand_both";
    modeldata.GlbPath =  "https://aystorage.b-cdn.net/standard/standard_hand.glb";
    modeldata.ConflictingBuckets = "{\"conflits\":[{\"name\":\"upperbody_hand_both\"}]}";
    modeldataResp.data = modeldata;
    modeldataList.Add(modeldataResp);
    }
    
    
 
  
    return modeldataList;
 }

FModelDataResponce ULocalDataFunctionLibrary::  GetEmptyModelDataClass()
{
    FModelDataResponce modeldataResp;
    modeldataResp.code = 0;
    modeldataResp.status = "";

    FModelData modeldata;
    modeldata. MainCatID = "";
    modeldata. GlbPath = "";
    modeldata. CoreBucket= "";
    modeldata. ConflictingBuckets= "";
    modeldataResp.data = modeldata;
    return modeldataResp;
}

TArray<FFacePoint> ULocalDataFunctionLibrary::GetEarshape()
{
  TArray<FFacePoint> points;

   FFacePoint point;

    point = FFacePoint();
    point.VertexNumber = 2083;
    point.partType = "EarShape";
    point.HorizontalShape = "";
    point.VerticalShape = "Ears_Goblin";
    point.ViewDirection = "Front";
    points.Add(point);

    point = FFacePoint();
    point.VertexNumber = 1997;
    point.partType = "EarShape";
    point.HorizontalShape = "";
    point.VerticalShape = "Ears_Monk";
    point.ViewDirection = "Front";
    points.Add(point);

    point = FFacePoint();
    point.VertexNumber = 2083;
    point.partType = "EarShape";
    point.HorizontalShape = "";
    point.VerticalShape = "Ears_Goblin";
    point.ViewDirection = "Side";
    points.Add(point);

    point = FFacePoint();
    // point.VertexNumber = 1996;
    point.VertexNumber = 1997;
    point.partType = "EarShape";
    point.HorizontalShape = "";
    point.VerticalShape = "Ears_Monk";
    point.ViewDirection = "Side";
    points.Add(point);
    return points;
}

TArray<FFacePoint> ULocalDataFunctionLibrary::GetNoseShape()
{
    TArray<FFacePoint> points;
    FFacePoint point;

    point = FFacePoint();
    point.VertexNumber = 1034;
    point.partType = "NoseShape";
    point.HorizontalShape = "Nose_UpDown";
    point.VerticalShape = "Nose_Scale";
    point.ViewDirection = "Front";
    points.Add(point);

    point = FFacePoint();
    point.VertexNumber = 1094;
    point.partType = "NoseShape";
    point.HorizontalShape = "Nose_Tip_UpDown";
    point.VerticalShape = "Nose_Tip_Scale";
    point.ViewDirection = "Front";
    points.Add(point);

    point = FFacePoint();
    point.VertexNumber = 1136;
    point.partType = "NoseShape";
    point.HorizontalShape = "Nose_Wings_InOut";
    point.VerticalShape = "Nose_Wings_Scale";
    point.ViewDirection = "Front";
    points.Add(point);

    point = FFacePoint();
    point.VertexNumber = 1118;
    point.partType = "NoseShape";
    point.HorizontalShape = "";
    point.VerticalShape = "Nose_Bone_ThickThin";
    point.ViewDirection = "Front";
    points.Add(point);

    point = FFacePoint();
    point.ViewDirection = "Front";
    point.VertexNumber = 1071;
    point.partType = "NoseShape";
    point.HorizontalShape = "";
    point.VerticalShape = "Nose_Columella_UpDown";
    points.Add(point);

    point = FFacePoint();
    point.ViewDirection = "Front";
    point.VertexNumber = 1106;
    point.partType = "NoseShape";
    point.HorizontalShape = "";
    point.VerticalShape = "Nose_Sharp";
    points.Add(point);

    point = FFacePoint();
    point.ViewDirection = "Side";
    point.VertexNumber = 1117;
    point.partType = "NoseShape";
    point.HorizontalShape = "Nose_Bone_FrontBack";
    point.VerticalShape = "";
    points.Add(point);

    point = FFacePoint();
    point.ViewDirection = "Side";
    point.VertexNumber = 1027;
    point.partType = "NoseShape";
    point.VerticalShape = "Nose_Wings_Scale";
    point.HorizontalShape = "Nose_Wings_UpDown";
    points.Add(point);

    point = FFacePoint();
    point.ViewDirection = "Side";
    point.VertexNumber = 1035;
    point.partType = "NoseShape";
    point.VerticalShape = "Nose_UpDown";
    point.HorizontalShape = "Nose_FrontBack";
    points.Add(point);

    point = FFacePoint();
    point.ViewDirection = "Side";
    point.VertexNumber = 1091;
    point.partType = "NoseShape";
    point.VerticalShape = "Nose_Tip_UpDown";
    point.HorizontalShape = "Nose_Tip_FrontBack";
    points.Add(point);

    point = FFacePoint();
    point.ViewDirection = "Side";
    point.VertexNumber = 1006;
    point.partType = "NoseShape";
    point.VerticalShape = "";
    point.HorizontalShape = "Nose_Columella_UpDown";
    points.Add(point);

    return points;

}

TArray<FFacePoint> ULocalDataFunctionLibrary::GetEyebrowShape()
{
    TArray<FFacePoint> points;
  
    FFacePoint point;

    point = FFacePoint();
    point.ViewDirection = "Front";
    point.VertexNumber = 1291;
    point.partType = "EyebrowShape";
    point.VerticalShape = "Eyebrows_InOut";
    point.HorizontalShape = "Eyebrows_Inner_UpDown";
    points.Add(point);

    point = FFacePoint();
    point.ViewDirection = "Front";
    point.VertexNumber = 1289;
    point.partType = "EyebrowShape";
    point.VerticalShape = "Eyebrows_FrontBack";
    point.HorizontalShape = "Eyebrows_Middle_UpDown";
    points.Add(point);

    point = FFacePoint();
    point.ViewDirection = "Front";
    point.VertexNumber = 1311;
    point.partType = "EyebrowShape";
    point.VerticalShape = "";
    point.HorizontalShape = "Eyebrows_Outer_UpDown";
    points.Add(point);

    point = FFacePoint();
    point.ViewDirection = "Side";
    point.VertexNumber = 1289;
    point.partType = "EyebrowShape";
    point.VerticalShape = "Eyebrows_InOut";
    point.HorizontalShape = "Eyebrows_Inner_UpDown";
    points.Add(point);

    point = FFacePoint();
    point.ViewDirection = "Side";
    point.VertexNumber = 1309;
    point.partType = "EyebrowShape";
    point.VerticalShape = "Eyebrows_FrontBack";
    point.HorizontalShape = "Eyebrows_Middle_UpDown";
    points.Add(point);

    point = FFacePoint();
    point.ViewDirection = "Side";
    point.VertexNumber = 1311;
    // point.VertexNumber = 1313;
    point.partType = "EyebrowShape";
    point.VerticalShape = "";
    point.HorizontalShape = "Eyebrows_Outer_UpDown";
    points.Add(point);
    return points;
}

TArray<FFacePoint> ULocalDataFunctionLibrary::GetEyeShape()
{
    TArray<FFacePoint> points;
    FFacePoint point;

    point = FFacePoint();
    point.ViewDirection = "Front";
    point.VertexNumber = 1410;
    point.partType = "EyeShape";
    point.VerticalShape = "Eyeshape_UpDown";
    point.HorizontalShape = "Eyeshape_LowerLid_OpenClose";
    points.Add(point);

    point = FFacePoint();
    point.ViewDirection = "Front";
    point.VertexNumber = 1322;
    // point.VertexNumber = 1357;
    point.partType = "EyeShape";
    point.VerticalShape = "Eyeshape_Rotate";
    point.HorizontalShape = "Eyeshape_UpperLid_OpenClose";
    points.Add(point);

    point = FFacePoint();
    point.ViewDirection = "Front";
    point.VertexNumber = 1318;
    // point.VertexNumber = 1282;
    point.partType = "EyeShape";
    point.VerticalShape = "Eyeshape_Scale";
    point.HorizontalShape = "Eyeshape_UpperLid_Sharp";
    points.Add(point);

    point = FFacePoint();
    point.ViewDirection = "Front";
    point.VertexNumber = 1440;
    point.partType = "EyeShape";
    point.VerticalShape = "Eyeshape_Inner_LeftRight";
    point.HorizontalShape = "Eyeshape_Inner_UpDown";
    points.Add(point);

    point = FFacePoint();
    point.ViewDirection = "Front";
    point.VertexNumber = 1350;
    point.partType = "EyeShape";
    point.VerticalShape = "Eyeshape_Outer_LeftRight";
    point.HorizontalShape = "Eyeshape_Outer_UpDown";
    points.Add(point);

    point = FFacePoint();
    point.ViewDirection = "Front";
    point.VertexNumber = 1405;
    point.partType = "EyeShape";
    point.VerticalShape = "Pupil_Scale";
    point.HorizontalShape = "Iris_Scale";
    points.Add(point);

    point = FFacePoint();
    point.ViewDirection = "Front";
    point.VertexNumber = 1449;
    point.partType = "EyeShape";
    point.VerticalShape = "";
    point.HorizontalShape = "Eyeshape_InOut";
    points.Add(point);

    point = FFacePoint();
    point.ViewDirection = "Side";
    point.VertexNumber = 1318;
    point.partType = "EyeShape";
    point.VerticalShape = "";
    point.HorizontalShape = "Eyeshape_FrontBack";
    points.Add(point);

    return points;

}

TArray<FFacePoint> ULocalDataFunctionLibrary::GetLipShape()
{
    TArray<FFacePoint> points;
    FFacePoint point;

    point = FFacePoint();
    point.ViewDirection = "Front";
    point.VertexNumber = 770;
    point.partType = "LipShape";
    point.VerticalShape = "Lips_Scale";
    point.HorizontalShape = "Lips_Sharp";
    points.Add(point);

    point = FFacePoint();
    point.ViewDirection = "Front";
    point.VertexNumber = 750;
    point.partType = "LipShape";
    point.VerticalShape = "Lips_Smile";
    point.HorizontalShape = "Lips_Sad";
    points.Add(point);

    point = FFacePoint();
    point.ViewDirection = "Front";
    point.VertexNumber = 876;
    point.partType = "LipShape";
    point.VerticalShape = "Lips_LowerTip_UpDown";
    point.HorizontalShape = "Lips_Lower_Scale";
    points.Add(point);

    point = FFacePoint();
    point.ViewDirection = "Front";
    point.VertexNumber = 972;
    point.partType = "LipShape";
    point.VerticalShape = "Lips_UpperTip_UpDown";
    point.HorizontalShape = "Lips_Upper_Scale";
    points.Add(point);

    point = FFacePoint();
    point.ViewDirection = "Front";
    point.VertexNumber = 962;
    point.partType = "LipShape";
    point.VerticalShape = "Lips_Center_UpDown";
    point.HorizontalShape = "Lips_Center_Scale";
    points.Add(point);

    point = FFacePoint();
    point.ViewDirection = "Front";
    point.VertexNumber = 767;
    point.partType = "LipShape";
    point.VerticalShape = "Lips_Side_InOut";
    point.HorizontalShape = "Lips_UpDown";
    points.Add(point);


    point = FFacePoint();
    point.ViewDirection = "Side";
    point.VertexNumber = 751;
    // point.VertexNumber = 762;
    point.partType = "LipShape";
    point.VerticalShape = "Lips_Sad";
    point.HorizontalShape = "Lips_Side_InOut";
    points.Add(point);

    point = FFacePoint();
    point.ViewDirection = "Side";
    point.VertexNumber = 876;
    point.partType = "LipShape";
    point.VerticalShape = "Lips_FrontBack";
    point.HorizontalShape = "Lips_UpDown";
    points.Add(point);

    point = FFacePoint();
    point.ViewDirection = "Side";
    point.VertexNumber = 770;
    point.partType = "LipShape";
    point.VerticalShape = "Lips_Sharp";
    point.HorizontalShape = "Lips_Scale";
    points.Add(point);

    // point = FFacePoint();
    // point.ViewDirection = "Side";
    // point.VertexNumber = 0;
    // point.partType = "LipShape";
    // point.VerticalShape = "";
    // point.HorizontalShape = "Lips_Smile";
    // points.Add(point);

    return points;
}

TArray<FFacePoint> ULocalDataFunctionLibrary::GetFaceShape()
{
    TArray<FFacePoint> points;

    FFacePoint point;

    point = FFacePoint();
    point.ViewDirection = "Front";
    point.VertexNumber = 862;
    point.partType = "FaceShape";
    point.VerticalShape = "Face_Chin_UpDown";
    point.HorizontalShape = "Face_Chin_Scale";
    points.Add(point);

    point = FFacePoint();
    point.ViewDirection = "Front";
    // point.VertexNumber = 159;
    point.VertexNumber = 818;
    point.partType = "FaceShape";
    point.VerticalShape = "Face_Jaw_InOut";
    point.HorizontalShape = "Face_Jaw_Back_UpDown";
    points.Add(point);

    point = FFacePoint();
    point.ViewDirection = "Front";
    point.VertexNumber = 813;
    point.partType = "FaceShape";
    point.VerticalShape = "Face_Cheek_Puff";
    point.HorizontalShape = "Face_Jaw_Middle_UpDown";
    points.Add(point);

    point = FFacePoint();
    point.ViewDirection = "Front";
   // point.VertexNumber = 1460;
     point.VertexNumber = 822;
    point.partType = "FaceShape";
    point.VerticalShape = "";
    point.HorizontalShape = "Face_Cheekbone_Scale";
    points.Add(point);

    point = FFacePoint();
    point.ViewDirection = "Front";
    point.VertexNumber = 1810;
    point.partType = "FaceShape";
    point.VerticalShape = "";
    point.HorizontalShape = "Neck_Scale";
    points.Add(point);

    point = FFacePoint();
    point.ViewDirection = "Front";
    point.VertexNumber = 1452;
    point.partType = "FaceShape";
    point.VerticalShape = "";
    point.HorizontalShape = "Face_UpperCheek_Puff";
    points.Add(point);

    point = FFacePoint();
    point.ViewDirection = "Front";
    point.VertexNumber = 802;
    point.partType = "FaceShape";
    point.VerticalShape = "";
    point.HorizontalShape = "Face_Chin_Side_Scale";
    points.Add(point);

    point = FFacePoint();
    point.ViewDirection = "Side";
    point.VertexNumber = 862;
    point.partType = "FaceShape";
    point.VerticalShape = "Face_Chin_UpDown";
    point.HorizontalShape = "Face_Chin_FrontBack";
    points.Add(point);

    point = FFacePoint();
    point.ViewDirection = "Side";
    point.VertexNumber = 821;
    point.partType = "FaceShape";
    point.VerticalShape = "";
    point.HorizontalShape = "Face_Jaw_FrontBack";
    points.Add(point);

    point = FFacePoint();
    point.ViewDirection = "Side";
    point.VertexNumber = 1810;
    point.partType = "FaceShape";
    point.VerticalShape = "";
    point.HorizontalShape = "Neck_Scale";
    points.Add(point);

    return points;

}

TArray<FGetAllBucketVerticesResultDataInner> ULocalDataFunctionLibrary::GetVertices()
{
    TArray<FGetAllBucketVerticesResultDataInner> bucketPoints;

    FGetAllBucketVerticesResultDataInner bucketPoint;

    bucketPoint = FGetAllBucketVerticesResultDataInner();
    bucketPoint.BucketName = "ears_helix_mid_left";
    bucketPoint.MainCatID = "Ears";
    bucketPoint.Platform = "unreal";
    bucketPoint.VertexArray = "[2027]";
    bucketPoint.Meta = "";
    bucketPoint.ID = "00345ee9-5f50-4633-8dae-4ce6d7bdc3bf";
    bucketPoints.Add(bucketPoint);
 return bucketPoints;
}

TArray<FVertexBucketPoint> ULocalDataFunctionLibrary::GetBucketVertices()
{
  
    TArray<FVertexBucketPoint> bucketPoints;

    FVertexBucketPoint bucketPoint;



    bucketPoint = FVertexBucketPoint();
    bucketPoint.BucketName = "nose_wing_left";
    bucketPoint.MainCatID = "Nose";
    bucketPoint.VertexArray.Add(1027);
    bucketPoints.Add(bucketPoint);

    bucketPoint = FVertexBucketPoint();
    bucketPoint.BucketName = "mouth_lowerlip_right";
    bucketPoint.MainCatID = "Mouth";
    bucketPoint.VertexArray.Add(754);
    bucketPoints.Add(bucketPoint);

    bucketPoint = FVertexBucketPoint();
    bucketPoint.BucketName = "ears_helix_mid_right";
    bucketPoint.MainCatID = "Ears";
    bucketPoint.VertexArray.Add(2258);
    bucketPoints.Add(bucketPoint);

    bucketPoint = FVertexBucketPoint();
    bucketPoint.BucketName = "ears_canal_right";
    bucketPoint.MainCatID = "Ears";
    bucketPoint.VertexArray.Add(2240);
    bucketPoints.Add(bucketPoint);


    bucketPoint = FVertexBucketPoint();
    bucketPoint.BucketName = "neck_upper";
    bucketPoint.MainCatID = "Neck";
    bucketPoint.VertexArray.Add(1765);
    bucketPoints.Add(bucketPoint);



    bucketPoint = FVertexBucketPoint();
    bucketPoint.BucketName = "hair_center";
    bucketPoint.MainCatID = "Hair";
    bucketPoint.VertexArray.Add(1662);
    bucketPoints.Add(bucketPoint);


    bucketPoint = FVertexBucketPoint();
    bucketPoint.BucketName = "eyebrows_left";
    bucketPoint.MainCatID = "Eyebrows";
    bucketPoint.VertexArray.Add(1310);
    bucketPoints.Add(bucketPoint);


    bucketPoint = FVertexBucketPoint();
    bucketPoint.BucketName = "nose_wing_both";
    bucketPoint.MainCatID = "Nose";
    bucketPoint.VertexArray.Add(1027);
    bucketPoint.VertexArray.Add(1160);
    bucketPoints.Add(bucketPoint);


    bucketPoint = FVertexBucketPoint();
    bucketPoint.BucketName = "ears_lobule_left";
    bucketPoint.MainCatID = "Ears";
    bucketPoint.VertexArray.Add(2001);
    bucketPoints.Add(bucketPoint);


    bucketPoint = FVertexBucketPoint();
    bucketPoint.BucketName = "ears_above_left";
    bucketPoint.MainCatID = "Ears";
    bucketPoint.VertexArray.Add(2077);
    bucketPoints.Add(bucketPoint);

    
    bucketPoint = FVertexBucketPoint();
    bucketPoint.BucketName = "head_wear_face_closed";
    bucketPoint.MainCatID = "Head";
    bucketPoint.VertexArray.Add(1662);
    bucketPoints.Add(bucketPoint);


    bucketPoint = FVertexBucketPoint();
    bucketPoint.BucketName = "mouth_lowerlip_right";
    bucketPoint.MainCatID = "Mouth";
    bucketPoint.VertexArray.Add(930);
    bucketPoints.Add(bucketPoint);


    bucketPoint = FVertexBucketPoint();
    bucketPoint.BucketName = "eyes_glasses_both";
    bucketPoint.MainCatID = "Eyes";
    bucketPoint.VertexArray.Add(1130);
    bucketPoints.Add(bucketPoint);


    bucketPoint = FVertexBucketPoint();
    bucketPoint.BucketName = "face_jaw_left";
    bucketPoint.MainCatID = "Face";
    bucketPoint.VertexArray.Add(821);
    bucketPoints.Add(bucketPoint);


    bucketPoint = FVertexBucketPoint();
    bucketPoint.BucketName = "mouth_inside_left";
    bucketPoint.MainCatID = "Mouth";
    bucketPoint.VertexArray.Add(730);
    bucketPoints.Add(bucketPoint);


    bucketPoint = FVertexBucketPoint();
    bucketPoint.BucketName = "eyes_full_right";
    bucketPoint.MainCatID = "Eyes";
    bucketPoint.VertexArray.Add(1243);
    bucketPoints.Add(bucketPoint);


    bucketPoint = FVertexBucketPoint();
    bucketPoint.BucketName = "ears_lobule_both";
    bucketPoint.MainCatID = "Ears";
    bucketPoint.VertexArray.Add(1707);
    bucketPoint.VertexArray.Add(2001);
    bucketPoints.Add(bucketPoint);



    bucketPoint = FVertexBucketPoint();
    bucketPoint.BucketName = "face_lower_half";
    bucketPoint.MainCatID = "Face";
    bucketPoint.VertexArray.Add(1095);
    bucketPoints.Add(bucketPoint);


    bucketPoint = FVertexBucketPoint();
    bucketPoint.BucketName = "nose_full";
    bucketPoint.MainCatID = "Nose";
    bucketPoint.VertexArray.Add(1104);
    bucketPoints.Add(bucketPoint);



    bucketPoint = FVertexBucketPoint();
    bucketPoint.BucketName = "nose_wing_right";
    bucketPoint.MainCatID = "Nose";
    bucketPoint.VertexArray.Add(1160);
    bucketPoints.Add(bucketPoint);


    bucketPoint = FVertexBucketPoint();
    bucketPoint.BucketName = "ears_helix_mid_both";
    bucketPoint.MainCatID = "Ears";
    bucketPoint.VertexArray.Add(2027);
    bucketPoint.VertexArray.Add(2258);
    bucketPoints.Add(bucketPoint);


    bucketPoint = FVertexBucketPoint();
    bucketPoint.BucketName = "head_wear_face_open";
    bucketPoint.MainCatID = "Head";
    bucketPoint.VertexArray.Add(1662);
    bucketPoints.Add(bucketPoint);


    bucketPoint = FVertexBucketPoint();
    bucketPoint.BucketName = "ears_full_left";
    bucketPoint.MainCatID = "Ears";
    bucketPoint.VertexArray.Add(2047);
    bucketPoints.Add(bucketPoint);

  
    bucketPoint = FVertexBucketPoint();
    bucketPoint.BucketName = "ears_lobule_right";
    bucketPoint.MainCatID = "Ears";
    bucketPoint.VertexArray.Add(1707);
    bucketPoints.Add(bucketPoint);


    bucketPoint = FVertexBucketPoint();
    bucketPoint.BucketName = "ears_helix_top_both";
    bucketPoint.MainCatID = "Ears";
    bucketPoint.VertexArray.Add(2074);
    bucketPoint.VertexArray.Add(2215);
    bucketPoints.Add(bucketPoint);


    bucketPoint = FVertexBucketPoint();
    bucketPoint.BucketName = "ears_canal_left";
    bucketPoint.MainCatID = "Ears";
    bucketPoint.VertexArray.Add(2047);
    bucketPoints.Add(bucketPoint);


    bucketPoint = FVertexBucketPoint();
    bucketPoint.BucketName = "mouth_lowerlip_both";
    bucketPoint.MainCatID = "Mouth";
    bucketPoint.VertexArray.Add(754);
    bucketPoint.VertexArray.Add(930);
    bucketPoints.Add(bucketPoint);


    bucketPoint = FVertexBucketPoint();
    bucketPoint.BucketName = "face_temple_left";
    bucketPoint.MainCatID = "Face";
    bucketPoint.VertexArray.Add(1480);
    bucketPoints.Add(bucketPoint);


    bucketPoint = FVertexBucketPoint();
    bucketPoint.BucketName = "facialhair";
    bucketPoint.MainCatID = "Face";
    bucketPoint.VertexArray.Add(990);
    bucketPoints.Add(bucketPoint);

    bucketPoint = FVertexBucketPoint();
    bucketPoint.BucketName = "ears_helix_mid_left";
    bucketPoint.MainCatID = "Ears";
    bucketPoint.VertexArray.Add(2027);
    bucketPoints.Add(bucketPoint);

    bucketPoint = FVertexBucketPoint();
    bucketPoint.BucketName = "face_chick_left";
    bucketPoint.MainCatID = "Face";
    bucketPoint.VertexArray.Add(815);
    bucketPoints.Add(bucketPoint);

    bucketPoint = FVertexBucketPoint();
    bucketPoint.BucketName = "head_back";
    bucketPoint.MainCatID = "Head";
    bucketPoint.VertexArray.Add(2177);
    bucketPoints.Add(bucketPoint);

    bucketPoint = FVertexBucketPoint();
    bucketPoint.BucketName = "ears_above_right";
    bucketPoint.MainCatID = "Ears";
    bucketPoint.VertexArray.Add(2212);
    bucketPoints.Add(bucketPoint);

    bucketPoint = FVertexBucketPoint();
    bucketPoint.BucketName = "eyes_full_left";
    bucketPoint.MainCatID = "Eyes";
    bucketPoint.VertexArray.Add(1406);
    bucketPoints.Add(bucketPoint);

    bucketPoint = FVertexBucketPoint();
    bucketPoint.BucketName = "face_full";
    bucketPoint.MainCatID = "Face";
    bucketPoint.VertexArray.Add(1093);
    bucketPoints.Add(bucketPoint);


    bucketPoint = FVertexBucketPoint();
    bucketPoint.BucketName = "neck_lower";
    bucketPoint.MainCatID = "Neck";
    bucketPoint.VertexArray.Add(1786);
    bucketPoints.Add(bucketPoint);


    bucketPoint = FVertexBucketPoint();
    bucketPoint.BucketName = "face_jaw_right";
    bucketPoint.MainCatID = "Face";
    bucketPoint.VertexArray.Add(1620);
    bucketPoints.Add(bucketPoint);

    bucketPoint = FVertexBucketPoint();
    bucketPoint.BucketName = "hair";
    bucketPoint.MainCatID = "Hair";
    bucketPoint.VertexArray.Add(1662);
    bucketPoints.Add(bucketPoint);

    bucketPoint = FVertexBucketPoint();
    bucketPoint.BucketName = "head_upper_full";
    bucketPoint.MainCatID = "Head";
    bucketPoint.VertexArray.Add(1662);
    bucketPoints.Add(bucketPoint);


    bucketPoint = FVertexBucketPoint();
    bucketPoint.BucketName = "mouth_full";
    bucketPoint.MainCatID = "Mouth";
    bucketPoint.VertexArray.Add(966);
    bucketPoints.Add(bucketPoint);

    bucketPoint = FVertexBucketPoint();
    bucketPoint.BucketName = "nose_nostril_center";
    bucketPoint.MainCatID = "Nose";
    bucketPoint.VertexArray.Add(1069);
    bucketPoints.Add(bucketPoint);

    bucketPoint = FVertexBucketPoint();
    bucketPoint.BucketName = "mouth_inside_right";
    bucketPoint.MainCatID = "Mouth";
    bucketPoint.VertexArray.Add(949);
    bucketPoints.Add(bucketPoint);

    bucketPoint = FVertexBucketPoint();
    bucketPoint.BucketName = "head_upper_horizontal";
    bucketPoint.MainCatID = "Head";
    bucketPoint.VertexArray.Add(1301);
    bucketPoints.Add(bucketPoint);

    bucketPoint = FVertexBucketPoint();
    bucketPoint.BucketName = "head_upper_vertical";
    bucketPoint.MainCatID = "Head";
    bucketPoint.VertexArray.Add(1662);
    bucketPoints.Add(bucketPoint);

    bucketPoint = FVertexBucketPoint();
    bucketPoint.BucketName = "eyebrows_both";
    bucketPoint.MainCatID = "Eyebrows";
    bucketPoint.VertexArray.Add(1310);
    bucketPoint.VertexArray.Add(1508);
    bucketPoints.Add(bucketPoint);


    bucketPoint = FVertexBucketPoint();
    bucketPoint.BucketName = "ears_over";
    bucketPoint.MainCatID = "Ears";
    bucketPoint.VertexArray.Add(1662);
    bucketPoints.Add(bucketPoint);


    bucketPoint = FVertexBucketPoint();
    bucketPoint.BucketName = "ears_helix_top_right";
    bucketPoint.MainCatID = "Ears";
    bucketPoint.VertexArray.Add(2215);
    bucketPoints.Add(bucketPoint);


    bucketPoint = FVertexBucketPoint();
    bucketPoint.BucketName = "face_chin";
    bucketPoint.MainCatID = "Head";
    bucketPoint.VertexArray.Add(862);
    bucketPoints.Add(bucketPoint);


    bucketPoint = FVertexBucketPoint();
    bucketPoint.BucketName = "ears_helix_top_left";
    bucketPoint.MainCatID = "Ears";
    bucketPoint.VertexArray.Add(2074);
    bucketPoints.Add(bucketPoint);


    bucketPoint = FVertexBucketPoint();
    bucketPoint.BucketName = "eyes_goggles_both";
    bucketPoint.MainCatID = "Eyes";
    bucketPoint.VertexArray.Add(1130);
    bucketPoints.Add(bucketPoint);


    bucketPoint = FVertexBucketPoint();
    bucketPoint.BucketName = "eyes_full_both";
    bucketPoint.MainCatID = "Eyes";
    bucketPoint.VertexArray.Add(1406);
    bucketPoint.VertexArray.Add(1243);
    bucketPoints.Add(bucketPoint);


    bucketPoint = FVertexBucketPoint();
    bucketPoint.BucketName = "ears_full_right";
    bucketPoint.MainCatID = "Ears";
    bucketPoint.VertexArray.Add(1243);
    bucketPoints.Add(bucketPoint);


    bucketPoint = FVertexBucketPoint();
    bucketPoint.BucketName = "face_temple_right";
    bucketPoint.MainCatID = "Face";
    bucketPoint.VertexArray.Add(1505);
    bucketPoints.Add(bucketPoint);


    bucketPoint = FVertexBucketPoint();
    bucketPoint.BucketName = "eyebrows_right";
    bucketPoint.MainCatID = "Eyebrows";
    bucketPoint.VertexArray.Add(1508);
    bucketPoints.Add(bucketPoint);


    bucketPoint = FVertexBucketPoint();
    bucketPoint.BucketName = "face_chick_right";
    bucketPoint.MainCatID = "Face";
    bucketPoint.VertexArray.Add(1601);
    bucketPoints.Add(bucketPoint);


    bucketPoint = FVertexBucketPoint();
    bucketPoint.BucketName = "face_forehead";
    bucketPoint.MainCatID = "Face";
    bucketPoint.VertexArray.Add(1301);
    bucketPoints.Add(bucketPoint);



    bucketPoint = FVertexBucketPoint();
    bucketPoint.BucketName = "mouth_inside_center";
    bucketPoint.MainCatID = "Mouth";
    bucketPoint.VertexArray.Add(876);
    bucketPoints.Add(bucketPoint);


    bucketPoint = FVertexBucketPoint();
    bucketPoint.BucketName = "mouth_lowerlip_center";
    bucketPoint.MainCatID = "Mouth";
    bucketPoint.VertexArray.Add(962);
    bucketPoints.Add(bucketPoint);


    bucketPoint = FVertexBucketPoint();
    bucketPoint.BucketName = "ears_canal_both";
    bucketPoint.MainCatID = "Ears";
    bucketPoint.VertexArray.Add(2047);
    bucketPoint.VertexArray.Add(2240);
    bucketPoints.Add(bucketPoint);

  return bucketPoints;
}


