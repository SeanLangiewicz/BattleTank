// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // Must be last include

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public :

	void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;



private:

	ATank* GetControlledTank() const;
	

	//Start the tank moving the barrel so that a shot where the crosshair intercets the world.
	virtual void AimTowardsCrossHair();


	//Return an OUT parameter, true if hit landscape
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	

	UPROPERTY(EditAnywhere)
		float CrosshairXLocation = 05.f;

	UPROPERTY(EditAnywhere)
		float CrosshairYLocation = 0.3333f;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;


	
	
};
