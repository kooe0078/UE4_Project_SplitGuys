// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

APlatformActor::APlatformActor()
{
	PrimaryActorTick.bCanEverTick = true;

	// 박스 콜리전
	boxColl = CreateDefaultSubobject<UBoxComponent>(TEXT("boxColl"));
	boxColl->SetGenerateOverlapEvents(true);
	RootComponent = boxColl;

	// 발판 물체
	cubePlat = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("cubePlat"));
	cubePlat->SetupAttachment(RootComponent);

	// 사라질 물체
	destroyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("changeMesh"));
}

void APlatformActor::BeginPlay()
{
	Super::BeginPlay();

	FScriptDelegate overlap_delegate;
	overlap_delegate.BindUFunction(this, FName("OnOverlapEvent"));
	boxColl->OnComponentBeginOverlap.Add(overlap_delegate);
}

void APlatformActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// 발판 충돌 이벤트
void APlatformActor::OnOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "Destroy Platform!");
	Destroy();
}