// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DetectionCharacter.generated.h"

UCLASS()
class PROTOTYPING_API ADetectionCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADetectionCharacter();

	UFUNCTION(BlueprintCallable, Category = "Interactable")
	void DetectObjects();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Interactable")
    float detectionRadius = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Interactable")
    FName tag = "Interactable";

	UPROPERTY()
	AActor* currentRoom = nullptr;

	UFUNCTION()
  void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
    const FHitResult& SweepResult);

	UFUNCTION()
  void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
		UMaterialInterface* overlayMaterial;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
