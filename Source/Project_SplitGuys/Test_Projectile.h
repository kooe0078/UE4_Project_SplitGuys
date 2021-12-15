
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Test_Projectile.generated.h"

UCLASS()
class PROJECT_SPLITGUYS_API ATest_Projectile : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleDefaultsOnly, Category = "Projectile") 
	class USphereComponent* Collision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	class UProjectileMovementComponent* ProjectileMovement;

public:	
	// Sets default values for this actor's properties
	ATest_Projectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
