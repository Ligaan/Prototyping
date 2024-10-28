// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "StringUtils.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPING_API UStringUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category = "StringUtils")
	static int32 StringToNumber(const FString& String);
	UFUNCTION(BlueprintPure, Category = "StringUtils")
	static FLinearColor NumberToColor(int32 Color);
};
