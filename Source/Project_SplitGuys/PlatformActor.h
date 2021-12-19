// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlatformActor.generated.h"

UCLASS()
class PROJECT_SPLITGUYS_API APlatformActor : public AActor
{
	GENERATED_BODY()
	
	// 박스 콜리전
	class UBoxComponent* boxColl;
	// 발판 물체
	UPROPERTY(EditInstanceOnly)
	class UStaticMeshComponent* cubePlat;
	// 사라질 물체
	UPROPERTY(EditInstanceOnly)
	class UStaticMeshComponent* destroyMesh;

public:	
	APlatformActor();

	// 충돌 이벤트
	UFUNCTION()
	void OnOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
