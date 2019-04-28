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

}

void UOpenDoor::OpenTheDoor()
{

	OnOpenRequest.Broadcast();

}

void UOpenDoor::CloseTheDoor()
{

	OnCloseRequest.Broadcast();

}


float UOpenDoor::GetTotalMassOfActorsOnPlate() {
	
	float TotalMass = 0.f;

	// Find all the actors overlapping with the TriggerVolume (PressurePlate)
	
	TArray<AActor*> OverlappingActors;
	if (!PressurePlate) { return 0.f; }
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	for (const auto* Actor : OverlappingActors) {
		if (Actor) {
			FString name = Actor->GetName();
			TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		}
	}
	
	return TotalMass;
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Inefficient method!
	// Poll the Trigger volume every frame
	if (GetTotalMassOfActorsOnPlate() > TriggerMass) {
	    //Then we open the door.
		OpenTheDoor();
	}
	else {
		CloseTheDoor();
	}


}

