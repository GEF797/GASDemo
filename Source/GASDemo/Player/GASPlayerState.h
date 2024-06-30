// Copyright G.E.FC 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/TestAttributeSet.h"
#include "AbilitySystem/RPGAbilitySystemComponent.h"
#include "GenericTeamAgentInterface.h"
#include "GASPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class GASDEMO_API AGASPlayerState : public APlayerState, public IAbilitySystemInterface, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:

	AGASPlayerState(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());



	UFUNCTION(BlueprintCallable, Category = "RPG|PlayerState")
	URPGAbilitySystemComponent* GetRPGAbilitySystemComponent() const { return AbilitySystemComponent; }
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;



	virtual FGenericTeamId GetGenericTeamId() const override;




	protected:

		virtual void ClientInitialize(class AController* C);

private:



	// The ability system component sub-object used by player characters.
	UPROPERTY(VisibleAnywhere, Category = "RPG|PlayerState")
	TObjectPtr<URPGAbilitySystemComponent> AbilitySystemComponent;



	TObjectPtr<UTestAttributeSet> TestAttributeSet;
};
