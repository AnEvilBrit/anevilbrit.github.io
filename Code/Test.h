// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPP/CPPProjectile.h"
#include "GameFramework/Actor.h"
#include "LightSwitch.generated.h"

UCLASS()
class ALightSwitch : public AActor
{
	GENERATED_BODY()
	
public:
	
	// Sets default values for this actor's properties
	ALightSwitch();
	
	//Vector2D Variable
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "First|Second|Third")
		FVector2D Vector2;

	//Vector3 Variable
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "First|Second")
		FVector Vector3;

	//Vector4 Variable
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "First")
		FVector4 Vector4;

	//Boolean Variable
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "First")
		bool bIsEnabled = false;

	//Integer Variable
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "First", meta = (ClampMin="1", ClampMax="8"))
		int32 SwitchInput = 1;

	//Float Variable
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "First|Second|Third")
		float Float = 1.6f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "First")
		FColor Colour;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "First")
		AActor* Actor = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "First")
		ACPPProjectile* Projectile = nullptr;

	UPROPERTY(EditAnywhere,	BlueprintReadWrite, Category = "Second", Meta =(AllowedClasses = "LightSwitch, CPPProjectile"))
		TArray<AActor*> Actors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Second", Meta = (ClampMin = "1", ClampMax = "8"))
		TMap<int32, FString> ActorMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Second")
		TSet<int32> ActorSet;
	
	UFUNCTION(BlueprintCallable, Category = "First")
		bool Function(bool bInput) {
			// Set the value of bIsEnabled to the input value
			bIsEnabled = bInput;
	
			// Return the new value of bIsEnabled
			return bIsEnabled;
		}
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
