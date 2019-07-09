// Fill out your copyright notice in the Description page of Project Settings.
#include "OpenDoor.h"
#include "EscapeGame.h"
#include "Gameframework/Actor.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"

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
    
    ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	// ...
	
}

void UOpenDoor::DoorOpen() {
    FRotator NewRotation = FRotator(0.f, 60.f, 0.f);
    AActor* Owner = GetOwner();
    Owner->SetActorRotation(NewRotation);
}
void UOpenDoor::DoorClose() {
    FRotator NewRotation = FRotator(0.f, 0.f, 0.f);
    AActor* Owner = GetOwner();
    Owner->SetActorRotation(NewRotation);
}
// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    if(PressurePlate->IsOverlappingActor(ActorThatOpens)){
        DoorOpen();
        LastDoorOpenTime = GetWorld()->GetTimeSeconds();
    }
    if(GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay){
        DoorClose();
    }
	// ...
}
