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
TArray&lt;AActor*> Actors;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Second", Meta = (ClampMin = "1", ClampMax = "8"))
TMap&lt;int32, FString> ActorMap;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Second")
TSet&lt;int32> ActorSet;

UFUNCTION(BlueprintCallable, Category = "First")
bool Function(bool bInput) {
// Set the value of bIsEnabled to the input value
bIsEnabled = bInput;

// Return the new value of bIsEnabled
return bIsEnabled;
}

if (!bIsEnabled) {
// If bIsEnabled is false, return
return;
}