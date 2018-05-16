// Fill out your copyright notice in the Description page of Project Settings.

#include "ASpawnSphereController.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/BoxComponent.h"
#include "TimerManager.h"
#include "Engine/World.h"

struct FActorSpawnParameters;
// Sets default values
AASpawnSphereController::AASpawnSphereController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	//Create the Box Component to represent the spawn volume (plane with the field of view)
	WhereToSpawn = CreateDefaultSubobject<UBoxComponent>(TEXT("WhereToSpawn"));
	RootComponent = WhereToSpawn;
	//Set the spawn delay range
	SpawnDelayRangeLow = 1.0f;
	SpawnDelayRangeHigh = 4.5f;

}

// Called when the game starts or when spawned
void AASpawnSphereController::BeginPlay()
{
	Super::BeginPlay();
	

}

// Called every frame
void AASpawnSphereController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector AASpawnSphereController::GetMarkerLocationInTheBox()
{
	FVector SpawnOrigin = WhereToSpawn->Bounds.Origin;
	FVector SpawnExtent = WhereToSpawn->Bounds.BoxExtent;

	return UKismetMathLibrary::RandomPointInBoundingBox(SpawnOrigin, SpawnExtent);//TODO Make Specific locations
}

void AASpawnSphereController::SpawnSphere()
{
	if(WhatToSpawn!=nullptr)
	{	
		//Check of Valid World
		UWorld* const World = GetWorld();
		if(World)
		{
			//Set The Spawn Parameters
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;
			//Get Location To Spawn At
			FVector SpawnLocation = GetMarkerLocationInTheBox();
			FRotator SpawnRotation; //I know it might be useless
			SpawnRotation.Yaw = FMath::FRand() *360.f;
			SpawnRotation.Pitch = FMath::FRand() *360.f;
			SpawnRotation.Roll = FMath::FRand() *360.f;

			//Spawn The Sphere
			AASphereMarker* const SpawnedSphere =  World->SpawnActor<AASphereMarker>(WhatToSpawn, SpawnLocation, SpawnRotation, SpawnParams);

			SpawnDelay = FMath::FRandRange(SpawnDelayRangeLow, SpawnDelayRangeHigh);
			GetWorldTimerManager().SetTimer(SpawnTimer, this, &AASpawnSphereController::SpawnSphere, SpawnDelay, false);

		}
	}
}

