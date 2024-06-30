// Copyright G.E.FC 2024

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "AbilitySystem/TestAttributeSet.h"
#include "TestExecutionCalculation.generated.h"


struct FRPGStatics
{

	//FGameplayEffectAttributeCaptureDefinition HealthDef;
	FGameplayEffectAttributeCaptureDefinition DamageDef;

	FRPGStatics()
	{
		//HealthDef = FGameplayEffectAttributeCaptureDefinition(UTestAttributeSet::GetHealthAttribute(), EGameplayEffectAttributeCaptureSource::Target, false);
		DamageDef = FGameplayEffectAttributeCaptureDefinition(UTestAttributeSet::GetBaseDamageAttribute(), EGameplayEffectAttributeCaptureSource::Source, true);


	}
};

static FRPGStatics& RPGStatics()
{
	static FRPGStatics Statics;
	return Statics;
}
/**
 * 
 */
UCLASS()
class GASDEMO_API UTestExecutionCalculation : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
	
public:
	// Constructor and overrides
	UTestExecutionCalculation();
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
