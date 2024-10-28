// Fill out your copyright notice in the Description page of Project Settings.


#include "StringUtils.h"
#include "Misc/Crc.h"

int32 UStringUtils::StringToNumber(const FString& String)
{
	return static_cast<int32>(FCrc::StrCrc32(*String));
}

FLinearColor UStringUtils::NumberToColor(int32 Color)
{
    Color = FMath::Abs(Color);

    // Extract RGBA values from the integer
    uint8 Red = (Color >> 24) & 0xFF;
    uint8 Green = (Color >> 16) & 0xFF;
    uint8 Blue = (Color >> 8) & 0xFF;
    uint8 Alpha = Color & 0xFF;

    // Return an FLinearColor or FColor
    return FLinearColor(Red / 255.0f, Green / 255.0f, Blue / 255.0f, Alpha / 255.0f);
}
