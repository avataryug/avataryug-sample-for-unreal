// Fill out your copyright notice in the Description page of Project Settings.


#include "GltfActor.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/StaticMeshSocket.h"
#include "Animation/AnimSequence.h"

AGltfActor::AGltfActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AssetRoot = CreateDefaultSubobject<USceneComponent>(TEXT("AssetRoot"));
	RootComponent = AssetRoot;
	bAllowNodeAnimations = true;
	bStaticMeshesAsSkeletal = false;
	bAllowSkeletalAnimations = true;
	bAllowPoseAnimations = true;
}

// Called when the game starts or when spawned
void AGltfActor::BeginPlay()
{
	Super::BeginPlay();
}


// Called when the game starts or when spawned
void AGltfActor::LoadModel(FString maincatid) 
{
  	MainCategory = maincatid;
	if (!Asset)
	{
		return;
	}

	double LoadingStartTime = FPlatformTime::Seconds();

	TArray<FglTFRuntimeScene> Scenes = Asset->GetScenes();
    for (FglTFRuntimeScene &Scene : Scenes)
    {
        
		USceneComponent* SceneComponent = NewObject<USceneComponent>(this, *FString::Printf(TEXT("Scene %d"), Scene.Index));
		SceneComponent->SetupAttachment(RootComponent);
		SceneComponent->RegisterComponent();
		AddInstanceComponent(SceneComponent);
		
		for (int32 NodeIndex : Scene.RootNodesIndices)
		{
			FglTFRuntimeNode Node;
			if (!Asset->GetNode(NodeIndex, Node))
			{
				return;
			}
			ProcessNode(SceneComponent, NAME_None, Node);
		}
	}

	for (TPair<USceneComponent*, FName>& Pair : SocketMapping)
	{
		for (USkeletalMeshComponent* SkeletalMeshComponent : DiscoveredSkeletalMeshComponents)
		{
			if (SkeletalMeshComponent->DoesSocketExist(Pair.Value))
			{
				Pair.Key->AttachToComponent(SkeletalMeshComponent, FAttachmentTransformRules::KeepRelativeTransform, Pair.Value);
				Pair.Key->SetRelativeTransform(FTransform::Identity);
				CurveBasedAnimations.Remove(Pair.Key);
				break;
			}
		}
	}

    UE_LOG(LogGLTFRuntime, Log, TEXT("Asset loaded in %f seconds"),  FPlatformTime::Seconds() - LoadingStartTime);

}

