// Fill out your copyright notice in the Description page of Project Settings.


#include "AutoCannon.h"

// Sets default values
AAutoCannon::AAutoCannon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CannonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CannonMesh"));
	SetRootComponent(CannonMesh);
}

// Called when the game starts or when spawned
void AAutoCannon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAutoCannon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// add on time since last fram
	timePassed += DeltaTime;
	if(timePassed >= delay)
	{
		// pew pew and reset timer
		Shoot();
		timePassed = 0.0f;
	}
}

void AAutoCannon::Shoot()
{
	// spawn a projectile and set its damage
	FVector Location = GetActorLocation() + GetActorForwardVector() * 200.f;
	FRotator Rotation = GetActorRotation();
	FActorSpawnParameters SpawnParams;
	AFT_EvadeProjectile* Projectile = GetWorld()->SpawnActor<AFT_EvadeProjectile>(ProjectileToSpawn, Location, Rotation, SpawnParams);
	//UE_LOG(LogTemp, Warning, TEXT("Pew Pew!"));
}

