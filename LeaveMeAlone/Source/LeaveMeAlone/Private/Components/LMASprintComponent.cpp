//  LeaveMeAlone Game by Netologiya. All RightsReserved.


#include "Components/LMASprintComponent.h"
#include "TimerManager.h"

// Sets default values for this component's properties
ULMASprintComponent::ULMASprintComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	Stamina = MaxStamina;
}

// Called every frame
void ULMASprintComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

// Called when the game starts
void ULMASprintComponent::BeginPlay()
{
	Super::BeginPlay();	
}



void ULMASprintComponent::Sprint()
{
	if (Stamina - 0.1 <= 0.0f)
	{
		Sprinting = false;
	}
	else if (Sprinting)
	{
		Stamina--;
		OnStaminaChanged.Broadcast(Stamina);
		StaminaRestored = false;
	}
	if (!Sprinting && Stamina != MaxStamina)
	{
		RestoreStamina();
	}
}

void ULMASprintComponent::StartSprint()
{
	if (Stamina - 0.1 <= 0.0f)
	{
		return;
	}
	Sprinting = true;		
}

void ULMASprintComponent::StopSprint()
{
	Sprinting = false;
}

void ULMASprintComponent::RestoreStamina()
{
	Stamina += 0.3;

	if (Stamina >= MaxStamina)
	{
		Stamina = MaxStamina;
		OnStaminaChanged.Broadcast(Stamina);
		return;
	}	
	
	OnStaminaChanged.Broadcast(Stamina);
}
