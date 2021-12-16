// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformActor.h"

APlatformActor::APlatformActor()
{
	PrimaryActorTick.bCanEverTick = true;

}

void APlatformActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlatformActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

