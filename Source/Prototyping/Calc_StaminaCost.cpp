// Fill out your copyright notice in the Description page of Project Settings.


#include "Calc_StaminaCost.h"
#include "BasicAttributeSet.h"

UCalc_StaminaCost::UCalc_StaminaCost()
{
	StaminaDef.AttributeToCapture = UBasicAttributeSet::GetStaminaAttribute();
	StaminaDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	StaminaDef.bSnapshot = false;

	MaxStaminaDef.AttributeToCapture = UBasicAttributeSet::GetStaminaAttribute();
	MaxStaminaDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	MaxStaminaDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(StaminaDef);
	RelevantAttributesToCapture.Add(MaxStaminaDef);
}

float UCalc_StaminaCost::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float Stamina = 0.0f;
	GetCapturedAttributeMagnitude(StaminaDef, Spec, EvaluationParameters, Stamina);

	float MaxStamina = 0.0f;
	GetCapturedAttributeMagnitude(MaxStaminaDef, Spec, EvaluationParameters, MaxStamina);

	return FMath::Clamp(MaxStamina - Stamina,0.0f,1.0f);
}
