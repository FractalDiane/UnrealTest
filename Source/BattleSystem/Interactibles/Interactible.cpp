// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactible.h"

#include "../Cosmo.h"

#include <Components/SphereComponent.h>

// Sets default values
AInteractible::AInteractible()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	InteractArea = CreateDefaultSubobject<USphereComponent>(TEXT("InteractArea"));
	InteractArea->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AInteractible::BeginPlay()
{
	Super::BeginPlay();
	
	InteractArea->OnComponentBeginOverlap.AddDynamic(this, &AInteractible::PlayerEnterArea);
	InteractArea->OnComponentEndOverlap.AddDynamic(this, &AInteractible::PlayerExitArea);
}

// Called every frame
void AInteractible::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AInteractible::Interact()
{}


void AInteractible::InteractFinish()
{}


void AInteractible::PlayerEnterArea(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ACosmo::StaticClass())) {
		PlayerInArea = true;
		ACosmo* Player = Cast<ACosmo>(OtherActor);
		Player->AddInteractibleInRange(this);
		Player->GetPlayerHUD()->SetInteractPrompt(InteractPrompt);
		Player->GetPlayerHUD()->ShowInteractHUD(true);
	}
}


void AInteractible::PlayerExitArea(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	if (OtherActor->IsA(ACosmo::StaticClass())) {
		PlayerInArea = false;
		ACosmo* Player = Cast<ACosmo>(OtherActor);
		Player->RemoveInteractibleInRange(this);
		Player->GetPlayerHUD()->ShowInteractHUD(false);
	}
}
