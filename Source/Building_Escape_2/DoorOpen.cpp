// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorOpen.h"
#include "Math/UnrealMathUtility.h"


// Sets default values for this component's properties
UDoorOpen::UDoorOpen()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoorOpen::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("%s is attached!"), *GetOwner()->GetName());


	InitialRotation = GetOwner()->GetActorRotation();
	// UE_LOG(LogTemp, Warning, TEXT("%s is the initial rotation!"), *InitialRotation.ToString());
	CurrentRotation = InitialRotation;
	TargetRotation += InitialRotation.Yaw;

	FindPressurePlate();



}

void UDoorOpen::FindPressurePlate() const
{
	if(!PressurePlate)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s's pressure plate is not assigned! Assign to get rid of Null Pointer exception."), *GetOwner()->GetName());
	}
}

void UDoorOpen::OpenDoor(float DeltaTime)
{

	CurrentRotation.Yaw = FMath::FInterpTo(CurrentRotation.Yaw, TargetRotation, DeltaTime, 1.5f);
	GetOwner()->SetActorRotation(CurrentRotation);

}

// Door opens when detects weight over 70 KG
float UDoorOpen::TotalMassOfActors() const
{	
	float TotalMass = 0.f;

	return TotalMass;
}
// Implement Close Door
// Using World Time Get Seconds (After 3 seconds, automatically close the door)


// Called every frame
void UDoorOpen::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	OpenDoor(DeltaTime);
}

