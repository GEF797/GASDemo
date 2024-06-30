// Copyright G.E.FC 2024


#include "AbilitySystem/TestExecutionCalculation.h"

UTestExecutionCalculation::UTestExecutionCalculation()
{
	RelevantAttributesToCapture.Add(RPGStatics().DamageDef);
}

void UTestExecutionCalculation::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	UAbilitySystemComponent* TargetAbilitySystemComponent = ExecutionParams.GetTargetAbilitySystemComponent();
	UAbilitySystemComponent* SourceAbilitySystemComponent = ExecutionParams.GetSourceAbilitySystemComponent();

	AActor* SourceActor = SourceAbilitySystemComponent ? SourceAbilitySystemComponent->GetAvatarActor_Direct() : nullptr;
	AActor* TargetActor = TargetAbilitySystemComponent ? TargetAbilitySystemComponent->GetAvatarActor_Direct() : nullptr;

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	// Gather the tags from the source and target as that can affect which buffs should be used
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;


	float Damage = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(RPGStatics().DamageDef, EvaluationParameters, Damage);


	float DamageDone = Damage;
	
	DamageDone = FMath::FloorToInt(FMath::Clamp(DamageDone, 1, 99999));

	if (DamageDone > 0.0f)
	{
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(UTestAttributeSet::GetDamageAttribute(), EGameplayModOp::Additive, DamageDone));
	}
}
