// Fill out your copyright notice in the Description page of Project Settings.

#include "MoveAround.h"


// Sets default values for this component's properties
UMoveAround::UMoveAround()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMoveAround::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMoveAround::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector NewLocation = GetOwner()->GetActorLocation();
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	NewLocation.Z += DeltaHeight * 20.0f;
	float DeltaDepth = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	NewLocation.X += DeltaHeight * 10.0f;
	float DeltaWidth = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	NewLocation.Y += DeltaHeight * 10.0f;
	RunningTime += DeltaTime;
	GetOwner()->SetActorLocation(NewLocation);
}

