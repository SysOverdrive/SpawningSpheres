// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ASphereMarker.generated.h"

UCLASS()
class SPAWNINGSPHERES_API AASphereMarker : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AASphereMarker();
	//Keep the current alive 
	float currentTime;
	/**Return the Mesh for the Sphere*/
	FORCEINLINE class UStaticMeshComponent* GetMesh() const {	return MeshComponent;}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;
	//Sphere Location In The World
	FVector SphereLocation;
	//Sphere Size
	FVector SphereSize;
private :
	/**Statoc mesh to represent the Sphere*/
	UPROPERTY(VisibleAnywhere, Category = "Callibration Sphere",meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent *MeshComponent;

	
	
};
