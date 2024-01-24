//  LeaveMeAlone Game by Netologiya. All RightsReserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LMASprintComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnStaminaChanged, float);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LEAVEMEALONE_API ULMASprintComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULMASprintComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool IsSprinting() const { return Sprinting; }
	float GetStamina() const { return Stamina; }
	
	void Sprint();
	void StartSprint();
	void StopSprint();
	void RestoreStamina();

	FOnStaminaChanged OnStaminaChanged;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	float MaxStamina = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	float RestoreDelay = 5.0f;

private:
	float Stamina = 0.0f;
	bool Sprinting = false;
	bool StaminaRestored = true;
	


	

		
};
