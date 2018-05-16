// Fill out your copyright notice in the Description page of Project Settings.
//SHOULD BE A PLANE SOMEHOW

// FOR Calibration toggle and raycast toggle
//InputComponent->BindAxis("MoveForward", this, &ACollidingPawn::MoveForward);



#pragma once

#include "GameFramework/Actor.h"
#include "ASphereMarker.h"


#include "ASpawnSphereController.generated.h"

UCLASS()
class SPAWNINGSPHERES_API AASpawnSphereController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AASpawnSphereController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// The Sphere To Spawn
	 AASphereMarker *WhatToSpawn;

	FTimerHandle SpawnTimer;
	/** Minimum spawn delay */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
		float SpawnDelayRangeLow;

	/** Maximum spawn delay */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
		float SpawnDelayRangeHigh;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	/** Returns where to spawn Spheres */
	FORCEINLINE class UBoxComponent* GetWhereToSpawn() const { return WhereToSpawn; }
	/**Get a point for where to spawn*/
	UFUNCTION(BlueprintPure, Category="Spawning")
	FVector GetMarkerLocationInTheBox();

private:
	/**This Should be the plane where to spawn the spheres*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category ="Spawning" , meta =(AllowPrivateAccess= "true"))
	class UBoxComponent* WhereToSpawn; //Makers field of viewplane

	/** The current spawn delay */
	float SpawnDelay;

	void SpawnSphere();
};
