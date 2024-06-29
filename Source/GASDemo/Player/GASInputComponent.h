// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "EnhancedInputComponent.h"
#include "GASInputComponent.generated.h"

/**
 * 
 */
UCLASS(Config = Input)
class GASDEMO_API UGASInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:

	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType>
	void BindAbilityActions( TMap<FGameplayTag, UInputAction*> InputConfigs, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, TArray<uint32>& BindHandles);

	
};

template<class UserClass, typename PressedFuncType, typename ReleasedFuncType>
inline void UGASInputComponent::BindAbilityActions(TMap<FGameplayTag, UInputAction*> InputConfigs, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, TArray<uint32>& BindHandles)
{
		for (const TPair<FGameplayTag, UInputAction*>& InputConfig : InputConfigs)
		{
			if (InputConfig.Value)
			{
				if (PressedFunc)
				{
					BindHandles.Add(BindAction(InputConfig.Value, ETriggerEvent::Triggered, Object, PressedFunc, InputConfig.Key).GetHandle());
				}

				if (ReleasedFunc)
				{
					BindHandles.Add(BindAction(InputConfig.Value, ETriggerEvent::Completed, Object, ReleasedFunc, InputConfig.Key).GetHandle());
				}
			}

		}
}
