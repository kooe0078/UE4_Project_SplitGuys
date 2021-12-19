// Fill out your copyright notice in the Description page of Project Settings.


#include "Sprit_AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "Project_SplitGuysCharacter.h"

const FName ASprit_AIController::Key_playerPos(TEXT("playerPos"));

ASprit_AIController::ASprit_AIController() {
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("BlackboardData'/Game/NewMaked/BB_BT/BB_Split.BB_Split'"));
	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("BehaviorTree'/Game/NewMaked/BB_BT/BT_Sprit.BT_Sprit'"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}

	playerChar = NewObject<AProject_SplitGuysCharacter>();
}

void ASprit_AIController::OnPossess(APawn* InPawn) {
	Super::OnPossess(InPawn);
	RunAI();
}

void ASprit_AIController::RunAI() {
	if (UseBlackboard(BBAsset, Blackboard))
	{
		RunBehaviorTree(BTAsset);
	}
		
	FVector pos = playerChar->GetActorLocation();
	FVector targetPos = FVector(pos.X, pos.Y + 2000.0f, pos.Z);
	this->MoveToLocation(targetPos);
}

void ASprit_AIController::StopAI() {
	UBehaviorTreeComponent* BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (nullptr == BehaviorTreeComponent) return;

	BehaviorTreeComponent->StopTree(EBTStopMode::Safe);
}
