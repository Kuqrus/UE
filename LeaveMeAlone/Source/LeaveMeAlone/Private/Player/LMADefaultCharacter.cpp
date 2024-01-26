//  LeaveMeAlone Game by Netologiya. All RightsReserved.


#include "Player/LMADefaultCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

#include "Components/LMAHealthComponent.h"
#include "Components/LMASprintComponent.h"
#include "Weapon/LMAWeaponComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/Engine.h"

// Sets default values
 ALMADefaultCharacter::ALMADefaultCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->SetUsingAbsoluteRotation(true);
	SpringArmComponent->TargetArmLength = ArmLength;
	SpringArmComponent->SetRelativeRotation(FRotator(YRotation, 0.0f, 0.0f));
	SpringArmComponent->bDoCollisionTest = false;
	SpringArmComponent->bEnableCameraLag = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->SetFieldOfView(FOV);
	CameraComponent->bUsePawnControlRotation = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	HealthComponent = CreateDefaultSubobject<ULMAHealthComponent>("HealthComponent");
	SprintComponent = CreateDefaultSubobject<ULMASprintComponent>("SprintComponent");

	WeaponComponent = CreateDefaultSubobject<ULMAWeaponComponent>("Weapon");


 }


 float ALMADefaultCharacter::ChangeSpeed() const
 {
	if (SprintComponent->IsSprinting())
	{
		return 600.0f;
	}
	else
	{
		return 300.0f;
	}
 }

 bool ALMADefaultCharacter::IsSprinting() const
 {
	return SprintComponent->IsSprinting();
 }


 void ALMADefaultCharacter::BeginPlay()
 {
	Super::BeginPlay();

	if (CursorMaterial)
	{
		CurrentCursor = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), CursorMaterial, CursorSize, FVector(0));
	}

	HealthComponent->OnDeath.AddUObject(this, &ALMADefaultCharacter::OnDeath);

	OnHealthChanged(HealthComponent->GetHealth());
	HealthComponent->OnHealthChanged.AddUObject(this, &ALMADefaultCharacter::OnHealthChanged);

	OnStaminaChanged(SprintComponent->GetStamina());
	SprintComponent->OnStaminaChanged.AddUObject(this, &ALMADefaultCharacter::OnStaminaChanged);
}

// Called every frame
void ALMADefaultCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!HealthComponent->IsDead())
	{
		RotationPlayerOnCursor();
	}
	
	SprintComponent->Sprint();
	WeaponComponent->Fire();
}

// Called to bind functionality to input
 void ALMADefaultCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("ZoomIn", IE_Pressed, this, &ALMADefaultCharacter::ZoomIn);
	PlayerInputComponent->BindAction("ZoomOut", IE_Pressed, this, &ALMADefaultCharacter::ZoomOut);
	PlayerInputComponent->BindAction("ZoomReset", IE_Pressed, this, &ALMADefaultCharacter::ZoomReset);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ALMADefaultCharacter::StartSprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ALMADefaultCharacter::StopSprint);

	PlayerInputComponent->BindAxis("MoveForward", this, &ALMADefaultCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ALMADefaultCharacter::MoveRight);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &ULMAWeaponComponent::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &ULMAWeaponComponent::StopFire);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &ULMAWeaponComponent::Reload);

 }

void ALMADefaultCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void ALMADefaultCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

 

 void ALMADefaultCharacter::ZoomIn()
{
	SpringArmComponent->TargetArmLength -= ZoomSensitivity;
 }

 void ALMADefaultCharacter::ZoomOut()
{
	SpringArmComponent->TargetArmLength += ZoomSensitivity;
 }

 void ALMADefaultCharacter::ZoomReset()
{
	SpringArmComponent->TargetArmLength = ArmLength;
}



void ALMADefaultCharacter::StartSprint()
{
	SprintComponent->StartSprint();
}

void ALMADefaultCharacter::StopSprint()
{
	SprintComponent->StopSprint();
}

void ALMADefaultCharacter::OnStaminaChanged(float Stamina)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Stamina: %f"), Stamina));
}


void ALMADefaultCharacter::OnDeath()
{
	CurrentCursor->DestroyRenderState_Concurrent();
	PlayAnimMontage(DeathMontage);
	GetCharacterMovement()->DisableMovement();	
	SetLifeSpan(5.0f);
	if (IsValid(Controller))
	{
		Controller->ChangeState(NAME_Spectating);
	}
}

void ALMADefaultCharacter::RotationPlayerOnCursor() 
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (IsValid(PC))
	{
		FHitResult ResultHit;
		PC->GetHitResultUnderCursor(ECC_GameTraceChannel1, true, ResultHit);
		float FindRotatorResultYaw = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), ResultHit.Location).Yaw;
		SetActorRotation(FQuat(FRotator(0.0f, FindRotatorResultYaw, 0.0f)));
		if (IsValid(CurrentCursor))
		{
			CurrentCursor->SetWorldLocation(ResultHit.Location);
		}
	}
}

void ALMADefaultCharacter::OnHealthChanged(float Health)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Health: %f"), Health));
}
