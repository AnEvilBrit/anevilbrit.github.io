// Fill out your copyright notice in the Description page of Project Settings.

#include "LightSwitch.h"

// Sets default values
ALightSwitch::ALightSwitch()
{
	// Set this actor to call Tick() every frame
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ALightSwitch::BeginPlay()
{
	Super::BeginPlay();

	//Switch statement
	switch (SwitchInput) {
		case 1:
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Case 1"));
			}
			Function(true);
			break;
		
		case 2:
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Case 2"));
			}
			break;
		
		default:
			break;
	}

	//If statement
	if (bIsEnabled == true) {
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("True"));
		}
	} else {
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("False"));
		}
	}
}

// Called every frame
void ALightSwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}