// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "NewGravityMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPING_API UNewGravityMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
	public:
	UFUNCTION(Blueprintcallable)
	void UpdateGravityDirection(const FVector& newGravityDirection);
};
