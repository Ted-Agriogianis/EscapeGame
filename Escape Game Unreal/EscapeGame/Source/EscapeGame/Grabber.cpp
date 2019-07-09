// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "DrawDebugHelpers.h"
#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
///Starts the game
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty!"));
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
    OUT PlayerViewPosition, OUT PlayerViewRotation);
    PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
    if(PhysicsHandle){
        
    }else{
        UE_LOG(LogTemp,Warning,TEXT("%s is missing a physics handle component."), *GetOwner()->GetName());
    }
    
    Input = GetOwner()->FindComponentByClass<UInputComponent>();
    if(Input){
        UE_LOG(LogTemp,Warning,TEXT("%s has an input component."), *GetOwner()->GetName());
        Input->BindAction("Grab",IE_Pressed, this, &UGrabber::Grab);
        Input->BindAction("Grab",IE_Released, this, &UGrabber::Release);
    }else{
        UE_LOG(LogTemp,Warning,TEXT("%s is missing an input component."), *GetOwner()->GetName());
    }
	// ...
	
}

void UGrabber::Grab(){
    UE_LOG(LogTemp,Warning,TEXT("Grabbing."));
    
    auto HitResult = GetFirstObjectInReach();
    auto ComponentToGrab = HitResult.GetComponent();
    auto ActorHit = HitResult.GetActor();
    if(ActorHit){
    PhysicsHandle->GrabComponentAtLocationWithRotation (ComponentToGrab, NAME_None, ComponentToGrab->GetOwner()->GetActorLocation(), ComponentToGrab->GetOwner()->GetActorRotation());
    }else{
        
    }
}
void UGrabber::Release(){
    UE_LOG(LogTemp,Warning,TEXT("Releasing."));
    PhysicsHandle->ReleaseComponent();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
                                                               OUT PlayerViewPosition, OUT PlayerViewRotation);
    GetFirstObjectInReach();
    FVector LineTraceEnd = PlayerViewPosition + PlayerViewRotation.Vector() * Reach;
    //GetFirstObjectInReach();
    if(PhysicsHandle->GrabbedComponent){
        PhysicsHandle->SetTargetLocation(LineTraceEnd);
    }
	// ...
}

const FHitResult UGrabber::GetFirstObjectInReach() {
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPosition, OUT PlayerViewRotation);
    FVector LineTraceEnd = PlayerViewPosition + PlayerViewRotation.Vector() * Reach;
    
    FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
    FHitResult Hit;
    GetWorld()->LineTraceSingleByObjectType(OUT Hit, PlayerViewPosition, LineTraceEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),TraceParameters);
    
    AActor* ActorHit = Hit.GetActor();
    if(ActorHit)
    {
        UE_LOG(LogTemp, Warning, TEXT("Line trace hit: %s"), *(ActorHit->GetName()));
    }
    return Hit;
}
