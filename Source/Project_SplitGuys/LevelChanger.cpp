// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelChanger.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Project_SplitGuysCharacter.h"

ALevelChanger::ALevelChanger()
{
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	RootComponent = mesh;

	boxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComponent"));
	boxComponent->SetupAttachment(RootComponent);

}

void ALevelChanger::BeginPlay()
{
	Super::BeginPlay();
	
	FScriptDelegate overlap_delegate;
	overlap_delegate.BindUFunction(this, FName("OnOverlapEvent"));
	boxComponent->OnComponentBeginOverlap.Add(overlap_delegate);
}

void ALevelChanger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelChanger::OnOverlapEvent(UPrimitiveComponent* OnComponentBeginOverlap, UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {

	AProject_SplitGuysCharacter* playerChar = Cast<AProject_SplitGuysCharacter>(OtherActor);

	if (OtherActor->ActorHasTag("Player")) {
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, __FUNCTION__);
		UGameplayStatics::OpenLevel(this, changeLevelName);
	}
}