// LeaveMeAlone Game by Netologiya. All Rights Reserved.

#include "Weapon/LMAWeaponComponent.h"
#include "Animations/LMAReloadFinishedAnimNotify.h"
#include "GameFramework/Character.h"
#include "Weapon/LMABaseWeapon.h"

ULMAWeaponComponent::ULMAWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void ULMAWeaponComponent::Fire()
{	
	if (IsFiring && IsRate)
	{
		if (Weapon && !AnimReloading)
		{
			Weapon->Fire();
			IsRate = false;
			GetWorld()->GetTimerManager().SetTimer(handle, this, &ULMAWeaponComponent::RateHandle, Weapon->GetFireRate(), true);
		}
	}	
}

void ULMAWeaponComponent::StartFire()
{
	IsFiring = true;
}

void ULMAWeaponComponent::StopFire()
{
	IsFiring = false;
	IsRate = true;
}

void ULMAWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapon();
	InitAnimNotify();
}

void ULMAWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void ULMAWeaponComponent::SpawnWeapon()
{
	Weapon = GetWorld()->SpawnActor<ALMABaseWeapon>(WeaponClass);
	if (Weapon)
	{
		const auto Character = Cast<ACharacter>(GetOwner());
		if (Character)
		{
			FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
			Weapon->AttachToComponent(Character->GetMesh(), AttachmentRules, "r_Weapon_Socket");
			Weapon->OnClipEmpty.AddUObject(this, &ULMAWeaponComponent::ReloadEmptyClip);
		}
	}
}

void ULMAWeaponComponent::InitAnimNotify()
{
	

	if (!ReloadMontage)
	{
		return;
	}
	const auto NotifiesEvents = ReloadMontage->Notifies;
	for (auto NotifyEvent : NotifiesEvents)
	{
		auto ReloadFinish = Cast<ULMAReloadFinishedAnimNotify>(NotifyEvent.Notify);
		if (ReloadFinish)
		{
			ReloadFinish->OnNotifyReloadFinished.AddUObject(this, &ULMAWeaponComponent::OnNotifyReloadFinished);
			break;
		}
	}
}

void ULMAWeaponComponent::OnNotifyReloadFinished(USkeletalMeshComponent* SkeletalMesh)
{
	const auto Character = Cast<ACharacter>(GetOwner());
	if (Character->GetMesh() == SkeletalMesh)
	{
		AnimReloading = false;
	}
}

bool ULMAWeaponComponent::CanReload() const
{
	return !AnimReloading && !Weapon->IsCurrentClipFull();
}

void ULMAWeaponComponent::RateHandle()
{
	IsRate = true;
}

void ULMAWeaponComponent::Reload()
{
	if (!CanReload())
		return;
	
	Weapon->ChangeClip();
	AnimReloading = true;
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	Character->PlayAnimMontage(ReloadMontage);
	
}

void ULMAWeaponComponent::ReloadEmptyClip()
{
	Weapon->ChangeClip();
	AnimReloading = true;
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	Character->PlayAnimMontage(ReloadMontage);
}

bool ULMAWeaponComponent::GetCurrentAmmoWeapon(FAmmoWeapon& AmmoWeapon) const
{
	if (IsValid(Weapon))
	{
		AmmoWeapon = Weapon->GetCurrentAmmoWeapon();
		return true;
	}
	return false;
}
