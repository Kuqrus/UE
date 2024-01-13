// Fill out your copyright notice in the Description page of Project Settings.


#include "CppBaseActor.h"

// Sets default values
ACppBaseActor::ACppBaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ACppBaseActor::ShowInformation()
{
	UE_LOG(LogTemp, Display, TEXT("Instance name: %s"), *Name);
	UE_LOG(LogTemp, Display, TEXT("Enemy number: %d"), EnemyNum);
	UE_LOG(LogTemp, Display, TEXT("Is alive: %i"), IsAlive);
}

// Called when the game starts or when spawned
void ACppBaseActor::BeginPlay()
{
	Super::BeginPlay();

	ShowInformation();
	
}

// Called every frame
void ACppBaseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

