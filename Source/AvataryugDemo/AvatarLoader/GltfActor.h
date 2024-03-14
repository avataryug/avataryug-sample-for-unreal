// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "glTFRuntimeAsset.h"
#include "GltfActor.generated.h"

UCLASS()
class AVATARYUGDEMO_API AGltfActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGltfActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FString MainCategory;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    FString ID;
	void LoadModel(FString maincatid);
 	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
	bool isBoth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
	int LeftPoint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
	int RightPoint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
        TArray<USkeletalMeshComponent *> bothSkeletal;
        
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Avataryug")
    TArray<UStaticMeshComponent*> bothStatic;
        
        
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    class UMaterial* BodyMaterial;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Avataryug")
    UStaticMesh* bodyMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Avataryug")
    UTexture *bodyTex;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Avataryug")
    UMaterialInterface *getMaerial;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Avataryug")
    TArray<UStaticMesh*> StaticMeshList;
	virtual void ProcessNode(USceneComponent* NodeParentComponent, const FName SocketName, FglTFRuntimeNode& Node);

	TMap<USceneComponent*, float>  CurveBasedAnimationsTimeTracker;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Avataryug")
	TSet<FString> DiscoveredCurveAnimationsNames;

	TMap<USceneComponent*, TMap<FString, UglTFRuntimeAnimationCurve*>> DiscoveredCurveAnimations;

	template<typename T>
	FName GetSafeNodeName(const FglTFRuntimeNode& Node)
	{
		return MakeUniqueObjectName(this, T::StaticClass(), *Node.Name);
	}

	TMap<USceneComponent*, FName> SocketMapping;
	TArray<USkeletalMeshComponent*> DiscoveredSkeletalMeshComponents;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true), Category = "Avataryug")
	UglTFRuntimeAsset* Asset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true), Category = "Avataryug")
	FglTFRuntimeStaticMeshConfig StaticMeshConfig;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true), Category = "Avataryug")
	FglTFRuntimeSkeletalMeshConfig SkeletalMeshConfig;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true), Category = "Avataryug")
	FglTFRuntimeSkeletalAnimationConfig SkeletalAnimationConfig;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
	TMap<USceneComponent*, UglTFRuntimeAnimationCurve*> CurveBasedAnimations;

	UFUNCTION(BlueprintNativeEvent, Category = "Avataryug", meta = (DisplayName = "On StaticMeshComponent Created"))
	void ReceiveOnStaticMeshComponentCreated(UStaticMeshComponent* StaticMeshComponent, const FglTFRuntimeNode& Node);

	UFUNCTION(BlueprintNativeEvent, Category = "Avataryug", meta = (DisplayName = "On SkeletalMeshComponent Created"))
	void ReceiveOnSkeletalMeshComponentCreated(USkeletalMeshComponent* SkeletalMeshComponent, const FglTFRuntimeNode& Node);

	UFUNCTION(BlueprintCallable, Category = "Avataryug")
	void SetCurveAnimationByName(const FString& CurveAnimationName);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true), Category = "Avataryug")
	bool bAllowNodeAnimations;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true), Category = "Avataryug")
	bool bStaticMeshesAsSkeletal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true), Category = "Avataryug")
	bool bAllowSkeletalAnimations;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true), Category = "Avataryug")
        bool bAllowPoseAnimations;
        
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyCategory)
    UMaterialInstanceDynamic *DynamicMaterial;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	class TSubclassOf<UAnimInstance> AnimClass;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ready Player Me")
	class USkeleton* TargetSkeleton;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category="glTFRuntime")
        USceneComponent *AssetRoot;
public:
    UFUNCTION()
	void SetBodyMaterial(UMaterialInstanceDynamic *material, FString category);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Avataryug")
	USkeletalMeshComponent* SkeletalMeshComponentBody;
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Avataryug")
	FString nodeName;
UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Avataryug")
			int bodyIndex = 0;
};
