// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleCharacter.h"

#include <Animation/AnimInstance.h>
#include <Camera/CameraComponent.h>
#include <Components/SkeletalMeshComponent.h>

// Sets default values
ABattleCharacter::ABattleCharacter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	auto* Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	CharacterModel = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterModel"));
	CharacterModel->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void ABattleCharacter::BeginPlay()
{
	Super::BeginPlay();

}


void ABattleCharacter::SpawnCharacter()
{
	CharacterModel->SetSkeletalMesh(Data->GetModel());
	CharacterModel->SetWorldRotation(FRotator{ 0, 90, 0 });
	CharacterModel->SetWorldScale3D(Data->GetModelScale());
	PlayAnimation("Idle", true);

	for (const FTransform& Position : Data->GetCameraPositions()) {
		UCameraComponent* Camera = NewObject<UCameraComponent>(this, UCameraComponent::StaticClass());
		FTransform Xform = Position;
		Xform.SetLocation(Xform.GetLocation() * Data->GetModelScale());
		Camera->SetWorldTransform(Xform);
		Camera->RegisterComponent();
		Camera->AttachTo(GetRootComponent());
	}
}


void ABattleCharacter::PlayAnimation(FName Animation, bool Loop)
{
	CharacterModel->PlayAnimation(Data->GetIdleAnimation(), Loop);
}


void ABattleCharacter::ActivateRandomCamera()
{
	TArray<UCameraComponent*> Array;
	GetComponents<UCameraComponent>(Array);

	int32 Rand = FMath::RandRange(0, Array.Num() - 1);
	for (int i = 0; i < Array.Num(); i++) {
		Array[i]->SetActive(i == Rand);
	}
}
