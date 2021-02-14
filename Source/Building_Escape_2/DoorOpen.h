// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "DoorOpen.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_2_API UDoorOpen : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorOpen();
	void OpenDoor(float DeltaTime);
	float TotalMassOfActors() const;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
FRotator InitialRotation;
FRotator CurrentRotation;

UPROPERTY(EditAnywhere)
float TargetRotation = 90.f;

UPROPERTY(EditAnywhere)
ATriggerVolume* PressurePlate = nullptr;

// Find Pressure Plate
void FindPressurePlate() const;

UPROPERTY(EditAnywhere)
float MassToOpen = 50.f;



};
