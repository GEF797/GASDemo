// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GASCharacter.h"
#include "Player/GASPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AGASCharacter::AGASCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	NetCullDistanceSquared = 900000000.0f;



	UCharacterMovementComponent* MoveComp = CastChecked<UCharacterMovementComponent>(GetCharacterMovement());
	MoveComp->GravityScale = 1.0f;
	MoveComp->MaxAcceleration = 2400.0f;
	MoveComp->BrakingFrictionFactor = 1.0f;
	MoveComp->BrakingFriction = 6.0f;
	MoveComp->GroundFriction = 8.0f;
	MoveComp->BrakingDecelerationWalking = 1400.0f;
	MoveComp->bUseControllerDesiredRotation = false;
	MoveComp->bOrientRotationToMovement = false;
	MoveComp->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	MoveComp->bAllowPhysicsRotationDuringAnimRootMotion = false;
	MoveComp->GetNavAgentPropertiesRef().bCanCrouch = true;
	MoveComp->bCanWalkOffLedgesWhenCrouching = true;
	MoveComp->SetCrouchedHalfHeight(65.0f);


	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

}

FGenericTeamId AGASCharacter::GetGenericTeamId() const
{
	return MyTeamID;
}

void AGASCharacter::BP_SetGenericTeamId(const FGenericTeamId& NewTeamID)
{
	SetGenericTeamId(NewTeamID);
}

void AGASCharacter::SetGenericTeamId(const FGenericTeamId& NewTeamID)
{
	if (HasAuthority())
	{
		const FGenericTeamId OldTeamID = MyTeamID;

		MARK_PROPERTY_DIRTY_FROM_NAME(ThisClass, MyTeamID, this);
		MyTeamID = NewTeamID;
	}

}
void AGASCharacter::OnRep_MyTeamID(FGenericTeamId OldTeamID)
{
}

URPGAbilitySystemComponent* AGASCharacter::GetRPGAbilitySystemComponent() const
{
	if (AGASPlayerState* PS = Cast<AGASPlayerState>(GetPlayerState()))
	{
		return PS->GetRPGAbilitySystemComponent();
	}
	return nullptr;
}

UAbilitySystemComponent* AGASCharacter::GetAbilitySystemComponent() const
{
	if (AGASPlayerState* PS=Cast<AGASPlayerState>(GetPlayerState()))
	{
		return PS->GetAbilitySystemComponent();
	}
	return nullptr;
}

void AGASCharacter::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	if (const URPGAbilitySystemComponent* ASC = GetRPGAbilitySystemComponent())
	{
		ASC->GetOwnedGameplayTags(TagContainer);
	}
}

bool AGASCharacter::HasMatchingGameplayTag(FGameplayTag TagToCheck) const
{
	if (const URPGAbilitySystemComponent* ASC = GetRPGAbilitySystemComponent())
	{
		return ASC->HasMatchingGameplayTag(TagToCheck);
	}

	return false;
}

bool AGASCharacter::HasAllMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const
{
	if (const URPGAbilitySystemComponent* ASC = GetRPGAbilitySystemComponent())
	{
		return ASC->HasAllMatchingGameplayTags(TagContainer);
	}

	return false;
}

bool AGASCharacter::HasAnyMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const
{
	if (const URPGAbilitySystemComponent* ASC = GetRPGAbilitySystemComponent())
	{
		return ASC->HasAnyMatchingGameplayTags(TagContainer);
	}

	return false;
}

void AGASCharacter::PossessedBy(AController* NewController)
{
Super::PossessedBy(NewController);
if (GetAbilitySystemComponent())
{
if (NewController->PlayerState)
{
	
		GetAbilitySystemComponent()->InitAbilityActorInfo(NewController->PlayerState,this);
	
}
else
{
		GetAbilitySystemComponent()->InitAbilityActorInfo(this, this);
}
}
}
     



void AGASCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	FDoRepLifetimeParams SharedParams;
	SharedParams.bIsPushBased = true;

	DOREPLIFETIME_WITH_PARAMS_FAST(ThisClass, MyTeamID, SharedParams);

}




