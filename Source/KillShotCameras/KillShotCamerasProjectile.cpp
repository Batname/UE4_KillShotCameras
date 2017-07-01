// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "KillShotCamerasProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SphereComponent.h"

AKillShotCamerasProjectile::AKillShotCamerasProjectile()
{

	// Tell Engine to call tick function every frame
	PrimaryActorTick.bCanEverTick = true;

	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AKillShotCamerasProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	/** KillShotCode begin */
	ProjectileMovement->MaxSpeed = 0.f; // inittial 3000.0f
	ProjectileMovement->bShouldBounce = false; // initial true
	InitialLifeSpan = 0.f; // Initial 3.0f. We want this projectile to exist until it hits something
	/** KillShotCode end */
	ProjectileMovement->bRotationFollowsVelocity = true;

	/** KillShotCode begin */
	ProjectileSpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("ProjectileSpringArmComp"));
	ProjectileSpringArmComp->SetupAttachment(RootComponent);

	ProjectileCameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("ProjectileCameraComp"));
	ProjectileCameraComp->SetupAttachment(ProjectileSpringArmComp);
	/** KillShotCode end */
}

void AKillShotCamerasProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

		Destroy();
	}
}

void AKillShotCamerasProjectile::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!bActivatedTransition && 
		EnemyToKill &&
		(EnemyToKill->GetActorLocation() - GetActorLocation()).Size() <= DeathCameraTransitionDistance
	)
	{
		// We're near the enemy, enable the camera transition
		EnemyToKill->EnableCameraTransition();
		bActivatedTransition = true;
	}
}
