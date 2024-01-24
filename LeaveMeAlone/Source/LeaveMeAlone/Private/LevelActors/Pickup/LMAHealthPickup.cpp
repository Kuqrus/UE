//  LeaveMeAlone Game by Netologiya. All RightsReserved.


#include "LevelActors/Pickup/LMAHealthPickup.h"
#include "Components/SphereComponent.h"
#include "Components/LMAHealthComponent.h"
#include "Player/LMADefaultCharacter.h"


ALMAHealthPickup::ALMAHealthPickup()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SetRootComponent(SphereComponent);	

}

void ALMAHealthPickup::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALMAHealthPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALMAHealthPickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	const auto Character = Cast<ALMADefaultCharacter>(OtherActor);
	if (GivePickup(Character))
	{
		PickupWasTaken();
	}
}

bool ALMAHealthPickup::GivePickup(ALMADefaultCharacter* Character)
{
	const auto HealthComponent = Character->GetHealthComponent();
	
	if(!HealthComponent) return false;

	return HealthComponent->AddHealth(HealthFromPickup);
}

void ALMAHealthPickup::PickupWasTaken()
{
	SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	GetRootComponent()->SetVisibility(false, true);

	FTimerHandle RespawnTimerHandle;
	GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ALMAHealthPickup::RespawnPickup, RespawnTime);
}

void ALMAHealthPickup::RespawnPickup()
{
	SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	GetRootComponent()->SetVisibility(true, true);
}