//  LeaveMeAlone Game by Netologiya. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CppBaseActor.generated.h"

UCLASS()
class CPPBASE_API ACppBaseActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACppBaseActor();

	UFUNCTION(BlueprintCallable)
	void SinMovement(double Seconds);

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	float Amplitude = 70.0;

	UPROPERTY(EditAnywhere)
	float Frequency = 4.0;

	UPROPERTY(VisibleAnywhere)
	FVector InitialLocation;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
