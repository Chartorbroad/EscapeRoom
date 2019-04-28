// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <GameFramework/PlayerController.h>
#include <PhysicsEngine/PhysicsHandleComponent.h>
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEROOM_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	APlayerController* PlayerController;
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotator;
	float Reach = 150.f;

	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputComponent = nullptr;

	// Find assumed attached Physics Handle
	void FindPhysicsHandleComponent();

	// Setup assumed attached input component
	void SetupInputComponent();

	// Ray-cast and grab what's in reach
	void GrabObject();
	// Release a grabbed object
	void ReleaseObject();

	// Return hit for first Physics body in LINE TRACE
	const FHitResult GetFirstPhysicsBodyInReach();

	// Returns current start of reach line
	const FVector GetPlayerReachLineStart();

	// Returns current end of reach line
	const FVector GetPlayerReachLineEnd();

};
