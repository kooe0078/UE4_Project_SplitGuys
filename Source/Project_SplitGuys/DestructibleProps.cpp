// Fill out your copyright notice in the Description page of Project Settings.


#include "DestructibleProps.h"
#include "Components/BoxComponent.h"
#include "DestructibleComponent.h"

ADestructibleProps::ADestructibleProps()
{
	PrimaryActorTick.bCanEverTick = true;

	destructibleComponent = CreateDefaultSubobject<UDestructibleComponent>(TEXT("destructibleComponent"));
	RootComponent = destructibleComponent;
	destructibleComponent->SetNotifyRigidBodyCollision(true);
	destructibleComponent->SetGenerateOverlapEvents(true);

	triggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("triggerBox"));
	triggerBox->SetupAttachment(RootComponent);

	bIsTrigger = false;
	bIsDestroy = false;

	maxHealth = 50.0f;

	defaultDamage = 10.0f;
	defaultImpulse = 10.0f;
}

void ADestructibleProps::BeginPlay()
{
	Super::BeginPlay();

	FScriptDelegate hit_delegate;
	hit_delegate.BindUFunction(this, FName("OnHitEvent"));
	destructibleComponent->OnComponentHit.Add(hit_delegate);

	FScriptDelegate overlap_delegate;
	overlap_delegate.BindUFunction(this, FName("OnOverlapEvent"));
	triggerBox->OnComponentBeginOverlap.Add(overlap_delegate);

	health = maxHealth;
}

void ADestructibleProps::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADestructibleProps::OnHitEvent(UPrimitiveComponent* OnComponentHit, UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	if (bIsDestroy && OtherActor->ActorHasTag("Player")) {
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, __FUNCTION__);
		health -= 10.0f;
		if (health <= 0.0f) {
			Destroy();
		}
	}
}

void ADestructibleProps::OnOverlapEvent(UPrimitiveComponent* OnComponentBeginOverlap, UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {

	if (bIsDestroy && bIsTrigger && OtherActor->ActorHasTag("Player")) {
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, __FUNCTION__);
		health -= 10.0f;
		if (health <= 0.0f) {
			Destroy();
		}
	}

}

void ADestructibleProps::Destroy() {
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, __FUNCTION__);

	if (!bIsDestroy) {
		bIsDestroy = true;
	}
}
