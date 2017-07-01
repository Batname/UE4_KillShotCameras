// Fill out your copyright notice in the Description page of Project Settings.


#include "DummyEnemyCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"


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