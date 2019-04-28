// Copyright Jacob Kempster 2019

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEROOM_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenTheDoor();
	void CloseTheDoor();
	void SetDoorOpenStatus(bool);
	bool IsDoorOpen() const;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	//UPROPERTY affects the variable directly underneath it.  This particular case allows the variable to be visible in the UE4 Editor but not editable from the same field.
	UPROPERTY(VisibleAnywhere)
	float OpenAngle = -60.f;

	// This makes is visible AND editable in the UE4 editor even though it is a private variable
	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;
	
	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 1.f;

	float LastDoorOpenTime;
	bool doorOpenStatus = false;

	AActor* ActorThatOpens; // Remember pawn inherits from actor (could use APawn here too if we only want the player to be the trigger.  But AActor allows us to use chairs etc too)

	AActor* Owner;

};
