// Fill out your copyright notice in the Description page of Project Settings.

#include "DetectionCharacter.h"
#include "Engine.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "BaseInteractable.h"

// Sets default values
ADetectionCharacter::ADetectionCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UCapsuleComponent *capsuleComponent = GetCapsuleComponent();
	capsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &ADetectionCharacter::OnOverlapBegin);
	capsuleComponent->OnComponentEndOverlap.AddDynamic(this, &ADetectionCharacter::OnOverlapEnd);
}

// Called when the game starts or when spawned
void ADetectionCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADetectionCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ADetectionCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ADetectionCharacter::DetectObjects()
{
	if (currentRoom)
	{
		TSet<UPrimitiveComponent *> components;
		currentRoom->GetOverlappingComponents(components);
		for (auto &c : components)
		{
			if (c->GetOwner()->ActorHasTag(tag) && (GetActorLocation()-c->GetOwner()->GetActorLocation()).Size()<detectionRadius)
			{
				UStaticMeshComponent *mesh = Cast<UStaticMeshComponent>(c);
				mesh->SetRenderCustomDepth(true);
				
				if (ABaseInteractable* interactable = Cast<ABaseInteractable>(c->GetOwner()); interactable != nullptr)
				{
					interactable->ResetOutlineVariable();
				}
			}
		}
	}
}

void ADetectionCharacter::OnOverlapBegin(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
										 UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep,
										 const FHitResult &SweepResult)
{
	if (OtherActor->ActorHasTag(TEXT("Room")))
	{
		currentRoom = OtherActor;
	}
}
void ADetectionCharacter::OnOverlapEnd(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
									   UPrimitiveComponent *OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->ActorHasTag(TEXT("Room")))
	{
		currentRoom = nullptr;
	}
}