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

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	//UPROPERTY affects the variable directly underneath it.  This particular case allows the variable to be visible in the UE4 Editor but not editable from the same field.
	UPROPERTY(VisibleAnywhere)
	float OpenAngle = 90.f;

	// This makes is visible AND editable in the UE4 editor even though it is a private variable
	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;

		
};
