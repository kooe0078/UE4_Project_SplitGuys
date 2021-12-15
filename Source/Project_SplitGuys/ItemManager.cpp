// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemManager.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

AItemManager::AItemManager()
{
	PrimaryActorTick.bCanEverTick = true;

	boxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("box"));
	boxCollision->SetGenerateOverlapEvents(true);
	RootComponent = boxCollision;

	cubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("cube"));
	cubeMesh->SetupAttachment(RootComponent);

}

void AItemManager::BeginPlay()
{
	Super::BeginPlay();

	FScriptDelegate overlap_delegate;
	overlap_delegate.BindUFunction(this, FName("OnOverlapEvent"));
	boxCollision->OnComponentBeginOverlap.Add(overlap_delegate);
}

// Called every frame
void AItemManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemManager::OnOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
								int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "Get Item!");

	this->overlapAction();
	this->Destroy();
}