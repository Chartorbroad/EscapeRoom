// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "Engine/Public/DrawDebugHelpers.h"
#include <GameFramework/PlayerController.h>

#define OUT //this does nothing at all but can be used for markup lower down - i.e. visual reminders!

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = GetWorld()->GetFirstPlayerController();

	UE_LOG(LogTemp, Warning, TEXT("Grabber is reporting for duty!"));
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Get the player view point
	PlayerController->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotator);
	/*UE_LOG(LogTemp, Warning, TEXT("PlayerController View Point = %s , %s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotator.ToString());*/

	// Draw a red trace in the world to visualise
	FVector LineTraceEnd = PlayerViewPointLocation + (PlayerViewPointRotator.Vector() * Reach);//FVector(0.f, 0.f, 100.f); // temporary end vector for drawing;
	DrawDebugLine(
		GetWorld(),
		PlayerViewPointLocation,
		LineTraceEnd,
		FColor(255, 0, 0),
		false,
		0.f,
		0,
		10.f
	);

	// Ray-cast out to reach distance

	// See what we hit


}