void AGltfActor::ProcessNode(USceneComponent* NodeParentComponent, const FName SocketName, FglTFRuntimeNode& Node)
{
	// special case for bones/joints
	if (Asset->NodeIsBone(Node.Index))
	{
		for (int32 ChildIndex : Node.ChildrenIndices)
		{
			FglTFRuntimeNode Child;
			if (!Asset->GetNode(ChildIndex, Child))
			{
				return;
			}
			ProcessNode(NodeParentComponent, *Child.Name, Child);
		}
		return;
	}

	USceneComponent* NewComponent = nullptr;
	if (Node.CameraIndex != INDEX_NONE)
	{
		UCameraComponent* NewCameraComponent = NewObject<UCameraComponent>(this, GetSafeNodeName<UCameraComponent>(Node));
		NewCameraComponent->SetupAttachment(NodeParentComponent);
		NewCameraComponent->RegisterComponent();
		NewCameraComponent->SetRelativeTransform(Node.Transform);
		AddInstanceComponent(NewCameraComponent);
		Asset->LoadCamera(Node.CameraIndex, NewCameraComponent);
		NewComponent = NewCameraComponent;

	}
	else if (Node.MeshIndex < 0)
	{
		NewComponent = NewObject<USceneComponent>(this, GetSafeNodeName<USceneComponent>(Node));
		NewComponent->SetupAttachment(NodeParentComponent);
		NewComponent->RegisterComponent();
		NewComponent->SetRelativeTransform(Node.Transform);
		AddInstanceComponent(NewComponent);
	}
	else
	{
		if (Node.SkinIndex < 0 && !bStaticMeshesAsSkeletal)
		{
			UStaticMeshComponent* StaticMeshComponent = nullptr;
			TArray<FTransform> GPUInstancingTransforms;
			if (Asset->GetNodeGPUInstancingTransforms(Node.Index, GPUInstancingTransforms))
			{
				UInstancedStaticMeshComponent* InstancedStaticMeshComponent = NewObject<UInstancedStaticMeshComponent>(this, GetSafeNodeName<UInstancedStaticMeshComponent>(Node));
				for (const FTransform& GPUInstanceTransform : GPUInstancingTransforms)
				{
					InstancedStaticMeshComponent->AddInstance(GPUInstanceTransform);
				}
				StaticMeshComponent = InstancedStaticMeshComponent;
			}
			else
			{
				StaticMeshComponent = NewObject<UStaticMeshComponent>(this, GetSafeNodeName<UStaticMeshComponent>(Node));
			}
			StaticMeshComponent->SetupAttachment(NodeParentComponent);
			StaticMeshComponent->RegisterComponent();
			StaticMeshComponent->SetRelativeTransform(Node.Transform);
			AddInstanceComponent(StaticMeshComponent);
			if (StaticMeshConfig.Outer == nullptr)
			{
				StaticMeshConfig.Outer = StaticMeshComponent;
			}
                        UStaticMesh *StaticMesh = Asset->LoadStaticMesh(
                            Node.MeshIndex, StaticMeshConfig);
                        
			if (StaticMesh && !StaticMeshConfig.ExportOriginalPivotToSocket.IsEmpty())
			{
				UStaticMeshSocket* DeltaSocket = StaticMesh->FindSocket(FName(StaticMeshConfig.ExportOriginalPivotToSocket));
				if (DeltaSocket)
				{
					FTransform NewTransform = StaticMeshComponent->GetRelativeTransform();
					FVector DeltaLocation = -DeltaSocket->RelativeLocation * NewTransform.GetScale3D();
					DeltaLocation = NewTransform.GetRotation().RotateVector(DeltaLocation);
					NewTransform.AddToTranslation(DeltaLocation);
					StaticMeshComponent->SetRelativeTransform(NewTransform);
				}
                        }
            
			StaticMeshComponent->SetStaticMesh(StaticMesh);
			ReceiveOnStaticMeshComponentCreated(StaticMeshComponent, Node);
            NewComponent = StaticMeshComponent;
                     
                      
		}
		else
		{
			USkeletalMeshComponent* SkeletalMeshComponent = NewObject<USkeletalMeshComponent>(this, GetSafeNodeName<USkeletalMeshComponent>(Node));
			SkeletalMeshComponent->SetupAttachment(NodeParentComponent);
			
			SkeletalMeshComponent->RegisterComponent();
			SkeletalMeshComponent->SetRelativeTransform(Node.Transform);
			AddInstanceComponent(SkeletalMeshComponent);
			USkeletalMesh* SkeletalMesh = Asset->LoadSkeletalMesh(Node.MeshIndex, Node.SkinIndex, SkeletalMeshConfig);
			SkeletalMeshComponent->SetSkeletalMesh(SkeletalMesh);
			DiscoveredSkeletalMeshComponents.Add(SkeletalMeshComponent);
			ReceiveOnSkeletalMeshComponentCreated(SkeletalMeshComponent, Node);
			NewComponent = SkeletalMeshComponent;
		}
	}

	if (!NewComponent)
	{
		return;
	}
	else
	{
		NewComponent->ComponentTags.Add(*FString::Printf(TEXT("GLTFRuntime:NodeName:%s"), *Node.Name));
		NewComponent->ComponentTags.Add(*FString::Printf(TEXT("GLTFRuntime:NodeIndex:%d"), Node.Index));

		if (SocketName != NAME_None)
		{
			SocketMapping.Add(NewComponent, SocketName);
		}
	}


	TArray<int32> EmitterIndices;
	if (Asset->GetNodeExtensionIndices(Node.Index, "MSFT_audio_emitter", "emitters", EmitterIndices))
	{
		// check for audio emitters
		for (const int32 EmitterIndex : EmitterIndices)
		{
			FglTFRuntimeAudioEmitter AudioEmitter;
			if (Asset->LoadAudioEmitter(EmitterIndex, AudioEmitter))
			{
				UAudioComponent* AudioComponent = NewObject<UAudioComponent>(this, *AudioEmitter.Name);
				AudioComponent->SetupAttachment(NewComponent);
				AudioComponent->RegisterComponent();
				AudioComponent->SetRelativeTransform(Node.Transform);
				AddInstanceComponent(AudioComponent);
				Asset->LoadEmitterIntoAudioComponent(AudioEmitter, AudioComponent);
				AudioComponent->Play();
			}
		}
	}

	// check for animations
	if (!NewComponent->IsA<USkeletalMeshComponent>())
	{
		if (bAllowNodeAnimations)
		{
			TArray<UglTFRuntimeAnimationCurve*> ComponentAnimationCurves = Asset->LoadAllNodeAnimationCurves(Node.Index);
			TMap<FString, UglTFRuntimeAnimationCurve*> ComponentAnimationCurvesMap;
			for (UglTFRuntimeAnimationCurve* ComponentAnimationCurve : ComponentAnimationCurves)
			{
				if (!CurveBasedAnimations.Contains(NewComponent))
				{
					CurveBasedAnimations.Add(NewComponent, ComponentAnimationCurve);
					CurveBasedAnimationsTimeTracker.Add(NewComponent, 0);
				}
				DiscoveredCurveAnimationsNames.Add(ComponentAnimationCurve->glTFCurveAnimationName);
				ComponentAnimationCurvesMap.Add(ComponentAnimationCurve->glTFCurveAnimationName, ComponentAnimationCurve);
			}
			DiscoveredCurveAnimations.Add(NewComponent, ComponentAnimationCurvesMap);
		}
	}
	else
	{
		USkeletalMeshComponent* SkeletalMeshComponent = Cast<USkeletalMeshComponent>(NewComponent);
		if (bAllowSkeletalAnimations)
		{
		
			UAnimSequence* SkeletalAnimation = Asset->LoadNodeSkeletalAnimation(SkeletalMeshComponent->SkeletalMesh, Node.Index, SkeletalAnimationConfig);
			 if (!SkeletalAnimation && bAllowPoseAnimations)
			 {
			 	SkeletalAnimation = Asset->CreateAnimationFromPose(SkeletalMeshComponent->SkeletalMesh, SkeletalAnimationConfig, Node.SkinIndex);
			 }
			if (SkeletalAnimation)
			{
				SkeletalMeshComponent->AnimationData.AnimToPlay = SkeletalAnimation;
				SkeletalMeshComponent->AnimClass = AnimClass;
				SkeletalMeshComponent->AnimationData.bSavedLooping = true;
				SkeletalMeshComponent->AnimationData.bSavedPlaying = true;
				SkeletalMeshComponent->SetAnimationMode(EAnimationMode::AnimationBlueprint);
			}
		}
	}

	for (int32 ChildIndex : Node.ChildrenIndices)
	{
		FglTFRuntimeNode Child;
		if (!Asset->GetNode(ChildIndex, Child))
		{
			return;
		}
		ProcessNode(NewComponent, NAME_None, Child);
	}
}

