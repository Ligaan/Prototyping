// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayEffect.h"
#include "GameplayAbilityUtils.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPING_API UGameplayAbilityUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category = "GAS")
	static float GetAbilityCost(TSubclassOf<UGameplayAbility> AbilityClass, AActor* OwnerActor);
};
