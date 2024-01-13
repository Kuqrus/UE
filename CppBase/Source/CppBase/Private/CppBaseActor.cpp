//  LeaveMeAlone Game by Netologiya. All Rights Reserved.


#include "CppBaseActor.h"

// Sets default values
ACppBaseActor::ACppBaseActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
}

void ACppBaseActor::SinMovement(double Seconds) {

	double NewZ = FMath::Sin(Frequency * Seconds) * Amplitude;
	InitialLocation[2] = NewZ;
	SetActorLocation(InitialLocation);
}

// Called when the game starts or when spawned
void ACppBaseActor::BeginPlay()
{
	Super::BeginPlay();
	InitialLocation = GetActorLocation();
}

// Called every frame
void ACppBaseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

