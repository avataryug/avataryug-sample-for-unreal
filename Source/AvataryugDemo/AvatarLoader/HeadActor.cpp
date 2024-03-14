// Fill out your copyright notice in the Description page of Project Settings.


#include "HeadActor.h"
#include "Components/SkeletalMeshComponent.h"
// Sets default values
AHeadActor::AHeadActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SkeletalHeadComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	const FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
	SkeletalHeadComponent->SetupAttachment(RootComponent);
}	

// Called when the game starts or when spawned
void AHeadActor::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<FFinalSkinVertex> SkinnedVertices;
    SkeletalHeadComponent->GetCPUSkinnedVertices(SkinnedVertices, 3);
  	Locations.Empty();
    Locations.AddUninitialized(SkinnedVertices.Num());
    for (int32 i = 0; i < SkinnedVertices.Num(); ++i) 
	{
		Locations[i] = SkinnedVertices[i].Position;
    }
	const FTransform ToWorld = SkeletalHeadComponent->GetComponentTransform();
	for (FVector& EachVertex : Locations) 
	{
		EachVertex = ToWorld.TransformPosition(EachVertex);
    }
	VertexPoints = ULocalDataFunctionLibrary::GetBucketVertices();
	LoadVertexPoints();
}

// Called every frame
void AHeadActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHeadActor::SetBodyMaterial(UMaterialInstanceDynamic *material)
{
	if(DynamicFaceMaterial != nullptr)
	{
		DynamicFaceMaterial = material;
	}
	if (SkeletalHeadComponent != nullptr)
	{
        SkeletalHeadComponent->SetMaterial(2, material);
	}
}

void AHeadActor::SetMouthMaterial(UMaterialInstanceDynamic *material)
{
	 DynamicMouthMaterial = material;
  	if (SkeletalHeadComponent != nullptr)
	{
	
	}
}
void AHeadActor::SetEyeMaterial(UMaterialInstanceDynamic *material)
{
	DynamicEyeMaterial = material;
	if (SkeletalHeadComponent != nullptr)
	{
		SkeletalHeadComponent->SetMaterial(1, material);
	}
}

