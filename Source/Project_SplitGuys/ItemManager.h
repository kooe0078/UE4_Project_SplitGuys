// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemManager.generated.h"

UCLASS()
class PROJECT_SPLITGUYS_API AItemManager : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditInstanceOnly)
	class UBoxComponent* boxCollision;
	UPROPERTY(EditInstanceOnly)
	class UStaticMeshComponent* cubeMesh;

public:
	UFUNCTION(BlueprintImplementableEvent)
	void overlapAction();

private:
	UFUNCTION()
	void OnOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	AItemManager();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

};
