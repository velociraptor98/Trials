// Fill out your copyright notice in the Description page of Project Settings.


#include "public/SWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASWeapon::ASWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	RootComponent = MeshComp;
	MuzzleSocketName = "MuzzleSocket";
}

// Called when the game starts or when spawned
void ASWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASWeapon::Fire()
{
	AActor* Owner;
	Owner = GetOwner();
	if (Owner)
	{
		FVector EyesLoc;
		FRotator EyesRot;
		Owner->GetActorEyesViewPoint(EyesLoc, EyesRot);
		FVector ShootDirection = EyesRot.Vector();
		//FVector TraceEnd = EyesLoc + (EyesRot.Vector() * 10000);
		FCollisionQueryParams Query;
		Query.AddIgnoredActor(Owner);
		Query.AddIgnoredActor(this);
		Query.bTraceComplex = true;
		FHitResult Hit;
		if(GetWorld()->LineTraceSingleByChannel(Hit,EyesLoc,EyesLoc+(EyesRot.Vector()*10000),ECC_Visibility,Query))
		{
			AActor* HitActor = Hit.GetActor();
			FString a= Hit.GetActor()->GetHumanReadableName();
			UGameplayStatics::ApplyPointDamage(HitActor,20.0f,ShootDirection,Hit,Owner->GetInstigatorController(),this,DamageType);
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
		}
		DrawDebugLine(GetWorld(), EyesLoc, EyesLoc + (EyesRot.Vector() * 10000), FColor::White, false, 1.0f, 0, 1.0f);
		if(Muzzle)
		{
			UGameplayStatics::SpawnEmitterAttached(Muzzle, MeshComp, MuzzleSocketName);
		}
		
	}
}

// Called every frame
void ASWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

