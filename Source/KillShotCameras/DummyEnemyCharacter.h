// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DummyEnemyCharacter.generated.h"

UCLASS()
class KILLSHOTCAMERAS_API ADummyEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADummyEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	/** The blend time in seconds, from the projectile\s camera to correspondent death camera */
	UPROPERTY(EditAnywhere)
	float DeathCameraBlendTime = 0.05f;

	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* DeathSpringArmComp;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* DeathCameraComp;
	
public:
	/** Transmission the active amera to the corresponding death camera */
	void EnableCameraTransition();
	
};
