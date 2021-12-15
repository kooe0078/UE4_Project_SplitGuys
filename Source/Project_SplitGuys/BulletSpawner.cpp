// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletSpawner.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABulletSpawner::ABulletSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bodyCube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("bodyCube"));
	RootComponent = bodyCube;

	barrel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("barrel"));
	barrel->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABulletSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABulletSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

