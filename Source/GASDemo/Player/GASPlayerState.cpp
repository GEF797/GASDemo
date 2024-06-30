// Copyright G.E.FC 2024


#include "Player/GASPlayerState.h"


#include "GASPlayerState.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(GASPlayerState)

AGASPlayerState::AGASPlayerState(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AbilitySystemComponent = ObjectInitializer.CreateDefaultSubobject<URPGAbilitySystemComponent>(this, TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	// These attribute sets will be detected by AbilitySystemComponent::InitializeComponent. Keeping a reference so that the sets don't get garbage collected before that.
	TestAttributeSet = CreateDefaultSubobject<UTestAttributeSet>(TEXT("TestAttributeSet"));

	// AbilitySystemComponent needs to be updated at a high frequency.
	NetUpdateFrequency = 100.0f;



}





UAbilitySystemComponent* AGASPlayerState::GetAbilitySystemComponent() const
{
	return GetRPGAbilitySystemComponent();
}



FGenericTeamId AGASPlayerState::GetGenericTeamId() const
{
	if (GetPawn())
	{
		if (IGenericTeamAgentInterface* TeamInterface = Cast<IGenericTeamAgentInterface>(GetPawn()))
		{
			return TeamInterface->GetGenericTeamId();
		}
	}

	return FGenericTeamId();
}



void AGASPlayerState::ClientInitialize(AController* C)
{
    Super::ClientInitialize(C);
	if(AbilitySystemComponent&& GetPawn())
	{
		AbilitySystemComponent->InitAbilityActorInfo(this,GetPawn());
	}
}




