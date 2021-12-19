// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlatformActor.generated.h"

UCLASS()
class PROJECT_SPLITGUYS_API APlatformActor : public AActor
{
	GENERATED_BODY()
	
	// �ڽ� �ݸ���
	class UBoxComponent* boxColl;
	// ���� ��ü
	UPROPERTY(EditInstanceOnly)
	class UStaticMeshComponent* cubePlat;
	// ����� ��ü
	UPROPERTY(EditInstanceOnly)
	class UStaticMeshComponent* destroyMesh;

public:	
	APlatformActor();

	// �浹 �̺�Ʈ
	UFUNCTION()
	void OnOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
