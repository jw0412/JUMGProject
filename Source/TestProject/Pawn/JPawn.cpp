#include "JPawn.h"
#include "Controller/JPlayerController.h"

AJPawn::AJPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	AIControllerClass = AJPlayerController::StaticClass();
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void AJPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void AJPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AJPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	
}