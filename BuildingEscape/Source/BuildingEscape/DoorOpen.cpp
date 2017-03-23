// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "DoorOpen.h"


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
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();

	// find the owner object as before
	Owner = GetOwner();
}

void UDoorOpen::OpenDoor()
{
	Owner->SetActorRotation(FRotator(0.0f, OpenAngle, 0.0f));
}

void UDoorOpen::CloseDoor()
{
	Owner->SetActorRotation(FRotator(0.0f, 90.0f, 0.0f));
}


// Called every frame
void UDoorOpen::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// Poll trigger volume everyframe
	if (PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		// if the actor that opens is in the volume
		OpenDoor();
		LastTimeOpened = GetWorld()->GetTimeSeconds();
	}
	else
	{
		if (TimeToOpenTheDoor < (GetWorld()->GetTimeSeconds() - LastTimeOpened))
		{
			CloseDoor();
		}
	}	
}

