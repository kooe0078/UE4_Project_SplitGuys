
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletSpawner.generated.h"

UCLASS()
class PROJECT_SPLITGUYS_API ABulletSpawner : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	class UStaticMeshComponent* bodyCube;
	UPROPERTY(EditInstanceOnly)
	class UStaticMeshComponent* barrel;
	
public:	
	// Sets default values for this actor's properties
	ABulletSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
