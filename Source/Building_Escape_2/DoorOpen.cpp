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
	TargetRotation.Yaw += InitialRotation.Yaw;



}

void UDoorOpen::OpenDoor(float DeltaTime)
{

	CurrentRotation.Yaw = FMath::FInterpTo(CurrentRotation.Yaw, TargetRotation.Yaw, DeltaTime, 10.f);
	GetOwner()->SetActorRotation(CurrentRotation);

}

// Called every frame
void UDoorOpen::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	OpenDoor(DeltaTime);
}

