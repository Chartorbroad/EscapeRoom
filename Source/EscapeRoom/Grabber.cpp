// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "Engine/Public/DrawDebugHelpers.h"
#include "GameFramework/Actor.h"
#include <GameFramework/PlayerController.h>
#include "Components/InputComponent.h"

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

	/// Look for attached Physics Handle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle) {
		UE_LOG(LogTemp, Error, TEXT("%s is missing a PhysicsHandle!"), *(GetOwner()->GetName()))
	}

	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (!InputComponent) {
		UE_LOG(LogTemp, Error, TEXT("%s is missing an InputComponent!"), *(GetOwner()->GetName()))
	}
	else {
		///Bind the input actions
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::GrabObject);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::ReleaseObject);
	}
	
}

void UGrabber::GrabObject() {
	UE_LOG(LogTemp, Warning, TEXT("Trying to Grab!"))
}

void UGrabber::ReleaseObject() {
	UE_LOG(LogTemp, Warning, TEXT("Trying to Release!"))
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	/// Get the player view point
	PlayerController->GetPlayerViewPoint(
		OUT PlayerViewPointLocation, 
		OUT PlayerViewPointRotator);
	/*UE_LOG(LogTemp, Warning, TEXT("PlayerController View Point = %s , %s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotator.ToString());*/

	/// Draw a red trace in the world to visualise
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

	/// Setup query parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	/// Ray-cast (Line-trace) out to reach distance
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	/// See if anything was hit
	AActor* ActorHit = Hit.GetActor();
	if (ActorHit) { // make sure it's not a null-pointer (i.e. no collison)
		UE_LOG(LogTemp, Warning, TEXT("The LineTrace hit the Actor:: %s"), *(ActorHit->GetName()))
	}
		


}

