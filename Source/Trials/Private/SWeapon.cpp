// Fill out your copyright notice in the Description page of Project Settings.


#include "public/SWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraShake.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "trials.h"


// Sets default values

static int32 DebugWeaponDrawing = 0;
FAutoConsoleVariableRef CVARDEBUG(TEXT("COOP.DebugWeapons"), DebugWeaponDrawing, TEXT("Draw Debug lines for weapons"),ECVF_Cheat);
ASWeapon::ASWeapon()
{
	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	RootComponent = MeshComp;
	MuzzleSocketName = "MuzzleSocket";
	BaseDamage = 20.0f;
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
		Query.bReturnPhysicalMaterial = true;
		FHitResult Hit;
		FVector TracerEnd = EyesLoc + (EyesRot.Vector() * 10000);
		if (GetWorld()->LineTraceSingleByChannel(Hit, EyesLoc, EyesLoc + (EyesRot.Vector() * 10000), COLLISION_WEAPON, Query))
		{
			AActor* HitActor = Hit.GetActor();
			float DamageMul = 4.0f;
			float ActualDamage = BaseDamage;
			EPhysicalSurface SurfaceType = UPhysicalMaterial::DetermineSurfaceType(Hit.PhysMaterial.Get());
			switch(SurfaceType)
			{
			case SurfaceType1:
				if (DefaultImpactEffect)
				{
					ActualDamage = BaseDamage;
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FleshImpactEffect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
				}
				break;
			case SurfaceType2:
				if(FleshImpactEffect)
				{
					ActualDamage *= DamageMul;
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FleshImpactEffect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
				}
				break;
			default:
				if (DefaultImpactEffect)
				{
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DefaultImpactEffect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
				}
				break;
			}
			UGameplayStatics::ApplyPointDamage(HitActor, ActualDamage, ShootDirection, Hit, Owner->GetInstigatorController(), this, DamageType);
			TracerEnd = Hit.ImpactPoint;
		}
		if (DebugWeaponDrawing > 0)
		{
			DrawDebugLine(GetWorld(), EyesLoc, EyesLoc + (EyesRot.Vector() * 10000), FColor::White, false, 1.0f, 0, 1.0f);
		}
		if(Muzzle)
		{
			UGameplayStatics::SpawnEmitterAttached(Muzzle, MeshComp, MuzzleSocketName);
		}
		FVector MuzzleLocation = MeshComp->GetSocketLocation(MuzzleSocketName);
		if (Tracer)
		{
			FVector MuzzleLocation = MeshComp->GetSocketLocation(MuzzleSocketName);
			UParticleSystemComponent* TracerComponent =	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Tracer, MuzzleLocation);
			if(TracerComponent)
			{
				TracerComponent->SetVectorParameter("Target",TracerEnd);
			}
		}
		APawn* MOwner = Cast<APawn>(GetOwner());
		if(MOwner)
		{
			APlayerController* PC = Cast<APlayerController>(MOwner->GetController());
			if(PC)
			{
				PC->ClientPlayCameraShake(OnFireShake);
			}
		}
	}
}

