// Copyright Jacob Kempster 2019


#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"
#include <string>

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	
	// Find the pawn by going down from the world, to the player, to their 'body'
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	Owner = GetOwner();

}

void UOpenDoor::OpenTheDoor()
{
	//Set the door rotation
	Owner->SetActorRotation(FRotator(0.f, OpenAngle, 0.f)); // FRotator(pitch, yaw, roll)
	SetDoorOpenStatus(true);
}

void UOpenDoor::CloseTheDoor()
{
	//Set the door rotation
	Owner->SetActorRotation(FRotator(0.f, 0.0f, 0.f)); // FRotator(pitch, yaw, roll)
	SetDoorOpenStatus(false);
}

bool UOpenDoor::IsDoorOpen() const {
	return doorOpenStatus;
}

void UOpenDoor::SetDoorOpenStatus(bool status) {
	doorOpenStatus = status;
	return;
}

float UOpenDoor::GetTotalMassOfActorsOnPlate() {
	
	float TotalMass = 0.f;

	// Find all the actors overlapping with the TriggerVolume (PressurePlate)
	
	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	for (const auto* Actor : OverlappingActors) {
		if (Actor) {
			FString name = Actor->GetName();
			TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		}
	}
	
	// Iterate throgh them and sum their masses
	
	return TotalMass;
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Inefficient method!
	// Poll the Trigger volume every frame
	if (GetTotalMassOfActorsOnPlate() > 10.f) { // TODO Stop hardcoding this
		
	    //Then we open the door.
		OpenTheDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
		
	}

	// Check if it's time to close the door
	if (IsDoorOpen()) {
		if ( (GetWorld()->GetTimeSeconds()-LastDoorOpenTime) >= DoorCloseDelay) {
			CloseTheDoor();
		}
	}


}

