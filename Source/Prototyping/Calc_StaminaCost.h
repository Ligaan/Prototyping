// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "Calc_StaminaCost.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPING_API UCalc_StaminaCost : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
public:
	UCalc_StaminaCost();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

	FGameplayEffectAttributeCaptureDefinition StaminaDef;
	FGameplayEffectAttributeCaptureDefinition MaxStaminaDef;
};
