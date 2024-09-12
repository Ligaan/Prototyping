// Fill out your copyright notice in the Description page of Project Settings.


#include "NewGravityMovementComponent.h"

void UNewGravityMovementComponent::UpdateGravityDirection(const FVector &newGravityDirection)
{
    SetGravityDirection(newGravityDirection);
}
