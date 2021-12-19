// Fill out your copyright notice in the Description page of Project Settings.


#include "Test_Projectile.h"
#include "Engine/Classes/Components/SphereComponent.h"
#include "Engine/Classes/GameFramework/ProjectileMovementComponent.h"
#include "Project_SplitGuysCharacter.h"
#include "Kismet/GameplayStatics.h"


ATest_Projectile::ATest_Projectile()
{
	PrimaryActorTick.bCanEverTick = true;
	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision")); 
	Collision->InitSphereRadius(32.0f); 
	RootComponent = Collision;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement")); 
	ProjectileMovement->SetUpdatedComponent(Collision);
	ProjectileMovement->InitialSpeed = 2000.0f; 
	ProjectileMovement->MaxSpeed = 0.0f;
	ProjectileMovement->ProjectileGravityScale = 0.0f;	
}

void ATest_Projectile::BeginPlay()
{
	Super::BeginPlay();

	FScriptDelegate hit_delegate;
	hit_delegate.BindUFunction(this, FName("OnHitEvent"));
	Collision->OnComponentHit.Add(hit_delegate);
	//Collision->OnComponentHit.AddDynamic(this, &ATest_Projectile::OnHitEvent);
}

void ATest_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DestroyThisActor();
}


void ATest_Projectile::OnHitEvent(UPrimitiveComponent* HitComponent, AActor* OtherActor, 
								UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	Destroy();
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (OtherActor == PlayerPawn) {
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "Bullet Hit!");
		AProject_SplitGuysCharacter* player_char = Cast<AProject_SplitGuysCharacter>(OtherActor);
		player_char->health -= 5.0f;
	}
}

void ATest_Projectile::DestroyThisActor() {
	FTimerHandle TimerHandle;
	float delayTime = 3.0f;

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]()
	{
		UE_LOG(LogTemp, Warning, TEXT("3초"));
		// TimerHandle 초기화
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		Destroy();
	}), delayTime, false);
}