// Fill out your copyright notice in the Description page of Project Settings.


#include "LaserActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Project_SplitGuysCharacter.h"
#include "Kismet/GameplayStatics.h"

ALaserActor::ALaserActor()
{
	PrimaryActorTick.bCanEverTick = true;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	RootComponent = Body;

	Laser = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Laser"));
	Laser->SetupAttachment(RootComponent);

	Laser2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Laser2"));
	Laser2->SetupAttachment(RootComponent);

	rotation = 100.0f;
}

void ALaserActor::OnOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
								int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (OtherActor == PlayerPawn) {
		AProject_SplitGuysCharacter* player_char = Cast<AProject_SplitGuysCharacter>(OtherActor);
		player_char->health -= 5.0f;
	}
}

void ALaserActor::BeginPlay()
{
	Super::BeginPlay();

	FScriptDelegate overlap_delegate;
	overlap_delegate.BindUFunction(this, FName("OnOverlapEvent"));
	Laser->OnComponentBeginOverlap.Add(overlap_delegate);
	Laser2->OnComponentBeginOverlap.Add(overlap_delegate);
}

void ALaserActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float rot = rotation * DeltaTime;
	FRotator newRot(0.0f, rot, 0.0f);
	Body->AddLocalRotation(newRot);
}