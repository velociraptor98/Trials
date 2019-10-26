// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class TRIALS_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void MoveForward(float Val);
	void MoveRight(float Val);
	void BeginZoom();
	void EndZoom();
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components")
	UCameraComponent* CameraComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* ArmComp;
	void BeginCrouch();
	void EndCrouch();
	void Jumping();

	bool bCanZoom;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Components")
	float ZoomedFOV;
	float DefaultFOV;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin=0.1,ClampMax=100))
	float ZoomInterpSpeed;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual FVector GetPawnViewLocation() const override;
};
