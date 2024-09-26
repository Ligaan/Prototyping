// Fill out your copyright notice in the Description page of Project Settings.

#include "LobbyUtilityFunctions.h"
#include "Core/PlayFabClientAPI.h"


void ULobbyUtilityFunctions::OnSuccess()
{
    
}
/*
if (MemberData.Num() != 0)
    {
        writer->WriteObjectStart(TEXT("MemberData"));
        for (TMap<FString, FString>::TConstIterator It(MemberData); It; ++It)
        {
            writer->WriteIdentifierPrefix((*It).Key);
            writer->WriteValue((*It).Value);
        }
        writer->WriteObjectEnd();
    }

bool PlayFab::MultiplayerModels::FMember::readFromValue(const TSharedPtr<FJsonObject>& obj)
{
    bool HasSucceeded = true;

    const TSharedPtr<FJsonObject>* MemberDataObject;
    if (obj->TryGetObjectField(TEXT("MemberData"), MemberDataObject))
    {
        for (TMap<FString, TSharedPtr<FJsonValue>>::TConstIterator It((*MemberDataObject)->Values); It; ++It)
        {
            MemberData.Add(It.Key(), It.Value()->AsString());
        }
    }

    const TSharedPtr<FJsonValue> MemberEntityValue = obj->TryGetField(TEXT("MemberEntity"));
    if (MemberEntityValue.IsValid() && !MemberEntityValue->IsNull())
    {
        MemberEntity = MakeShareable(new FEntityKey(MemberEntityValue->AsObject()));
    }

    const TSharedPtr<FJsonValue> PubSubConnectionHandleValue = obj->TryGetField(TEXT("PubSubConnectionHandle"));
    if (PubSubConnectionHandleValue.IsValid() && !PubSubConnectionHandleValue->IsNull())
    {
        FString TmpValue;
        if (PubSubConnectionHandleValue->TryGetString(TmpValue)) { PubSubConnectionHandle = TmpValue; }
    }

    return HasSucceeded;
}
*/