//  LeaveMeAlone Game by Netologiya. All RightsReserved.

#include "Components/LMAHealthComponent.h"

// Sets default values for this component's properties
ULMAHealthComponent::ULMAHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void ULMAHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	AActor* OwnerComponent = GetOwner();

	if (IsValid(OwnerComponent))
	{
		OwnerComponent->OnTakeAnyDamage.AddDynamic(this, &ULMAHealthComponent::OnTakeAnyDamage);
	}	
}

bool ULMAHealthComponent::IsDead() const
{
	return FMath::IsNearlyZero(Health);
}

bool ULMAHealthComponent::IsHealthFull() const
{
	return FMath::IsNearlyEqual(Health, MaxHealth);
}

bool ULMAHealthComponent::AddHealth(float NewHealth)
{
	if (IsDead() || IsHealthFull()) return false;

	Health = FMath::Clamp(Health + NewHealth, 0.0f, MaxHealth);
	return true;

}


void ULMAHealthComponent::OnTakeAnyDamage(
	AActor* DamagedActor, float Damage, const UDamageType* DamageDype, AController* InstigatedBy, AActor* DamageCauser)
{
	
	if (IsDead())
		return;

	Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);

	if (IsDead())
	{
		OnDeath.Broadcast();
	}
}





