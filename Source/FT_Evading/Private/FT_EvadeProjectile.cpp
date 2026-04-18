// Fill out your copyright notice in the Description page of Project Settings.


#include "FT_EvadeProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PlatformingCharacter.h"
#include "Components/SphereComponent.h"

// Sets default values
AFT_EvadeProjectile::AFT_EvadeProjectile()
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(160.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AFT_EvadeProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 1000.f;
	ProjectileMovement->MaxSpeed = 1000.f;
	ProjectileMovement->ProjectileGravityScale = 0.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;

	// Die after 3 seconds by default
	InitialLifeSpan = 10.0f;

	// Set the static mesh component
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	ProjectileMesh->SetupAttachment(RootComponent);
}

void AFT_EvadeProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		// might need some fancy code here at some change
		UE_LOG(LogTemp, Warning, TEXT("Projectile hit actor: %s | Component: %s"),*OtherActor->GetName(),*OtherComp->GetName());

		// missed from video, but we should apply an impulse to the hit object if it simulates physics
		// Apply impulse to the hit object in the direction of the projectile
		if (APlatformingCharacter* Player = Cast<APlatformingCharacter>(OtherActor))
		{
			Player->InterruptDash();
			FVector Knockback = ProjectileMovement->Velocity.GetSafeNormal() * 2000;
			Player->LaunchCharacter(Knockback, true, true);
			// our duty is fulfilled 
			Destroy();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Projectile hit actor: %s | Component: %s | No physics simulation"),
				*OtherActor->GetName(), *OtherComp->GetName());
		}


	}
}
