// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlatformActor.generated.h"

UCLASS()
class PROJECT_SPLITGUYS_API APlatformActor : public AActor
{
	GENERATED_BODY()
	
public:	
	APlatformActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
