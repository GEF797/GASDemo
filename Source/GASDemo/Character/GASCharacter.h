// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Player/GASInputComponent.h"
#include "GameFramework/Character.h"
#include "GameplayTagAssetInterface.h"
#include "GenericTeamAgentInterface.h"
#include "AbilitySystem/RPGAbilitySystemComponent.h"
#include "GASCharacter.generated.h"

UCLASS()
class GASDEMO_API AGASCharacter : public ACharacter,public IAbilitySystemInterface, public IGenericTeamAgentInterface , public IGameplayTagAssetInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGASCharacter(const FObjectInitializer& ObjectInitializer);

	//Set TeamID
	UFUNCTION(BlueprintCallable, DisplayName = "SetGenericTeamId", Category = "RPG|Character")
	void BP_SetGenericTeamId(const FGenericTeamId& NewTeamID);

	virtual void SetGenericTeamId(const FGenericTeamId& NewTeamID) override;
	virtual FGenericTeamId GetGenericTeamId() const override;


	UFUNCTION(BlueprintCallable, Category = "RPG|Character")
	URPGAbilitySystemComponent* GetRPGAbilitySystemComponent() const;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;



protected:

	UFUNCTION()
	void OnRep_MyTeamID(FGenericTeamId OldTeamID);

	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;
	virtual bool HasMatchingGameplayTag(FGameplayTag TagToCheck) const override;
	virtual bool HasAllMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const override;
	virtual bool HasAnyMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const override;

	virtual void PossessedBy(AController* NewController) override;

	private:
		UPROPERTY(ReplicatedUsing = OnRep_MyTeamID)
		FGenericTeamId MyTeamID;
};
