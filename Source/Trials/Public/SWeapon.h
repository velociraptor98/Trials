// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SWeapon.generated.h"

class USkeletalMesh;
class UParticleSystem;
class UDamageType;
class UCameraShake;
UCLASS()
class TRIALS_API ASWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASWeapon();

protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components")
	USkeletalMeshComponent* MeshComp;
	UFUNCTION(BlueprintCallable,Category="Guns")
	void Fire();
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Guns")
	TSubclassOf<UDamageType> DamageType;
	UPROPERTY(VisibleDefaultsOnly,BlueprintReadOnly,Category="Guns")
	FName MuzzleSocketName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
	UParticleSystem* Muzzle;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
	UParticleSystem* ImpactEffect;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
	UParticleSystem* Tracer;
	UPROPERTY(EditDefaultsOnly,Category="Guns")
	TSubclassOf<UCameraShake> OnFireShake;
public:	
	

};
