// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterModel.h"

#include <Engine/SkeletalMesh.h>

// Sets default values for this component's properties
UCharacterModel::UCharacterModel()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCharacterModel::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->FindComponentByClass<USkeletalMeshComponent>()->PlayAnimation(default_animation, true);
}


// Called every frame
void UCharacterModel::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