void AGltfActor::SetCurveAnimationByName(const FString& CurveAnimationName)
{
	if (!DiscoveredCurveAnimationsNames.Contains(CurveAnimationName))
	{
		return;
	}

	for (TPair<USceneComponent*, UglTFRuntimeAnimationCurve*>& Pair : CurveBasedAnimations)
	{

		TMap<FString, UglTFRuntimeAnimationCurve*> WantedCurveAnimationsMap = DiscoveredCurveAnimations[Pair.Key];
		if (WantedCurveAnimationsMap.Contains(CurveAnimationName))
		{
			Pair.Value = WantedCurveAnimationsMap[CurveAnimationName];
			CurveBasedAnimationsTimeTracker[Pair.Key] = 0;
		}
		else
		{
			Pair.Value = nullptr;
		}

	}

}

// Called every frame
void AGltfActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (TPair<USceneComponent*, UglTFRuntimeAnimationCurve*>& Pair : CurveBasedAnimations)
	{
		// the curve could be null
		if (!Pair.Value)
		{
			continue;
		}
		float MinTime;
		float MaxTime;
		Pair.Value->GetTimeRange(MinTime, MaxTime);

		float CurrentTime = CurveBasedAnimationsTimeTracker[Pair.Key];
		if (CurrentTime > Pair.Value->glTFCurveAnimationDuration)
		{
			CurveBasedAnimationsTimeTracker[Pair.Key] = 0;
			CurrentTime = 0;
		}

		if (CurrentTime >= MinTime)
		{
			FTransform FrameTransform = Pair.Value->GetTransformValue(CurveBasedAnimationsTimeTracker[Pair.Key]);
			Pair.Key->SetRelativeTransform(FrameTransform);
		}
		CurveBasedAnimationsTimeTracker[Pair.Key] += DeltaTime;
	}
}

void AGltfActor::ReceiveOnStaticMeshComponentCreated_Implementation(UStaticMeshComponent *StaticMeshComponent, const FglTFRuntimeNode &Node) 
{
  nodeName = Node.Name;
  bothStatic.Add(StaticMeshComponent);
	UE_LOG(LogTemp, Display, TEXT("GLTF ACTOR--->>Receive On StaticMeshComponent Created_Implementation Meshh--->>   %s"), *Node.Name);
	bothStatic.Add(StaticMeshComponent);
  	if (Node.Name.Contains("hair"))
    {
		UE_LOG(LogTemp, Display, TEXT("GLTF ACTOR--->>Contains Hair  Meshh--->>  "));
    	bodyMesh = StaticMeshComponent->GetStaticMesh();
        getMaerial = StaticMeshComponent->GetMaterial(0);
        getMaerial->GetTextureParameterValue(FName(TEXT("baseColorTexture")),bodyTex,true);
    	if (DynamicMaterial == nullptr)
  		{
			UE_LOG(LogTemp, Display, TEXT("GLTF ACTOR--->>CDynamicMaterial--->>  "));
        	DynamicMaterial = UMaterialInstanceDynamic::Create(BodyMaterial, this);
            DynamicMaterial->SetVectorParameterValue(FName("BodyColor"),FLinearColor(1,1,1,1));
       		DynamicMaterial->SetTextureParameterValue(FName(TEXT("BodyTexture")),bodyTex);
        }
    }
}

