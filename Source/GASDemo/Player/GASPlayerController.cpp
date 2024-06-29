// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/GASPlayerController.h"
#include "Player/GASPlayerState.h"
#include "Character/GASCharacter.h"
#include "AbilitySystem/RPGAbilitySystemComponent.h"

void AGASPlayerController::BindingInput(const TMap<FGameplayTag, UInputAction*> InputConfig)
{
	TArray<uint32> BindHandles;

	const APawn* ControlPawn = GetPawn<APawn>();
	if (!ControlPawn)
	{
		return;
	}

	UGASInputComponent* IC = ControlPawn->FindComponentByClass<UGASInputComponent>();
	check(IC);

	IC->BindAbilityActions(InputConfig, this, &ThisClass::Input_AbilityInputTagPressed, &ThisClass::Input_AbilityInputTagReleased, /*out*/ BindHandles);


}



void AGASPlayerController::PostProcessInput(const float DeltaTime, const bool bGamePaused)
{
	if (AGASPlayerState* PS = CastChecked<AGASPlayerState>(PlayerState, ECastCheckedType::NullAllowed))
	{
		if (URPGAbilitySystemComponent* ASC = PS->GetRPGAbilitySystemComponent())
		{
			ASC->ProcessAbilityInput(DeltaTime, bGamePaused);
		}
	}


	Super::PostProcessInput(DeltaTime, bGamePaused);
}




FGenericTeamId AGASPlayerController::GetGenericTeamId() const
{
	if (const IGenericTeamAgentInterface* TeamInterface = Cast<IGenericTeamAgentInterface>(GetPawn()))
	{
		return TeamInterface->GetGenericTeamId();
	}
	return FGenericTeamId::NoTeam;
}


void AGASPlayerController::Input_AbilityInputTagPressed(FGameplayTag InputTag)
{
	if (auto Char = GetPawn<AGASCharacter>())
	{
		if (URPGAbilitySystemComponent* ASC = Char->GetRPGAbilitySystemComponent())
		{
			ASC->AbilityInputTagPressed(InputTag);
		}

	}
}

void AGASPlayerController::Input_AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (auto Char = GetPawn<AGASCharacter>())
	{
		if (URPGAbilitySystemComponent* ASC = Char->GetRPGAbilitySystemComponent())
		{
			ASC->AbilityInputTagReleased(InputTag);
		}

	}
}