void AHeadActor::OnGetAllBucketVerticesResult(FGetAllBucketVerticesResult result)
{
  	const FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
    FActorSpawnParameters spawnparams;
    spawnparams.Owner = this;
	if(Locations.Num() > 0)
	{
		if (vertexPointActor_BP)
		{
			for (int i = 0; i < result.Data.Num(); i++)
			{
				FString pointsarray = result.Data[i].VertexArray;
				pointsarray = pointsarray.Replace(TEXT("["), TEXT(""));
				pointsarray = pointsarray.Replace(TEXT("]"), TEXT(""));
				if (pointsarray.Contains(","))
				{
					TArray<FString> arrays = UKismetStringLibrary::ParseIntoArray(pointsarray, TEXT(","), true);
					float leftNumber = FCString::Atof(*arrays[0]);
					AGltfStaticActorPoint *leftPoint = GetWorld()->SpawnActor<AGltfStaticActorPoint>(vertexPointActor_BP, FVector(0, 0, 0), FRotator(0, 90, 0),spawnparams);
					leftPoint->VertexIndex = leftNumber;
					leftPoint->BucketName = "l_" + result.Data[i].BucketName;
					// FString LLabel = FString(TEXT("l_%s"), *result.Data[i].BucketName);
					// leftPoint->SetActorLabel("l_" + result.Data[i].BucketName);
					// leftPoint->Rename(TEXT("l_" + *result.Data[i].BucketName),nullptr,REN_Test);

					FString LNewName = leftPoint->BucketName;
					// leftPoint->Rename(*LNewName, nullptr, REN_Test);

					leftPoint->AttachToActor(this, AttachmentTransformRules);
					leftPoint->SetActorLocation(Locations[leftNumber]);
					vertexPointsAdded.Add(leftPoint);

					float rightNumber = FCString::Atof(*arrays[1]);
					AGltfStaticActorPoint *rightPoint = GetWorld()->SpawnActor<AGltfStaticActorPoint>(vertexPointActor_BP, FVector(0, 0, 0), FRotator(0, 90, 0),spawnparams);
					rightPoint->BucketName = "r_" + result.Data[i].BucketName;
					rightPoint->VertexIndex = rightNumber;
					// FString Label = FString::Printf(TEXT("r_%s"), *result.Data[i].BucketName);
					// rightPoint->SetActorLabel("r_" + result.Data[i].BucketName);
				// rightPoint->Rename(TEXT("r_" + *result.Data[i].BucketName),nullptr,REN_Test);

					// FString RNewName = rightPoint->BucketName;
					// rightPoint->Rename(*RNewName, nullptr, REN_Test);

		
					rightPoint->AttachToActor(this, AttachmentTransformRules);
					rightPoint->SetActorLocation(Locations[rightNumber]);
					vertexPointsAdded.Add(rightPoint);
				}
				else
				{
					float Number = FCString::Atof(*pointsarray);
					AGltfStaticActorPoint *point =  GetWorld()->SpawnActor<AGltfStaticActorPoint>(vertexPointActor_BP, FVector(0, 0, 0), FRotator(0, 90, 0), spawnparams);
					point->BucketName = result.Data[i].BucketName;
					point->VertexIndex = Number;
					// point->Rename(TEXT(*result.Data[i].BucketName),nullptr,REN_Test);
						// point->SetActorLabel(result.Data[i].BucketName);
					// point->SetActorLabel(result.Data[i].BucketName);

					FString NewName =  result.Data[i].BucketName;
					// point->Rename(*NewName, nullptr, REN_Test);
					
					point->AttachToActor(this, AttachmentTransformRules);
					point->SetActorLocation(Locations[Number]);
					vertexPointsAdded.Add(point);
				}
			}
		}
	}
}
void AHeadActor:: ChangeBlendshapeValue(FString blendshapename,float value)
{
  	FName morphTargetName = FName(blendshapename);
	UE_LOG(LogTemp, Display, TEXT("ChangeBlendshapeValue============== %s %f"), *blendshapename, value);
    if(SkeletalHeadComponent != nullptr)
	{
    	UMorphTarget *morphTargetHead = SkeletalHeadComponent->FindMorphTarget(morphTargetName);
  		if (morphTargetHead != nullptr)
    	{
        	SkeletalHeadComponent->SetMorphTarget(morphTargetName, value);
	TArray<FFinalSkinVertex> SkinnedVertices;
        SkeletalHeadComponent->GetCPUSkinnedVertices(SkinnedVertices, 3);
        Locations.Empty();
        Locations.AddUninitialized(SkinnedVertices.Num());
        for (int32 i = 0; i < SkinnedVertices.Num(); ++i) {
	 		Locations[i] = SkinnedVertices[i].Position;
        }
		const FTransform ToWorld = SkeletalHeadComponent->GetComponentTransform();
		for (FVector& EachVertex : Locations) {
			EachVertex = ToWorld.TransformPosition(EachVertex);
        }
			if(Locations.Num() > 0)
			{
				if (vertexPointsAdded.Num() > 0)
				{
					for (int i = 0; i < vertexPointsAdded.Num(); i++)
					{
						vertexPointsAdded[i]->SetActorLocation(Locations[ vertexPointsAdded[i]->VertexIndex]);
					}
				}
			}
			
		
		}
	}

}

void AHeadActor:: ClearBlendShapeWithname(FString blendshapename)
{
    TMap<FName, int32> morphtargets = SkeletalHeadComponent->SkeletalMesh->GetMorphTargetIndexMap();
    for (TPair<FName, int32> Entry : morphtargets)
    {
  		FString Key = Entry.Key.ToString();
    	int32 Value = Entry.Value;
        if (Key.Contains(blendshapename)) {
             UMorphTarget *morphTargetHead = SkeletalHeadComponent->FindMorphTarget(Entry.Key);
          if (morphTargetHead != nullptr)
    		{
        		SkeletalHeadComponent->SetMorphTarget(Entry.Key, 0);
        			TArray<FFinalSkinVertex> SkinnedVertices;
        SkeletalHeadComponent->GetCPUSkinnedVertices(SkinnedVertices, 3);
        Locations.Empty();
        Locations.AddUninitialized(SkinnedVertices.Num());
        for (int32 i = 0; i < SkinnedVertices.Num(); ++i) {
	 		Locations[i] = SkinnedVertices[i].Position;
        }
		const FTransform ToWorld = SkeletalHeadComponent->GetComponentTransform();
		for (FVector& EachVertex : Locations) {
			EachVertex = ToWorld.TransformPosition(EachVertex);
        }
        		if (vertexPointsAdded.Num() > 0)
        		{
          			for (int i = 0; i < vertexPointsAdded.Num(); i++)
            		{
					vertexPointsAdded[i]->SetActorLocation(Locations[ vertexPointsAdded[i]->VertexIndex]);
					}
				}
			}
		  }
	}
}

