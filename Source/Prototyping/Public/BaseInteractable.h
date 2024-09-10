// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseInteractable.generated.h"

UCLASS()
class PROTOTYPING_API ABaseInteractable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseInteractable();

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variable")
	bool reseted=false;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variable")
	float dt=0.0f;

UFUNCTION(BlueprintCallable, Category = "Interactable")
	void ResetOutlineVariable();	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
