// Fill out your copyright notice in the Description page of Project Settings.


#include "public/SWeapon.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
ASWeapon::ASWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	RootComponent = MeshComp;

}

// Called when the game starts or when spawned
void ASWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASWeapon::Fire()
{
	FHitResult Hit;
	AActor* Owner;
	Owner = GetOwner();
	if (Owner)
	{
		FVector EyesLoc;
		FRotator EyesRot;
		Owner->GetActorEyesViewPoint(EyesLoc, EyesRot);
		FCollisionQueryParams Query;
		Query.AddIgnoredActor(Owner);
		Query.AddIgnoredActor(this);
		Query.bTraceComplex = true;
		GetWorld()->LineTraceSingleByChannel(Hit,EyesLoc,EyesLoc+(EyesRot.Vector()*1000),ECC_Visibility,Query,);
	}
}

// Called every frame
void ASWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

