#include "Grab.h"
#include "Components/InputComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Math/Color.h"


#define OUT

// Sets default values for this component's properties
UGrab::UGrab()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UGrab::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Grabber attached!"));

	// Assign values to pointers
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	SetupInputComponent();
}

FVector UGrab::GetPlayerReach() const
{	
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation);

	// FVector LineTraceEnd = PlayerViewPointLocation + FVector(0.f, 0.f, 100.f);
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

	return LineTraceEnd;
}

FVector UGrab::GetPlayerViewPointLocation() const
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;


	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation);

	return PlayerViewPointLocation;
}

FHitResult UGrab::GetPhysicsActorInReach()
{
	
	FCollisionQueryParams TraceParams(TEXT(""),false,GetOwner());

	FHitResult Hit;

	GetWorld()->LineTraceSingleByObjectType
	(
		OUT Hit,
		GetPlayerViewPointLocation(),
		GetPlayerReach(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);
	
	return Hit;

}

void UGrab::SetupInputComponent()
{
	if(InputComponent)
	{
		InputComponent->BindAction(TEXT("Grab"), IE_Pressed, this, &UGrab::Grab);
		InputComponent->BindAction(TEXT("Grab"), IE_Released, this, &UGrab::Release);
	}
}

void UGrab::Grab()
{
	//Debug
	// UE_LOG(LogTemp, Warning, TEXT("Grabbed!"));

	if(!PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("CRITICAL: Physics handle component was not found on base actor!"));
		return;
	}

	PhysicsHandle->GrabComponentAtLocation
	(
		GetPhysicsActorInReach().GetComponent(),
		NAME_None,
		GetPlayerReach()
	);

}

void UGrab::Release()
{
	//Debug
	// UE_LOG(LogTemp, Warning, TEXT("Released!"));

	if(!PhysicsHandle)
	{
		return;
	}

	PhysicsHandle->ReleaseComponent();
}

// Called every frame
void UGrab::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(!PhysicsHandle)
	{
		return;
	}

	if(PhysicsHandle->GrabbedComponent)
	{
		//Move the object we've grabbed.
		PhysicsHandle->SetTargetLocation(GetPlayerReach());
	}

}