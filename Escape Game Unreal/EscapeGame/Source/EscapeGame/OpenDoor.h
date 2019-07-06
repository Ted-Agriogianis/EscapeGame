// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "Gameframework/Actor.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEGAME_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();
    
	// Called when the game starts
	virtual void BeginPlay() override;
    
    void DoorOpen();
    void DoorClose();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    UPROPERTY(VisibleAnywhere)
    float OpenAngle = 90.f;
    
    UPROPERTY(EditAnywhere)
    ATriggerVolume* PressurePlate;
    
    UPROPERTY(EditAnywhere)
    float DoorCloseDelay = 1.f;
    
    float LastDoorOpenTime;
    
    AActor* ActorThatOpens;
};
