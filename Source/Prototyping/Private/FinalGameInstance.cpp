// Fill out your copyright notice in the Description page of Project Settings.


#include "FinalGameInstance.h"
#include "OnlineSessionSettings.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

UFinalGameInstance::UFinalGameInstance() {
    //// Get the OnlineSubsystem for EOS and initialize the SessionInterface
    //IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
    //if (OnlineSubsystem)
    //{
    //    SessionInterface = OnlineSubsystem->GetSessionInterface();

    //    if (SessionInterface.IsValid())
    //    {
    //        UE_LOG(LogTemp, Warning, TEXT("OnlineSubsystemEOS initialized and SessionInterface found!"));
    //    }
    //    else
    //    {
    //        UE_LOG(LogTemp, Error, TEXT("Failed to find SessionInterface for EOS!"));
    //    }
    //}
    //else
    //{
    //    UE_LOG(LogTemp, Error, TEXT("OnlineSubsystemEOS is not enabled or not found!"));
    //}
}

//bool UFinalGameInstance::IsPlayerLoggedIn()
//{
//    IOnlineSubsystem* SubsystemRef = IOnlineSubsystem::Get();
//    if (SubsystemRef) {
//        IOnlineIdentityPtr IdentityPointerRef = SubsystemRef->GetIdentityInterface();
//        if (IdentityPointerRef) {
//            return IdentityPointerRef->GetLoginStatus(0) == ELoginStatus::LoggedIn;
//        }
//    }
//    return false;
//}
//FString UFinalGameInstance::GetPlayerUsername()
//{
//    IOnlineSubsystem* SubsystemRef = IOnlineSubsystem::Get();
//    if (SubsystemRef) {
//        IOnlineIdentityPtr IdentityPointerRef = SubsystemRef->GetIdentityInterface();
//        if (IdentityPointerRef) {
//            if (IdentityPointerRef->GetLoginStatus(0) == ELoginStatus::LoggedIn) {
//                return IdentityPointerRef->GetPlayerNickname(0);
//            }
//        }
//    }
//    return FString();
//}
//void UFinalGameInstance::LoginToEpicGames()
//{
//    // Get the OnlineSubsystem for EOS
//    IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
//
//    if (OnlineSubsystem)
//    {
//        // Get the Identity Interface from the OnlineSubsystem
//        IOnlineIdentityPtr IdentityInterface = OnlineSubsystem->GetIdentityInterface();
//
//        if (IdentityInterface.IsValid())
//        {
//            UE_LOG(LogTemp, Warning, TEXT("OnlineSubsystemEOS found, attempting login via EOS..."));
//
//            // Define login credentials using the "accountportal" for Epic Games Account Portal
//            FOnlineAccountCredentials Credentials;
//            Credentials.Type = TEXT("accountportal"); // This tells EOS to use the Epic Games Account Portal
//            Credentials.Id = TEXT("");                // Leave empty for Account Portal
//            Credentials.Token = TEXT("");             // Leave empty for Account Portal
//
//            // Bind the login completion delegate
//            LoginCompleteDelegateHandle = IdentityInterface->AddOnLoginCompleteDelegate_Handle(0, FOnLoginCompleteDelegate::CreateUObject(this, &UFinalGameInstance::OnLoginComplete));
//
//            // Initiate login process for local user 0
//            IdentityInterface->Login(0, Credentials);
//        }
//        else
//        {
//            UE_LOG(LogTemp, Error, TEXT("Failed to find Identity Interface for EOS."));
//        }
//    }
//    else
//    {
//        UE_LOG(LogTemp, Error, TEXT("OnlineSubsystemEOS is not enabled or not found."));
//    }
//}
//
//void UFinalGameInstance::LoginAsDev(FString user)
//{
//    // Get the OnlineSubsystem for EOS
//    IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
//
//    if (OnlineSubsystem)
//    {
//        // Get the Identity Interface from the OnlineSubsystem
//        IOnlineIdentityPtr IdentityInterface = OnlineSubsystem->GetIdentityInterface();
//
//        if (IdentityInterface.IsValid())
//        {
//            UE_LOG(LogTemp, Warning, TEXT("OnlineSubsystemEOS found, attempting login via EOS..."));
//
//            // Define login credentials using the "accountportal" for Epic Games Account Portal
//            FOnlineAccountCredentials Credentials;
//            Credentials.Type = TEXT("developer"); // This tells EOS to use the Epic Games Account Portal
//            Credentials.Id = TEXT("localhost:6666");                // Leave empty for Account Portal
//            Credentials.Token = (TEXT("%s"), *user);             // Leave empty for Account Portal
//
//            // Bind the login completion delegate
//            LoginCompleteDelegateHandle = IdentityInterface->AddOnLoginCompleteDelegate_Handle(0, FOnLoginCompleteDelegate::CreateUObject(this, &UFinalGameInstance::OnLoginComplete));
//
//            // Initiate login process for local user 0
//            IdentityInterface->Login(0, Credentials);
//        }
//        else
//        {
//            UE_LOG(LogTemp, Error, TEXT("Failed to find Identity Interface for EOS."));
//        }
//    }
//    else
//    {
//        UE_LOG(LogTemp, Error, TEXT("OnlineSubsystemEOS is not enabled or not found."));
//    }
//}
//
//void UFinalGameInstance::CreateSession(FName sessionName, int32 NumOfPublicConnections)
//{
//    if (SessionInterface.IsValid())
//    {
//        FOnlineSessionSettings SessionSettings;
//        SessionSettings.bIsDedicated = false;
//        SessionSettings.bIsLANMatch = false;  // Not LAN
//        SessionSettings.NumPublicConnections = NumOfPublicConnections;  // Number of players allowed
//        SessionSettings.bShouldAdvertise = true;  // Advertise the session to others
//        SessionSettings.bUsesPresence = true;  // Use presence for EOS matchmaking
//        SessionSettings.bAllowJoinViaPresence = true;
//        SessionSettings.bAllowInvites = true;
//        //SessionSettings.bUseLobbiesIfAvailable = false;
//        SessionSettings.bAllowJoinInProgress = true;
//
//        SessionSettings.Set(FName("SESSION_NAME_KEY"), sessionName.ToString(), EOnlineDataAdvertisementType::ViaOnlineService);
//        //SessionSettings.Set(FName("SETTING_MAPNAME"), FString("Gameplay_Level"), EOnlineDataAdvertisementType::ViaOnlineService);
//
//        // Bind delegate for session creation
//        CreateSessionCompleteDelegateHandle = SessionInterface->AddOnCreateSessionCompleteDelegate_Handle(
//            FOnCreateSessionCompleteDelegate::CreateUObject(this, &UFinalGameInstance::OnCreateSessionComplete));
//
//        if (PlayerUserId == "") {
//            IOnlineSubsystem* SubsystemRef = IOnlineSubsystem::Get();
//            UE_LOG(LogTemp, Warning, TEXT("Empty user id!!!"));
//            if (SubsystemRef) {
//                IOnlineIdentityPtr IdentityPointerRef = SubsystemRef->GetIdentityInterface();
//                if (IdentityPointerRef) {
//                    if (IdentityPointerRef->GetLoginStatus(0) == ELoginStatus::LoggedIn) {
//                        PlayerUserId = IdentityPointerRef->GetUniquePlayerId(0)->ToString();
//                        UE_LOG(LogTemp, Warning, TEXT("Good User Id?%s"), *PlayerUserId);
//                    }
//                }
//            }
//        }
//        // Create session for local user 0
//        SessionInterface->CreateSession(0, FName(PlayerUserId), SessionSettings);
//
//    }
//    else {
//        UE_LOG(LogTemp, Error, TEXT("Invalid session interface"));
//    }
//}
//
//void UFinalGameInstance::CreateLobby(FName sessionName, int32 NumOfPublicConnections)
//{
//    if (SessionInterface.IsValid())
//    {
//        FOnlineSessionSettings SessionSettings;
//        SessionSettings.bIsDedicated = false;
//        SessionSettings.bIsLANMatch = false;  // Not LAN
//        SessionSettings.NumPublicConnections = NumOfPublicConnections;  // Number of players allowed
//        SessionSettings.bShouldAdvertise = true;  // Advertise the session to others
//        SessionSettings.bUsesPresence = true;  // Use presence for EOS matchmaking
//        SessionSettings.bAllowJoinViaPresence = true;
//        SessionSettings.bAllowInvites = true;
//        SessionSettings.bUseLobbiesIfAvailable = true;
//        SessionSettings.bAllowJoinInProgress = true;
//
//        SessionSettings.Set(FName("SESSION_NAME_KEY"), sessionName.ToString(), EOnlineDataAdvertisementType::ViaOnlineService);
//
//        FOnlineSessionSetting Setting;
//        FVariantData data;
//        Setting.AdvertisementType = EOnlineDataAdvertisementType::ViaOnlineService;
//        data.SetValue(FString("Test"));
//        Setting.Data = data;
//        SessionSettings.Set(FName("Test"), Setting);
//        //SessionSettings.Set(FName("SETTING_MAPNAME"), FString("Gameplay_Level"), EOnlineDataAdvertisementType::ViaOnlineService);
//
//        // Bind delegate for session creation
//        CreateSessionCompleteDelegateHandle = SessionInterface->AddOnCreateSessionCompleteDelegate_Handle(
//            FOnCreateSessionCompleteDelegate::CreateUObject(this, &UFinalGameInstance::OnCreateSessionComplete));
//
//        if (PlayerUserId == "") {
//            IOnlineSubsystem* SubsystemRef = IOnlineSubsystem::Get();
//            UE_LOG(LogTemp, Warning, TEXT("Empty user id!!!"));
//            if (SubsystemRef) {
//                IOnlineIdentityPtr IdentityPointerRef = SubsystemRef->GetIdentityInterface();
//                if (IdentityPointerRef) {
//                    if (IdentityPointerRef->GetLoginStatus(0) == ELoginStatus::LoggedIn) {
//                        PlayerUserId = IdentityPointerRef->GetUniquePlayerId(0)->ToString();
//                        UE_LOG(LogTemp, Warning, TEXT("Good User Id?%s"), *PlayerUserId);
//                    }
//                }
//            }
//        }
//        // Create session for local user 0
//        SessionInterface->CreateSession(0, FName(PlayerUserId), SessionSettings);
//
//    }
//    else {
//        UE_LOG(LogTemp, Error, TEXT("Invalid session interface"));
//    }
//}
//
//
//void UFinalGameInstance::OnLoginComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& error)
//{
//    IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
//    IOnlineIdentityPtr IdentityInterface = OnlineSubsystem->GetIdentityInterface();
//
//    if (IdentityInterface.IsValid())
//    {
//        // Remove the delegate to avoid being called again
//        IdentityInterface->ClearOnLoginCompleteDelegate_Handle(LocalUserNum, LoginCompleteDelegateHandle);
//    }
//
//    if (bWasSuccessful)
//    {
//        UE_LOG(LogTemp, Warning, TEXT("Successfully logged into Epic Games with UserId: %s"), *UserId.ToString());
//        PlayerUserId = UserId.ToString();
//    }
//    else
//    {
//        UE_LOG(LogTemp, Error, TEXT("Failed to log into Epic Games: %s"), *error);
//    }
//}
//
//void UFinalGameInstance::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
//{
//    // Clear the delegate
//    if (SessionInterface.IsValid())
//    {
//        SessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegateHandle);
//    }
//
//    if (bWasSuccessful)
//    {
//        UE_LOG(LogTemp, Warning, TEXT("Session '%s' created successfully!"), *SessionName.ToString());
//
//        // Optionally, you can now travel to the game map if this is the host
//        //GetWorld()->ServerTravel(OpenLevelText);
//        //SessionExisting = true;
//        lSessionName = SessionName;
//
//        if (SessionInterface.IsValid())
//        {
//            //SessionInterface->AddOnStartSessionCompleteDelegate_Handle(
//            //    FOnStartSessionCompleteDelegate::CreateUObject(this, &UFinalGameInstance::OnStartSessionComplete)
//            //);
//
//            //// Start the session with the given name
//            //SessionInterface->StartSession(SessionName);
//        }
//    }
//    else
//    {
//        UE_LOG(LogTemp, Error, TEXT("Failed to create session '%s'."), *SessionName.ToString());
//    }
//}
