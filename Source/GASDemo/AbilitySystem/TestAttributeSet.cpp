// Copyright G.E.FC 2024


#include "AbilitySystem/TestAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"
#include "NativeGameplayTags.h"
#include "TestAttributeSet.h"



UE_DEFINE_GAMEPLAY_TAG_STATIC(TAG_GameplayEvent_Death, "GameplayEvent.Dead");


UTestAttributeSet::UTestAttributeSet()
	: Health(100.0f)
	, MaxHealth(100.0f)
	,Mana(100.0f)
	,MaxMana(100.0f)
	,EP(5.0f)
	,MaxEP(5.0f)
{
}

void UTestAttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTestAttributeSet, Health, OldValue);
}

void UTestAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTestAttributeSet, MaxHealth, OldValue);
}

void UTestAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTestAttributeSet, Mana, OldValue);
}

void UTestAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTestAttributeSet, MaxMana, OldValue);
}

void UTestAttributeSet::OnRep_EP(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTestAttributeSet, EP, OldValue);
}

void UTestAttributeSet::OnRep_MaxEP(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTestAttributeSet, MaxEP, OldValue);
}

void UTestAttributeSet::OnRep_BaseDamage(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTestAttributeSet, BaseDamage, OldValue);
}

bool UTestAttributeSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
	return Super::PreGameplayEffectExecute(Data);

}

void UTestAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	const FGameplayEffectContextHandle& EffectContext = Data.EffectSpec.GetEffectContext();
	AActor* Instigator = EffectContext.GetOriginalInstigator();
	AActor* Causer = EffectContext.GetEffectCauser();

	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		// Convert into -Health and then clamp
		SetHealth(FMath::Clamp(GetHealth() - GetDamage(), 0, GetMaxHealth()));
		SetDamage(0.0f);
	}
	else if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		// Clamp and fall into out of health handling below
		SetHealth(FMath::Clamp(GetHealth(), 0, GetMaxHealth()));
	}
	if ((GetHealth() <= 0.0f))
	{
#if WITH_SERVER_CODE
	FGameplayEventData Payload;
	Payload.EventTag = TAG_GameplayEvent_Death;
	Payload.Instigator = Instigator;
	Payload.Target = GetOwningAbilitySystemComponent()->GetAvatarActor();
	Payload.OptionalObject = Data.EffectSpec.Def;
	Payload.OptionalObject2 = Causer;
	Payload.ContextHandle = Data.EffectSpec.GetEffectContext();
	//Payload.InstigatorTags = &Data.EffectSpec.CapturedSourceTags->GetAggregatedTags();
	//Payload.TargetTags = &Data.EffectSpec.CapturedTargetTags->GetAggregatedTags();
	Payload.EventMagnitude = Data.EvaluatedData.Magnitude;

	FScopedPredictionWindow NewScopedWindow(GetOwningAbilitySystemComponent(), true);
	GetOwningAbilitySystemComponent()->HandleGameplayEvent(Payload.EventTag, &Payload);

#endif
}
}

void UTestAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);

	ClampAttribute(Attribute, NewValue);
}

void UTestAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	ClampAttribute(Attribute, NewValue);
}

void UTestAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
}

void UTestAttributeSet::ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const
{
	if (Attribute == GetHealthAttribute())
	{
		// Do not allow health to go negative or above max health.
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());

		return;
	}
	if (Attribute == GetMaxHealthAttribute())
	{
		// Do not allow max health to drop below 1.
		NewValue = FMath::Max(NewValue, 1.0f);

		return;
	}

	if (Attribute == GetManaAttribute())
	{
		// Do not allow health to go negative or above max health.
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxMana());

		return;
	}
	if (Attribute == GetMaxManaAttribute())
	{
		// Do not allow max health to drop below 1.
		NewValue = FMath::Max(NewValue, 1.0f);

		return;
	}

	if (Attribute == GetEPAttribute())
	{
		// Do not allow health to go negative or above max health.
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxEP());

		return;
	}
	if (Attribute == GetMaxEPAttribute())
	{
		// Do not allow max health to drop below 1.
		NewValue = FMath::Max(NewValue, 1.0f);

		return;
	}
}

void UTestAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UTestAttributeSet, BaseDamage, COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTestAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTestAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTestAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTestAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTestAttributeSet, EP, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTestAttributeSet, MaxEP, COND_None, REPNOTIFY_Always);

}
