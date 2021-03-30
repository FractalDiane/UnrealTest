// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "../Utils/Macros.h"
#include "../Data/CharacterData.h"

#include <GameFramework/Actor.h>

#include "BattleCharacter.generated.h"

UCLASS()
class BATTLESYSTEM_API ABattleCharacter : public AActor
{
	GENERATED_BODY()

private:
	int CharacterIndex;
	UCharacterData* Data;

	bool Dead = false;
	class USkeletalMeshComponent* CharacterModel;

public:	
	// Sets default values for this actor's properties
	ABattleCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	void SpawnCharacter();
	
	void PlayAnimation(FName Animation, bool Loop);

	SETTER(int, CharacterIndex);
	GETTER(UCharacterData*, Data);
	SETTER(UCharacterData*, Data);
	GETTER_BOOL(Dead);

	void ActivateRandomCamera();
};
