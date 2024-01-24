//  LeaveMeAlone Game by Netologiya. All RightsReserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LMAHealthPickup.generated.h"

class USphereComponent;
class ALMADefaultCharacter;

UCLASS()
class ALMAHealthPickup : public AActor
{
	GENERATED_BODY()
	
public:	
	ALMAHealthPickup();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Pickup")
	USphereComponent* SphereComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup");
	float RespawnTime = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "5.0", ClampMax = "100.0"));
	float HealthFromPickup = 100.0f;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

private:

	bool GivePickup(ALMADefaultCharacter* Character);

	void PickupWasTaken();
	void RespawnPickup();
	

};
