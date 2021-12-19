// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestructibleProps.generated.h"

UCLASS()
class PROJECT_SPLITGUYS_API ADestructibleProps : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBoxComponent* triggerBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UDestructibleComponent* destructibleComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bIsTrigger;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bIsDestroy;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float maxHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float defaultDamage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float defaultImpulse;

public:	
	ADestructibleProps();

	UFUNCTION()
	void OnHitEvent(UPrimitiveComponent* OnComponentHit, UPrimitiveComponent* HitComponent, AActor* OtherActor,
				UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
	void OnOverlapEvent(UPrimitiveComponent* OnComponentBeginOverlap, UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
				UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void Destroy();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
