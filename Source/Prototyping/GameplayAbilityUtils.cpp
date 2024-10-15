// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilityUtils.h"
#include "Abilities/GameplayAbility.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectTypes.h"

float UGameplayAbilityUtils::GetAbilityCost(TSubclassOf<UGameplayAbility> AbilityClass, AActor* OwnerActor)
{
    if (!AbilityClass || !OwnerActor)
    {
        return 0.0f; // Invalid input
    }

    // Get the default object of the Gameplay Ability class
    UGameplayAbility* Ability = AbilityClass->GetDefaultObject<UGameplayAbility>();
    if (!Ability)
    {
        return 0.0f; // Failed to get the ability
    }

    // Get the owner’s ability system component
    UAbilitySystemComponent* ASC = OwnerActor->FindComponentByClass<UAbilitySystemComponent>();
    if (!ASC)
    {
        return 0.0f; // Failed to find Ability System Component
    }

    // Iterate through the cost Gameplay Effects
    const UGameplayEffect* CostEffectClass = Ability->GetCostGameplayEffect();
    
    float MagnitudeValue = 0.0f;

    CostEffectClass->Modifiers[0].ModifierMagnitude.GetStaticMagnitudeIfPossible(0.0f, MagnitudeValue);

    return MagnitudeValue;
}
