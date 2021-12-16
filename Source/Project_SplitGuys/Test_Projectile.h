
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

private:
	UFUNCTION()
	void OnHitEvent(UPrimitiveComponent* HitComponent, AActor* OtherActor,
					UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
	void DestroyThisActor();

public:	
	ATest_Projectile();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
