// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "CharacterData.h"
#include "../Utils/Macros.h"

#include <Engine/DataAsset.h>

#include "EnemyGroup.generated.h"


USTRUCT()
struct FEnemyGroupEntry {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	UCharacterData* Enemy;

	UPROPERTY(EditAnywhere)
	FVector Position;
};

UCLASS()
class BATTLESYSTEM_API UEnemyGroup : public UDataAsset
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	TArray<FEnemyGroupEntry> Enemies;

public:
	GETTER(const TArray<FEnemyGroupEntry>&, Enemies);
};
