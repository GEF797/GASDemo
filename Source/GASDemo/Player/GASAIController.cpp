// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/GASAIController.h"
#include "GenericTeamAgentInterface.h"
#include "Player/GASPlayerState.h"

FGenericTeamId AGASAIController::GetGenericTeamId() const
{
	if (const IGenericTeamAgentInterface* TeamInterface = Cast<IGenericTeamAgentInterface>(GetPawn()))
	{
		return TeamInterface->GetGenericTeamId();
	}
	return FGenericTeamId::NoTeam;
}