// Fill out your copyright notice in the Description page of Project Settings.


#include "EOS_GameInstance.h"
#include "OnlineSubsystemUtils.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Online/OnlineSessionNames.h"

void UEOS_GameInstance::LogInWithEOS(FString ID,FString token,FString LoginType)
{
    IOnlineSubsystem *SubsystemRef = IOnlineSubsystem::Get();
    if(SubsystemRef){
        IOnlineIdentityPtr IdentityPointerRef = SubsystemRef->GetIdentityInterface();
        if(IdentityPointerRef){
            FOnlineAccountCredentials AccountDetails;
            AccountDetails.Id = ID;
            AccountDetails.Token = token;
            AccountDetails.Type = LoginType;
            IdentityPointerRef->OnLoginCompleteDelegates->AddUObject(this,&UEOS_GameInstance::LogInWithEOSReturn);
            IdentityPointerRef->Login(0, AccountDetails);
        }
    }
}

FString UEOS_GameInstance::GetPlayerUsername()
{
     IOnlineSubsystem *SubsystemRef = IOnlineSubsystem::Get();
    if(SubsystemRef){
        IOnlineIdentityPtr IdentityPointerRef = SubsystemRef->GetIdentityInterface();
        if(IdentityPointerRef){
            if(IdentityPointerRef->GetLoginStatus(0)==ELoginStatus::LoggedIn){
                return IdentityPointerRef->GetPlayerNickname(0);
            }
        }
    }
    return FString();
}

bool UEOS_GameInstance::IsPlayerLoggedIn()
{ IOnlineSubsystem *SubsystemRef = IOnlineSubsystem::Get();
    if(SubsystemRef){
        IOnlineIdentityPtr IdentityPointerRef = SubsystemRef->GetIdentityInterface();
        if(IdentityPointerRef){
            return IdentityPointerRef->GetLoginStatus(0)==ELoginStatus::LoggedIn;
        }
    }
    return false;
}

void UEOS_GameInstance::LogInWithEOSReturn(int32 LocalUserNum, bool bWasSuccess, const FUniqueNetId& UserID, const FString& error)
{
    if(bWasSuccess){
UE_LOG(LogTemp,Warning,TEXT("Login success!"));
    }else{
        UE_LOG(LogTemp,Error,TEXT("Login fail reason - %s"),*error);
    }
}

void UEOS_GameInstance::OnCreateEOSSessionCompleted(FName SessionName, bool Success)
{
    if(Success){
        UE_LOG(LogTemp,Warning,TEXT("Switched maps success!"));
        GetWorld()->ServerTravel(OpenLevelText);
    }
}

void UEOS_GameInstance::OnFindSessionCompleted(bool Success)
{
}

void UEOS_GameInstance::OnJoinSessionCompleted(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
}

void UEOS_GameInstance::CreateEOSSession(bool bIsDedicatedServer, bool IsLANServer, int32 NumOfPublicConnections)
{
    IOnlineSubsystem *SubsystemRef = IOnlineSubsystem::Get();
    if(SubsystemRef){
        IOnlineSessionPtr SessionPtrRef = SubsystemRef->GetSessionInterface();
        if(SessionPtrRef){
            FOnlineSessionSettings SessionCreationInfo;
            SessionCreationInfo.bIsDedicated = bIsDedicatedServer;
            SessionCreationInfo.bAllowInvites = true;
            SessionCreationInfo.bIsLANMatch = IsLANServer;
            SessionCreationInfo.NumPublicConnections = NumOfPublicConnections;
            SessionCreationInfo.bUseLobbiesIfAvailable = true;
            SessionCreationInfo.bUsesPresence = false;
            SessionCreationInfo.bShouldAdvertise = true;
            SessionCreationInfo.Set(SEARCH_KEYWORDS,FString("RandomHi"),EOnlineDataAdvertisementType::ViaOnlineService);
            SessionPtrRef->OnCreateSessionCompleteDelegates.AddUObject(this,&UEOS_GameInstance::OnCreateEOSSessionCompleted);       
            SessionPtrRef->CreateSession(0,FName("MainSession"),SessionCreationInfo);
        }
    }
}

void UEOS_GameInstance::FindSessionAndJoin(bool bIsDedicatedServer, bool IsLANServer, int32 NumOfPublicConnections)
{
}

void UEOS_GameInstance::JoinSession()
{
}
