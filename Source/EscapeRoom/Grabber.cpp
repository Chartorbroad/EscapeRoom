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
	FindPhysicsHandleComponent();
	SetupInputComponent();
	
}

// Look for attached Physics Handle
void UGrabber::FindPhysicsHandleComponent() {

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle) {
		UE_LOG(LogTemp, Error, TEXT("%s is missing a PhysicsHandle!"), *(GetOwner()->GetName()))
	}
}

// Look for attached InputComponent
void UGrabber::SetupInputComponent(){

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
	UE_LOG(LogTemp, Warning, TEXT("Trying to Grab!"));

	GetFirstPhysicsBodyInReach();

	/// LINE TRACE and reach any actors with physics body collision channel set

	/// If we hit something with a Ray-cast, then attach a Physics Handle
	// TODO attach physics handle
}

void UGrabber::ReleaseObject() {
	UE_LOG(LogTemp, Warning, TEXT("Trying to Release!"))

	// TODO release physics handle
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{

	/// Get the player view point
	PlayerController->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotator);

	/// Find linetrace end
	FVector LineTraceEnd = PlayerViewPointLocation + (PlayerViewPointRotator.Vector() * Reach);//FVector(0.f, 0.f, 100.f); // temporary end vector for drawing;

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

	return FHitResult();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// if the physics handle is attached
		// move the object that we're holding

}

