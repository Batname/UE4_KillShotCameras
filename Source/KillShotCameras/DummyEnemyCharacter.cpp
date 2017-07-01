// Fill out your copyright notice in the Description page of Project Settings.


#include "DummyEnemyCharacter.h"
#include "KillShotCamerasCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SkeletalMeshComponent.h"



// Sets default values
ADummyEnemyCharacter::ADummyEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DeathSpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("DeathSpringArmComp"));
	DeathSpringArmComp->SetupAttachment(RootComponent);

	DeathCameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("DeathCameraComp"));
	DeathCameraComp->SetupAttachment(DeathSpringArmComp);

}

// Called when the game starts or when spawned
void ADummyEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADummyEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADummyEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ADummyEnemyCharacter::EnableCameraTransition()
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetViewTargetWithBlend(this, DeathCameraBlendTime);
}

void ADummyEnemyCharacter::Die()
{
	USkeletalMeshComponent* CharSM = GetMesh();

	// Enable ragdoll physics for our dummy enamy (To simulate a dying effect)
	CharSM->SetSimulatePhysics(true);
	CharSM->SetAllBodiesSimulatePhysics(true);
	CharSM->WakeAllRigidBodies();
	CharSM->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	// Reset the global time to default
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f);

	FTimerHandle TimerHandle;
	FTimerDelegate TimerDel;

	TimerDel.BindLambda([&]()
	{
		// Deactivate the death camera
		DeathCameraComp->Deactivate();

		AKillShotCamerasCharacter* MainChar = Cast<AKillShotCamerasCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		MainChar->ResetActiveCamera();	
	});

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDel, CameraResetDelay, false);
}