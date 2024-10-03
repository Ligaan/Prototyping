// Fill out your copyright notice in the Description page of Project Settings.


#include "TestGameInstance.h"

#include "CommonSessionSubsystem.h"
#include "CommonUserSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

UTestGameInstance::UTestGameInstance()
{
    // Get the OnlineSubsystem for EOS and initialize the SessionInterface
    IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
    if (OnlineSubsystem)
    {
        SessionInterface = OnlineSubsystem->GetSessionInterface();

        if (SessionInterface.IsValid())
        {
            UE_LOG(LogTemp, Warning, TEXT("OnlineSubsystemEOS initialized and SessionInterface found!"));
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to find SessionInterface for EOS!"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("OnlineSubsystemEOS is not enabled or not found!"));
    }
}

void UTestGameInstance::CreateSession(FName sessionName,int32 NumOfPublicConnections)
{
    if (SessionInterface.IsValid())
    {
        FOnlineSessionSettings SessionSettings;
        SessionSettings.bIsLANMatch = false;  // Not LAN
        SessionSettings.NumPublicConnections = NumOfPublicConnections;  // Number of players allowed
        SessionSettings.bShouldAdvertise = true;  // Advertise the session to others
        SessionSettings.bUsesPresence = true;  // Use presence for EOS matchmaking
        SessionSettings.bAllowInvites = true;
        SessionSettings.bUseLobbiesIfAvailable = false;

        SessionSettings.Set(FName("SESSION_NAME_KEY"), sessionName.ToString(), EOnlineDataAdvertisementType::ViaOnlineService);

        // Bind delegate for session creation
        CreateSessionCompleteDelegateHandle = SessionInterface->AddOnCreateSessionCompleteDelegate_Handle(
            FOnCreateSessionCompleteDelegate::CreateUObject(this, &UTestGameInstance::OnCreateSessionComplete));

        if(PlayerUserId==""){
             IOnlineSubsystem *SubsystemRef = IOnlineSubsystem::Get();
             UE_LOG(LogTemp, Warning, TEXT("Empty user id!!!"));
            if(SubsystemRef){
                IOnlineIdentityPtr IdentityPointerRef = SubsystemRef->GetIdentityInterface();
                if(IdentityPointerRef){
                    if(IdentityPointerRef->GetLoginStatus(0)==ELoginStatus::LoggedIn){
                        PlayerUserId = IdentityPointerRef->GetUniquePlayerId(0)->ToString();
                        UE_LOG(LogTemp, Warning, TEXT("Good User Id?%s"),*PlayerUserId);
                    }
                }
            }
        }
        // Create session for local user 0
        SessionInterface->CreateSession(0, FName(PlayerUserId), SessionSettings);
    }else{
        UE_LOG(LogTemp, Error, TEXT("Invalid session interface"));
    }
}

void UTestGameInstance::FindSessions(FString LookForName)
{
    if (SessionInterface.IsValid())
    {
        SessionSearch = MakeShareable(new FOnlineSessionSearch());
        SessionSearch->bIsLanQuery = false;  // Not LAN
        SessionSearch->MaxSearchResults = 20;  // Limit the number of search results
        SessionSearch->PingBucketSize = 200;  // Max ping allowed for session
        //SessionSearch->
        SessionDesiredName = LookForName;
        // Bind delegate for session finding
        FindSessionsCompleteDelegateHandle = SessionInterface->AddOnFindSessionsCompleteDelegate_Handle(
            FOnFindSessionsCompleteDelegate::CreateUObject(this, &UTestGameInstance::OnFindSessionsComplete));

        // Start searching for sessions
        SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
    }
}

void UTestGameInstance::JoinSession(FName Session)
{   
    if (SessionInterface.IsValid() && SessionSearch.IsValid() && SessionSearch->SearchResults.Num() > 0)
    {
        // Bind delegate for joining session
        JoinSessionCompleteDelegateHandle = SessionInterface->AddOnJoinSessionCompleteDelegate_Handle(
            FOnJoinSessionCompleteDelegate::CreateUObject(this, &UTestGameInstance::OnJoinSessionComplete));

        // Join the first available session
        UE_LOG(LogTemp, Error, TEXT("Close to joining?"));
        SessionInterface->JoinSession(0, Session, SessionSearch->SearchResults[SessionSearchIndex]);
    }
}

void UTestGameInstance::CloseSession()
{
    if (SessionExisting && SessionInterface.IsValid())
    {
        // Bind delegate for session end completion
        EndSessionCompleteDelegateHandle = SessionInterface->AddOnEndSessionCompleteDelegate_Handle(
            FOnEndSessionCompleteDelegate::CreateUObject(this, &UTestGameInstance::OnEndSessionComplete));

        // Call EndSession with the session name
        if(lSessionName!=""){
        SessionInterface->EndSession(lSessionName);
        }else{
           UE_LOG(LogTemp, Warning, TEXT("WTF.")); 
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Session interface is not valid."));
    }
}

FString UTestGameInstance::GetPlayerUsername()
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

bool UTestGameInstance::IsPlayerLoggedIn()
{
    IOnlineSubsystem *SubsystemRef = IOnlineSubsystem::Get();
    if(SubsystemRef){
        IOnlineIdentityPtr IdentityPointerRef = SubsystemRef->GetIdentityInterface();
        if(IdentityPointerRef){
            return IdentityPointerRef->GetLoginStatus(0)==ELoginStatus::LoggedIn;
        }
    }
    return false;
}

void UTestGameInstance::LoginToEpicGames()
{
    // Get the OnlineSubsystem for EOS
    IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
    
    if (OnlineSubsystem)
    {
        // Get the Identity Interface from the OnlineSubsystem
        IOnlineIdentityPtr IdentityInterface = OnlineSubsystem->GetIdentityInterface();
        
        if (IdentityInterface.IsValid())
        {
            UE_LOG(LogTemp, Warning, TEXT("OnlineSubsystemEOS found, attempting login via EOS..."));
            
            // Define login credentials using the "accountportal" for Epic Games Account Portal
            FOnlineAccountCredentials Credentials;
            Credentials.Type = TEXT("accountportal"); // This tells EOS to use the Epic Games Account Portal
            Credentials.Id = TEXT("");                // Leave empty for Account Portal
            Credentials.Token = TEXT("");             // Leave empty for Account Portal
            
            // Bind the login completion delegate
            LoginCompleteDelegateHandle = IdentityInterface->AddOnLoginCompleteDelegate_Handle(0, FOnLoginCompleteDelegate::CreateUObject(this, &UTestGameInstance::OnLoginComplete));
            
            // Initiate login process for local user 0
            IdentityInterface->Login(0, Credentials);
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to find Identity Interface for EOS."));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("OnlineSubsystemEOS is not enabled or not found."));
    }
}

void UTestGameInstance::CloseOldSession()
{
    if(IsPlayerLoggedIn() && SessionInterface.IsValid())
    {
        if(PlayerUserId==""){
             IOnlineSubsystem *SubsystemRef = IOnlineSubsystem::Get();
            if(SubsystemRef){
                IOnlineIdentityPtr IdentityPointerRef = SubsystemRef->GetIdentityInterface();
                if(IdentityPointerRef){
                    if(IdentityPointerRef->GetLoginStatus(0)==ELoginStatus::LoggedIn){
                        PlayerUserId = IdentityPointerRef->GetUniquePlayerId(0)->ToString();
                         EndSessionCompleteDelegateHandle = SessionInterface->AddOnEndSessionCompleteDelegate_Handle(
                        FOnEndSessionCompleteDelegate::CreateUObject(this, &UTestGameInstance::OnEndSessionComplete));
                        /*if (SessionInterface->GetNamedSession(SessionName))
                        {
                            if (SessionInterface->GetNamedSession(SessionName)->SessionState == EOnlineSessionState::Active)
                            {
                                SessionInterface->EndSession(SessionName);
                                UE_LOG(LogTemp, Log, TEXT("Session ended successfully."));
                            }
                            else
                            {
                                UE_LOG(LogTemp, Warning, TEXT("Can't end session, current state is: %s"), 
                                *UEnum::GetDisplayValueAsText(SessionInterface->GetNamedSession(SessionName)->SessionState).ToString());
                                }
                        }*/
                        //SessionInterface->EndSession(FName(PlayerUserId));
                        SessionInterface->DestroySession(FName(PlayerUserId));
                        UE_LOG(LogTemp, Warning, TEXT("All good?"));
                    }
                }
            }
        }else{
            //SessionInterface->EndSession(FName(PlayerUserId));
            SessionInterface->DestroySession(FName(PlayerUserId));
                        UE_LOG(LogTemp, Warning, TEXT("All good?"));
        }
    }
}

void UTestGameInstance::OnLoginComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& error)
{
    IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
    IOnlineIdentityPtr IdentityInterface = OnlineSubsystem->GetIdentityInterface();

    if (IdentityInterface.IsValid())
    {
        // Remove the delegate to avoid being called again
        IdentityInterface->ClearOnLoginCompleteDelegate_Handle(LocalUserNum, LoginCompleteDelegateHandle);
    }

    if (bWasSuccessful)
    {
        UE_LOG(LogTemp, Warning, TEXT("Successfully logged into Epic Games with UserId: %s"), *UserId.ToString());
        PlayerUserId = UserId.ToString();
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to log into Epic Games: %s"), *error);
    }
}

void UTestGameInstance::FindSession(FName SessionName)
{
    if (SessionInterface.IsValid())
    {
        SessionSearch = MakeShareable(new FOnlineSessionSearch());
        SessionSearch->bIsLanQuery = false;  // Not LAN
        SessionSearch->MaxSearchResults = 20;  // Limit the number of search results
        SessionSearch->PingBucketSize = 200;  // Max ping allowed for session

        SessionToJoin = SessionName.ToString();
        //SessionSearch->QuerySettings.Set(FName("SESSION_NAME_KEY"), SessionName, EOnlineComparisonOp::Equals);
        // Bind delegate for session finding
        FindSessionsCompleteDelegateHandle = SessionInterface->AddOnFindSessionsCompleteDelegate_Handle(
            FOnFindSessionsCompleteDelegate::CreateUObject(this, &UTestGameInstance::OnFindJoinResultComplete));

        // Start searching for sessions
        SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
    }
}

void UTestGameInstance::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{

    // Clear the delegate
    if (SessionInterface.IsValid())
    {
        SessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegateHandle);
    }

    if (bWasSuccessful)
    {
        UE_LOG(LogTemp, Warning, TEXT("Session '%s' created successfully!"), *SessionName.ToString());

        // Optionally, you can now travel to the game map if this is the host
        //GetWorld()->ServerTravel(OpenLevelText);
        SessionExisting = true;
        lSessionName = SessionName;

        JoinSession(SessionName);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to create session '%s'."), *SessionName.ToString());
    }
}

void UTestGameInstance::OnFindSessionsComplete(bool bWasSuccessful)
{
    // Clear the delegate
    if (SessionInterface.IsValid())
    {
        SessionInterface->ClearOnFindSessionsCompleteDelegate_Handle(FindSessionsCompleteDelegateHandle);
    }

    if (bWasSuccessful && SessionSearch.IsValid())
    {
        UE_LOG(LogTemp, Log, TEXT("Found %d sessions."), SessionSearch->SearchResults.Num());

        if (SessionSearch->SearchResults.Num() > 0)
        {
            // Automatically join the first found session
            //JoinSession();

                AvailableSessions = TArray<FSessionCustomUIType>();
            for (const FOnlineSessionSearchResult& SearchResult : SessionSearch->SearchResults)
            {
                FString SessionName;
                UE_LOG(LogTemp, Warning, TEXT("Brooooooooooooooo"));
                // Retrieve the custom session name from the session settings
                if (SearchResult.Session.SessionSettings.Get(FName("SESSION_NAME_KEY"), SessionName))
                {UE_LOG(LogTemp, Warning, TEXT("Brooooooooooooooo%s"),*SessionDesiredName);
                    // Check if the session name contains the desired substring
                    if (SessionName.Contains(SessionDesiredName))
                    {
                        UE_LOG(LogTemp, Warning, TEXT("Brooooooooooooooo"));
                        FSessionCustomUIType currentSessionData = {};
                        FString SessionId = SearchResult.GetSessionIdStr();
                        int32 NumOpenPublicConnections = SearchResult.Session.NumOpenPublicConnections;

                        currentSessionData.SessionId = SessionId;
                        currentSessionData.SessionName = SessionName;
                        currentSessionData.MaxPlayerNumber = SearchResult.Session.SessionSettings.NumPublicConnections;
                        currentSessionData.CurrentPlayerNumber = currentSessionData.MaxPlayerNumber - NumOpenPublicConnections;
                        // Log or use the session as needed
                        AvailableSessions.Add(currentSessionData);
                        UE_LOG(LogTemp, Log, TEXT("Session ID: %s, Name: %s, Host: %s, Open Slots: %d"),
                               *SessionId, *SessionName, *SearchResult.Session.OwningUserName, NumOpenPublicConnections);
                    }
                }
            }
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to find any sessions."));
    }
}

void UTestGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
    // Clear the delegate
    if (SessionInterface.IsValid())
    {
        SessionInterface->ClearOnJoinSessionCompleteDelegate_Handle(JoinSessionCompleteDelegateHandle);
    }

    if (Result == EOnJoinSessionCompleteResult::Success)
    {
        UE_LOG(LogTemp, Log, TEXT("Successfully joined session '%s'!"), *SessionName.ToString());

        // Get the session URL to travel to the game map
        FString ConnectInfo;
        if (SessionInterface->GetResolvedConnectString(SessionName, ConnectInfo))
        {
            // Client travels to the host
            APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
            if (PlayerController)
            {
                PlayerController->ClientTravel(ConnectInfo, TRAVEL_Absolute);
            }
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to join session '%s'."), *SessionName.ToString());
    }
}

void UTestGameInstance::OnEndSessionComplete(FName SessionName, bool bWasSuccessful)
{
    // Clear the delegate
    SessionInterface->ClearOnEndSessionCompleteDelegate_Handle(EndSessionCompleteDelegateHandle);

    if (bWasSuccessful)
    {
        UE_LOG(LogTemp, Log, TEXT("Session %s closed successfully."), *SessionName.ToString());
        // Perform any additional cleanup or state changes as needed
        SessionExisting = false;
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to close session %s."), *SessionName.ToString());
    }
}

void UTestGameInstance::OnCloseOldSessionComplete(FName SessionName, bool bWasSuccessful)
{
    // Clear the delegate
    SessionInterface->ClearOnEndSessionCompleteDelegate_Handle(EndSessionCompleteDelegateHandle);

    if (bWasSuccessful)
    {
        UE_LOG(LogTemp, Log, TEXT("Session %s closed successfully."), *SessionName.ToString());
        // Perform any additional cleanup or state changes as needed
        SessionExisting = false;
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to close session %s."), *SessionName.ToString());
    }
}

void UTestGameInstance::OnFindJoinResultComplete(bool bWasSuccessful)
{
    // Clear the delegate
    if (SessionInterface.IsValid())
    {
        SessionInterface->ClearOnFindSessionsCompleteDelegate_Handle(FindSessionsCompleteDelegateHandle);
    }

    if (bWasSuccessful && SessionSearch.IsValid())
    {
        UE_LOG(LogTemp, Log, TEXT("Found %d sessions."), SessionSearch->SearchResults.Num());

        if (SessionSearch->SearchResults.Num() > 0)
        {
            int32 lSessionSearchIndex = 0;
            for (const FOnlineSessionSearchResult& SearchResult : SessionSearch->SearchResults)
            {
                    UE_LOG(LogTemp, Warning, TEXT("Close!%s   %s"),*SearchResult.GetSessionIdStr(),*SessionToJoin);
                    if(SearchResult.GetSessionIdStr() == SessionToJoin){
                    SessionSearchIndex = lSessionSearchIndex;
                     UE_LOG(LogTemp, Warning, TEXT("Found session to join!"));
                    break;
                    }
                
                lSessionSearchIndex++;
            }
        }
        JoinSession(FName(SessionToJoin));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to find any sessions."));
    }
}
