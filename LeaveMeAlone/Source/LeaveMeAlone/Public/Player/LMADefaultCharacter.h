//  LeaveMeAlone Game by Netologiya. All RightsReserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LMADefaultCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class ULMAHealthComponent;
class UAnimMontage;
class ULMASprintComponent;
class ULMAWeaponComponent;


UCLASS()
class ALMADefaultCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ALMADefaultCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	ULMAHealthComponent* GetHealthComponent() const { return HealthComponent; }

	UFUNCTION(BlueprintCallable)
	float ChangeSpeed() const;

	UFUNCTION(BlueprintCallable)
	bool IsSprinting() const;


protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent;

	UPROPERTY()
	UDecalComponent* CurrentCursor = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cursor")
	UMaterialInterface* CursorMaterial = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cursor")
	FVector CursorSize = FVector(20.f, 40.0f, 40.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cursor")
	uint8 ZoomSensitivity = 30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cursor")
	int MinZoom = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cursor")
	int MaxZoom = 5600;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components|Health")
	ULMAHealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* DeathMontage;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components|Sprint")
	ULMASprintComponent* SprintComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	ULMAWeaponComponent* WeaponComponent;


	
private:
	float YRotation = -75.0f;
	float ArmLength = 1400.0f;
	float FOV = 55.0f;

	void MoveForward(float Value);
	void MoveRight(float Value);

	void ZoomIn();
	void ZoomOut();
	void ZoomReset();

	void StartSprint();
	void StopSprint();
	void OnStaminaChanged(float Stamina);

	void OnDeath();
	void RotationPlayerOnCursor();
	void OnHealthChanged(float Health);

};
