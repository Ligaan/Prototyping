// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CommonUserSubsystem.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "TestGameInstance.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FSessionCustomUIType
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FString SessionId;

	UPROPERTY(BlueprintReadOnly)
	FString SessionName;

	UPROPERTY(BlueprintReadOnly)
	int32 CurrentPlayerNumber;

    UPROPERTY(BlueprintReadOnly)
	int32 MaxPlayerNumber;
};

UCLASS()
class PROTOTYPING_API UTestGameInstance : public UGameInstance
{
	GENERATED_BODY()
	public:
	UTestGameInstance();
	// Sets default values for this actor's properties
	UFUNCTION(BlueprintCallable, Category="EOS Functions")
	void CreateSession(FName sessionName,int32 NumOfPublicConnections);
	UFUNCTION(BlueprintCallable, Category="EOS Functions")
    void FindSessions(FString LookForName);
	UFUNCTION(BlueprintCallable, Category="EOS Functions")
    void JoinSession(FName Session);
    UFUNCTION(BlueprintCallable, Category="EOS Functions")
    void CloseSession();

    UFUNCTION(BlueprintCallable,BlueprintPure, Category="EOS Functions")
	FString GetPlayerUsername();

	UFUNCTION(BlueprintCallable,BlueprintPure, Category="EOS Functions")
	bool IsPlayerLoggedIn();


    // Function to initiate login
	UFUNCTION(BlueprintCallable, Category="EOS Functions")
    void LoginToEpicGames();

    UFUNCTION(BlueprintCallable, Category="EOS Functions")
    void CloseOldSession();

	private:
    // Callback for login completion
    void OnLoginComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& error);



    // Store the login complete delegate handle
    FDelegateHandle LoginCompleteDelegateHandle;
	
    void FindSession(FName Session);
	// Delegate functions for session management
    void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
    void OnFindSessionsComplete(bool bWasSuccessful);
    void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
    void OnEndSessionComplete(FName SessionName, bool bWasSuccessful);
    void OnCloseOldSessionComplete(FName SessionName, bool bWasSuccessful);
    void OnFindJoinResultComplete(bool bWasSuccessful);

    // Pointer to the session interface
    IOnlineSessionPtr SessionInterface;

    // Store the search results
    TSharedPtr<FOnlineSessionSearch> SessionSearch;

    // Store delegate handles
    FDelegateHandle CreateSessionCompleteDelegateHandle;
    FDelegateHandle FindSessionsCompleteDelegateHandle;
    FDelegateHandle JoinSessionCompleteDelegateHandle;
    FDelegateHandle EndSessionCompleteDelegateHandle;

    FString PlayerUserId;
    FName lSessionName;
public:
    UPROPERTY(BlueprintReadOnly,Category="EOS Variables")
    bool SessionExisting=false;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="EOS Variables")
	FString OpenLevelText;
    UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="EOS Variables")
    FString SessionDesiredName;
    UPROPERTY(BlueprintReadOnly,Category="EOS Variables")
    TArray<FSessionCustomUIType> AvailableSessions;
};