void AHeadActor:: ClearAllBlendShape()
{
    TMap<FName, int32> morphtargets = SkeletalHeadComponent->SkeletalMesh->GetMorphTargetIndexMap();
    for (TPair<FName, int32> Entry : morphtargets)
    {
        UMorphTarget *morphTargetHead = SkeletalHeadComponent->FindMorphTarget(Entry.Key);
        if (morphTargetHead != nullptr)
    	{
        	SkeletalHeadComponent->SetMorphTarget(Entry.Key, 0);
        		TArray<FFinalSkinVertex> SkinnedVertices;
        SkeletalHeadComponent->GetCPUSkinnedVertices(SkinnedVertices, 3);
        Locations.Empty();
        Locations.AddUninitialized(SkinnedVertices.Num());
        for (int32 i = 0; i < SkinnedVertices.Num(); ++i) {
	 		Locations[i] = SkinnedVertices[i].Position;
        }
		const FTransform ToWorld = SkeletalHeadComponent->GetComponentTransform();
		for (FVector& EachVertex : Locations) {
			EachVertex = ToWorld.TransformPosition(EachVertex);
        }
        		if (vertexPointsAdded.Num() > 0)
        		{
          			for (int i = 0; i < vertexPointsAdded.Num(); i++)
            		{
					vertexPointsAdded[i]->SetActorLocation(Locations[ vertexPointsAdded[i]->VertexIndex]);
					}
				}
		}
	}

}
void AHeadActor:: OnGetAllBucketVerticesError(FApiException result){}

void AHeadActor::SetBodyPartColor(FLinearColor OutColor,FString category)
{

}

void AHeadActor::LoadVertexPoints()
{
	const FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
    FActorSpawnParameters spawnparams;
    spawnparams.Owner = this;
	if(Locations.Num() > 0)
	{
		if (vertexPointActor_BP)
		{
			for (int i = 0; i < VertexPoints.Num(); i++)
			{
				TArray<int32> pointsarray = VertexPoints[i].VertexArray;
				if(pointsarray.Num() > 1)
				{
					UE_LOG(LogTemp, Display, TEXT("pointsarray---->>%d"),pointsarray.Num());
					int leftNumber = pointsarray[0];
					AGltfStaticActorPoint *leftPoint = GetWorld()->SpawnActor<AGltfStaticActorPoint>(vertexPointActor_BP, FVector(0, 0, 0), FRotator(0, 0, 0),spawnparams);
					leftPoint->VertexIndex = leftNumber;
					leftPoint->BucketName = "left_" + VertexPoints[i].BucketName;
					// leftPoint->SetActorLabel("left_" + VertexPoints[i].BucketName);
					leftPoint->AttachToActor(this, AttachmentTransformRules);
					leftPoint->SetActorLocation(Locations[leftNumber]);
					vertexPointsAdded.Add(leftPoint);

					int rightNumber =pointsarray[1];
					AGltfStaticActorPoint *rightPoint = GetWorld()->SpawnActor<AGltfStaticActorPoint>(vertexPointActor_BP, FVector(0, 0, 0), FRotator(0, 0, 0),spawnparams);
					rightPoint->BucketName = "right_" + VertexPoints[i].BucketName;
					// rightPoint->SetActorLabel("right_" + VertexPoints[i].BucketName);
					rightPoint->VertexIndex = rightNumber;
					rightPoint->AttachToActor(this, AttachmentTransformRules);
					rightPoint->SetActorLocation(Locations[rightNumber]);
					vertexPointsAdded.Add(rightPoint);
				}
				else
				{
					float Number = pointsarray[0];
					AGltfStaticActorPoint *point =  GetWorld()->SpawnActor<AGltfStaticActorPoint>(vertexPointActor_BP, FVector(0, 0, 0), FRotator(0, 0, 0), spawnparams);
					point->BucketName = VertexPoints[i].BucketName;
					point->VertexIndex = Number;
					point->AttachToActor(this, AttachmentTransformRules);
					point->SetActorLocation(Locations[Number]);
					// point->SetActorLabel( VertexPoints[i].BucketName);
					vertexPointsAdded.Add(point);
				}
			}			
		}
	}
}

void AHeadActor::IncrementValue()
{
	vertexPointValue++;
	UE_LOG(LogTemp, Display,TEXT("Increment Value---->>%d"),vertexPointValue);
}

void AHeadActor::DecrementValue()
{
	vertexPointValue--;
	UE_LOG(LogTemp, Display,TEXT("Decrement Value---->>%d"),vertexPointValue);
}
