// Fill out your copyright notice in the Description page of Project Settings.


#include "Test_Projectile.h"
#include "Engine/Classes/Components/SphereComponent.h"
#include "Engine/Classes/GameFramework/ProjectileMovementComponent.h"


ATest_Projectile::ATest_Projectile()
{
	PrimaryActorTick.bCanEverTick = true;
	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision")); 
	Collision->InitSphereRadius(32.0f); 
	RootComponent = Collision;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement")); 
	ProjectileMovement->SetUpdatedComponent(Collision);
	ProjectileMovement->InitialSpeed = 2000.0f; 
	ProjectileMovement->MaxSpeed = 0.0f;
	ProjectileMovement->ProjectileGravityScale = 0.0f;
}

void ATest_Projectile::BeginPlay()
{
	Super::BeginPlay();

	FScriptDelegate hit_delegate;
	hit_delegate.BindUFunction(this, FName("HitEvent"));
	Collision->OnComponentBeginOverlap.Add(hit_delegate);
}

void ATest_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}