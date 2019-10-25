// Fill out your copyright notice in the Description page of Project Settings.


#include "public/SWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"

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
		//FVector TraceEnd = EyesLoc + (EyesRot.Vector() * 10000);
		FCollisionQueryParams Query;
		Query.AddIgnoredActor(Owner);
		Query.AddIgnoredActor(this);
		Query.bTraceComplex = true;
		if(GetWorld()->LineTraceSingleByChannel(Hit,EyesLoc,EyesLoc+(EyesRot.Vector()*1000),ECC_Visibility,Query))
		{
			
		}
		DrawDebugLine(GetWorld(), EyesLoc, EyesLoc + (EyesRot.Vector() * 1000), FColor::White, false, 1.0f, 0, 1.0f);
	}
}

// Called every frame
void ASWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

