// Copyright Epic Games, Inc. All Rights Reserved.

#include "Project_SplitGuysGameMode.h"
#include "Project_SplitGuysCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProject_SplitGuysGameMode::AProject_SplitGuysGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
