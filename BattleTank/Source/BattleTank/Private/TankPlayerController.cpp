// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledPawn();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Controller possessing: %s"), *(ControlledTank->GetName()));
	}

}


// tick
void ATankPlayerController::Tick(float DeltaTime)
{
	// super
	Super::Tick(DeltaTime);

	AimTowardsCrossHair();


}



ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast <ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrossHair()
{
	if (!GetControlledTank())
	{
		return;
	}

	FVector HitLocation; // Out Prameter
	
	
	if (GetSightRayHitLocation(HitLocation)) // Has "side-effect", is going to line trace
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *HitLocation.ToString());
		// TODO tell controlled tank to aim at this point
	}
	
	
}

//Get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	//Find Crosshair position in pixel coordinates
	int32 ViewPortSizeX, ViewPortSizeY;
	GetViewportSize(ViewPortSizeX, ViewPortSizeY);
	auto ScreenLocation = FVector2D(ViewPortSizeX*CrosshairXLocation, ViewPortSizeY*CrosshairYLocation);
	// "de-project" the screen position of the crosshair to the world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		//Line-trace along that look direction, and see what we hit( up to some max range)
		GetLookVectorHitLocation(LookDirection, HitLocation);
	}
	

	
	return true;
}
bool ATankPlayerController ::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation)const
{
	FHitResult hitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
		if(GetWorld()-> LineTraceSingleByChannel(hitResult,StartLocation,EndLocation,ECollisionChannel::ECC_Visibility))
		{
			HitLocation = hitResult.Location;
			return true;
		}
		HitLocation = FVector(0);
	return false; // Line trace didnt suceed
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	
	FVector CameraWorldLocation; // To Be Discarded
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
	
}