void AGltfActor::ReceiveOnSkeletalMeshComponentCreated_Implementation(USkeletalMeshComponent* SkeletalMeshComponent, const FglTFRuntimeNode& Node)
{
	nodeName = Node.Name;
	UE_LOG(LogTemp, Display, TEXT("GLTF ACTOR--->>ReceiveOnSkeletalMeshComponentCreated_Implementation Meshh--->>   %s"), *Node.Name);
	bothSkeletal.Add(SkeletalMeshComponent);
	if(Node.Name == "body" )
	{
		SkeletalMeshComponentBody = SkeletalMeshComponent;
		
	}
	if( Node.Name == "AvatarMesh"  || nodeName == "body")
	{
		 UE_LOG(LogTemp,Warning,TEXT("SkeletalMeshComponentBody -Adding-->>%s"),*nodeName);
		SkeletalMeshComponentBody = SkeletalMeshComponent;
		
		TArray<FSkeletalMaterial> mats = SkeletalMeshComponent->SkeletalMesh->GetMaterials();
		for (int i = 0; i < mats.Num(); i++)
		{
			FString matname = mats[i].MaterialSlotName.ToString();
			if (matname.Contains("_body"))
			{
			 	bodyIndex = i;
			 	break;
			}
		}
	}
	if(Node.Name.Contains("hair"))
	{
		SkeletalMeshComponentBody = SkeletalMeshComponent;
	}

	if(Node.Name == "hair" || Node.Name.Contains("hair"))
	{
		SkeletalMeshComponentBody = SkeletalMeshComponent;
		TArray<FSkeletalMaterial> mats = SkeletalMeshComponent->SkeletalMesh->GetMaterials();
		for (int i = 0; i < mats.Num(); i++)
		{
			FString matname = mats[i].MaterialSlotName.ToString();
			if (matname.Contains("hair"))
			{
			 	bodyIndex = i;
			 	break;
			}
		}
	}

}

void AGltfActor::SetBodyMaterial(UMaterialInstanceDynamic *material,FString category)
{
	 UE_LOG(LogTemp,Warning,TEXT("Set Default MAterial --->>%s"),*category);

  	if (category == "body") 
	{
		 UE_LOG(LogTemp,Warning,TEXT("nodeName  MAterial --->>%s"),*nodeName)
		if(nodeName == "AvatarMesh" )
		{
			 UE_LOG(LogTemp,Warning,TEXT("nodeName   --->>%s"),*nodeName)
			if(SkeletalMeshComponentBody != nullptr)
			{
				SkeletalMeshComponentBody->SetMaterial(bodyIndex,material);
			}
		}
		else
		{
			UE_LOG(LogTemp,Warning,TEXT("nodeName elseeee   --->>%s"),*nodeName)
			if(SkeletalMeshComponentBody != nullptr)
			{
				if(!nodeName.Contains("hair") )
				{
					SkeletalMeshComponentBody->SetMaterial(0, material);
				}
				 UE_LOG(LogTemp,Warning,TEXT("nodeName SkeletalMeshComponentBody   --->>%s"),*nodeName)
			}
		}
	}

	if(category == "hair")
	{
		UE_LOG(LogTemp,Warning,TEXT("Set Node name Hair MAterial --->>%s"),*nodeName);
		if(nodeName.Contains("hair") )
		{
			if(SkeletalMeshComponentBody != nullptr)
			{
				UE_LOG(LogTemp,Warning,TEXT("SetHair  SkeletalMeshComponentBody --->>%s"),*nodeName);
				SkeletalMeshComponentBody->SetMaterial(bodyIndex,material);
			}
			if(bothStatic.Num() > 0)
			{
				UE_LOG(LogTemp,Warning,TEXT("SetHair  bothStatic --->>%s"),*nodeName);
				for (int i = 0; i < bothStatic.Num(); i++)
				{
					bothStatic[i]->SetMaterial(bodyIndex, material);
				}
				
			}
		}
		else
		{
			UE_LOG(LogTemp,Warning,TEXT("SetHair  else --->>%s"),*nodeName);
			if(SkeletalMeshComponentBody != nullptr)
			{
				UE_LOG(LogTemp,Warning,TEXT("SetHair  else -SkeletalMeshComponentBody-->>%s"),*nodeName);
			}
			if(bothStatic.Num() > 0)
			{
				UE_LOG(LogTemp,Warning,TEXT("SetHair  else -StaticMeshhhhComponenets-->>%s"),*nodeName);
			}
		}
	}
}