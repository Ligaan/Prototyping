// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "EOS_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPING_API UEOS_GameInstance : public UGameInstance
{
	GENERATED_BODY()
	public:
	UFUNCTION(BlueprintCallable, Category="EOS Functions")
	void LogInWithEOS(FString ID,FString token,FString LoginType);

	UFUNCTION(BlueprintCallable,BlueprintPure, Category="EOS Functions")
	FString GetPlayerUsername();

	UFUNCTION(BlueprintCallable,BlueprintPure, Category="EOS Functions")
	bool IsPlayerLoggedIn();

	UFUNCTION(BlueprintCallable, Category="EOS Functions")
	void CreateEOSSession(bool bIsDedicatedServer,bool IsLANServer,int32 NumOfPublicConnections);

	UFUNCTION(BlueprintCallable, Category="EOS Functions")
	void FindSessionAndJoin(bool bIsDedicatedServer,bool IsLANServer,int32 NumOfPublicConnections);

	UFUNCTION(BlueprintCallable, Category="EOS Functions")
	void JoinSession();

	UFUNCTION(BlueprintCallable, Category="EOS Functions")
	void DestroySession();
	//TSharedRef<FOnlineSessionSearch> SessionSearch;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="EOS Variables")
	FString OpenLevelText;

	void LogInWithEOSReturn(int32 LocalUserNum,bool bWasSuccess,const FUniqueNetId& UserID,const FString& error);
	void OnCreateEOSSessionCompleted(FName SessionName,bool Success);
	void OnDestroyEOSSessionCompleted(FName SessionName,bool Success);
	void OnFindSessionCompleted(bool Success);
	void OnJoinSessionCompleted(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
};
