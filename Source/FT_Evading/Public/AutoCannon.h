// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FT_EvadeProjectile.h"
#include "Components/StaticMeshComponent.h"
#include "AutoCannon.generated.h"

UCLASS()
class FT_EVADING_API AAutoCannon : public AActor
{
	GENERATED_BODY()
private:
	// i will use a simiple timer based ont he tick delta time
	float timePassed = 0.0f;
public:	
	// Sets default values for this actor's properties
	AAutoCannon();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AutoCannon")
	TSubclassOf <class AFT_EvadeProjectile> ProjectileToSpawn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AutoCannon")
	float delay = 5.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AutoCannon")
	float rotation = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AutoCannon")
	UStaticMeshComponent* CannonMesh;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void Shoot();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
