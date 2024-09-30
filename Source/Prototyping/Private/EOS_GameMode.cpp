// Fill out your copyright notice in the Description page of Project Settings.


#include "EOS_GameMode.h"
#include "OnlineSubsystemUtils.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "Interfaces/OnlineSessionInterface.h"

void AEOS_GameMode::PostLogin(APlayerController *NewPlayer)
{
    Super::PostLogin(NewPlayer);
    if(NewPlayer){
        FUniqueNetIdRepl UniqueNetIdRepl;
        if(NewPlayer->IsLocalController()){
            ULocalPlayer *LocalPlayerRef = NewPlayer->GetLocalPlayer();

            if(LocalPlayerRef){
                UniqueNetIdRepl = LocalPlayerRef->GetPreferredUniqueNetId();
            }else{

                UNetConnection *RemoteNetConnectionRef = Cast<UNetConnection>(NewPlayer->Player);
                check(IsValid(RemoteNetConnectionRef));
                UniqueNetIdRepl = RemoteNetConnectionRef->PlayerId;
            }
        }else{

             UNetConnection *RemoteNetConnectionRef = Cast<UNetConnection>(NewPlayer->Player);
                check(IsValid(RemoteNetConnectionRef));
                UniqueNetIdRepl = RemoteNetConnectionRef->PlayerId;
        }

        TSharedPtr<const FUniqueNetId> UniqueNetId =UniqueNetIdRepl.GetUniqueNetId();
        check(UniqueNetId!=nullptr)
        IOnlineSubsystem *SubsystemRef = IOnlineSubsystem::Get();
        IOnlineSessionPtr OnlineSessionPtr = SubsystemRef->GetSessionInterface();
        bool bRegistrationSuccess = OnlineSessionPtr->RegisterPlayer(FName("MainSession"),*UniqueNetId,false);
        if(bRegistrationSuccess){
            UE_LOG(LogTemp,Warning,TEXT("Registration Success"));
        }
    }
}
