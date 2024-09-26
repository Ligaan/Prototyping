// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayFab.h"
#include "Core/PlayFabError.h"
#include "Core/PlayFabClientDataModels.h"
#include "Core/PlayFabMultiplayerDataModels.h"
#include "LobbyUtilityFunctions.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPING_API ULobbyUtilityFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	public:
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "MMember", Keywords = "member"), Category = "Playfab")
        static void OnSuccess();
		
};
