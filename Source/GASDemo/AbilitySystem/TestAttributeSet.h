// Copyright G.E.FC 2024

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystem/RPGAbilitySystemComponent.h"
#include "TestAttributeSet.generated.h"



#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


/**
 * 
 */
UCLASS()
class GASDEMO_API UTestAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UTestAttributeSet();


	ATTRIBUTE_ACCESSORS(UTestAttributeSet, Health);
	ATTRIBUTE_ACCESSORS(UTestAttributeSet, MaxHealth);
	ATTRIBUTE_ACCESSORS(UTestAttributeSet, Mana);
	ATTRIBUTE_ACCESSORS(UTestAttributeSet, MaxMana);
	ATTRIBUTE_ACCESSORS(UTestAttributeSet, EP);
	ATTRIBUTE_ACCESSORS(UTestAttributeSet, MaxEP);
	ATTRIBUTE_ACCESSORS(UTestAttributeSet, Damage);
	ATTRIBUTE_ACCESSORS(UTestAttributeSet, BaseDamage);

protected:

	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_EP(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_MaxEP(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_BaseDamage(const FGameplayAttributeData& OldValue);


	virtual bool PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

	void ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const;

private:

	// The current health attribute.  The health will be capped by the max health attribute.  Health is hidden from modifiers so only executions can modify it.
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "RPG|Health", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Health;

	// The current max health attribute.  Max health is an attribute since gameplay effects can modify it.
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "RPG|Health", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxHealth;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "RPG|Health", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Mana;

	// The current max health attribute.  Max health is an attribute since gameplay effects can modify it.
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "RPG|Health", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxMana;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_EP, Category = "RPG|Health", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData EP;

	// The current max health attribute.  Max health is an attribute since gameplay effects can modify it.
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxEP, Category = "RPG|Health", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxEP;


	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BaseDamage, Category = "RPG|Health", Meta = (HideFromModifiers,AllowPrivateAccess = true))
	FGameplayAttributeData BaseDamage;

	// Incoming damage. This is mapped directly to -Health
	UPROPERTY(BlueprintReadOnly, Category = "RPG|Health", Meta = (HideFromModifiers, AllowPrivateAccess = true))
	FGameplayAttributeData Damage;


	
};
