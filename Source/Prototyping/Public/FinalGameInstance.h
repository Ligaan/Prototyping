// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "FinalGameInstance.generated.h"

/**
 * 
 */
//USTRUCT(BlueprintType)
//struct FFinalSessionCustomUIType
//{
//	GENERATED_BODY()
//
//	UPROPERTY(BlueprintReadOnly)
//	FString SessionId;
//
//	UPROPERTY(BlueprintReadOnly)
//	FString SessionName;
//
//	UPROPERTY(BlueprintReadOnly)
//	int32 CurrentPlayerNumber;
//
//	UPROPERTY(BlueprintReadOnly)
//	int32 MaxPlayerNumber;
//};

UCLASS()
class PROTOTYPING_API UFinalGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UFinalGameInstance();

//	// Function to initiate login
//	UFUNCTION(BlueprintCallable, Category = "EOS Functions")
//	void LoginToEpicGames();
//	UFUNCTION(BlueprintCallable, Category = "EOS Functions")
//	void LoginAsDev(FString user);
//	// Create Session
//	UFUNCTION(BlueprintCallable, Category = "EOS Functions")
//	void CreateSession(FName sessionName, int32 NumOfPublicConnections);
//	UFUNCTION(BlueprintCallable, Category = "EOS Functions")
//	void CreateLobby(FName sessionName, int32 NumOfPublicConnections);
//
//
//
//
//	//Utilities
//	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "EOS Functions")
//	bool IsPlayerLoggedIn();
//
//	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "EOS Functions")
//
//	FString GetPlayerUsername();
//
//	// Variables
//	// Pointer to the session interface
//	IOnlineSessionPtr SessionInterface;
//
//private:
//	// Callback for login completion
//	void OnLoginComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& error);
//	// Callback for create session complete
//	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
//
//	//Variables
//	// Store the login complete delegate handle
//	FDelegateHandle LoginCompleteDelegateHandle;
//	// Store the create session complete delegate handle
//	FDelegateHandle CreateSessionCompleteDelegateHandle;
//
//	FString PlayerUserId;
//	FName lSessionName;
//	FString SessionToJoin;
//	int32 SessionSearchIndex = 0;
};
