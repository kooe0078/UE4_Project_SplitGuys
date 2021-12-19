// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Sprit_AIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_SPLITGUYS_API ASprit_AIController : public AAIController
{
	GENERATED_BODY()

public:
	ASprit_AIController();

	virtual void OnPossess(APawn* InPawn) override;

	void RunAI();
	void StopAI();

	static const FName Key_playerPos;

	class AProject_SplitGuysCharacter* playerChar;

private:
	UPROPERTY()
		class UBehaviorTree* BTAsset;

	UPROPERTY()
		class UBlackboardData* BBAsset;
};
