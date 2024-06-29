// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GenericTeamAgentInterface.h"
#include "Player/GASInputComponent.h"
#include "GASPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GASDEMO_API AGASPlayerController : public APlayerController,public IGenericTeamAgentInterface
{
	GENERATED_BODY()
	
public:

    UFUNCTION(BlueprintCallable)
	void BindingInput(const TMap<FGameplayTag, UInputAction*> InputConfig);



	virtual void PostProcessInput(const float DeltaTime, const bool bGamePaused) override;


	void Input_AbilityInputTagPressed(FGameplayTag InputTag);
	void Input_AbilityInputTagReleased(FGameplayTag InputTag);

	virtual FGenericTeamId GetGenericTeamId() const override;


};
