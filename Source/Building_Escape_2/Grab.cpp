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

	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

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

	/* DrawDebugLine
	(
		GetWorld(),
		PlayerViewPointLocation,
		LineTraceEnd,
		FColor(0, 255, 0),
		false,
		0.f,
		0,
		5.f
	); */
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

	/* if(Hit.GetActor() != nullptr)
	{
			UE_LOG(LogTemp, Warning, TEXT("%s was hit!"), *Hit.GetActor()->GetName());
			return Hit;
	} */
	
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
	UE_LOG(LogTemp, Warning, TEXT("Grabbed!"));
}

void UGrab::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Released!"));
}

// Called every frame
void UGrab::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	

}