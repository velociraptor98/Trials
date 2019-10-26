// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/SCharacter.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PawnMovementComponent.h"


// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	ArmComp->bUsePawnControlRotation = true;
	ArmComp->SetupAttachment(RootComponent);
    APawn::GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;
	ACharacter::GetMovementComponent()->GetNavAgentPropertiesRef().bCanJump = true;
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(ArmComp);
	ZoomedFOV = 65.0f;
	ZoomInterpSpeed = 20;
}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	DefaultFOV=CameraComp->FieldOfView;
}

void ASCharacter::BeginCrouch()
{
	Crouch();
	UE_LOG(LogTemp, Warning, TEXT("ENTERED CROUCH"));
}

void ASCharacter::EndCrouch()
{
	UnCrouch();
}

void ASCharacter::Jumping()
{
	UE_LOG(LogTemp, Warning, TEXT("ENTERED Jump"));
	Jump();
}

// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float TargetFOV = bCanZoom ? ZoomedFOV : DefaultFOV;
	float CurrentFOV = FMath::FInterpTo(CameraComp->FieldOfView,TargetFOV,DeltaTime,ZoomInterpSpeed);
	CameraComp->SetFieldOfView(CurrentFOV);
}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ASCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn",this,&ASCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ASCharacter::BeginCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &ASCharacter::EndCrouch);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASCharacter::Jumping);
	PlayerInputComponent->BindAction("Zoom", IE_Pressed, this, &ASCharacter::BeginZoom);
	PlayerInputComponent->BindAction("Zoom", IE_Released, this, &ASCharacter::EndZoom);
}

FVector ASCharacter::GetPawnViewLocation() const
{
	if(CameraComp)
	{
		return (CameraComp->GetComponentLocation());
	}
	return Super::GetPawnViewLocation();
}

void ASCharacter::MoveForward(float Val)
{
	AddMovementInput(GetActorForwardVector()*Val);
}
void ASCharacter::MoveRight(float Val)
{
	AddMovementInput(GetActorRightVector()*Val);
}

void ASCharacter::BeginZoom()
{
	bCanZoom = true;
}

void ASCharacter::EndZoom()
{
	bCanZoom = false;
}



