// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "CharacterData.h"

#include <Engine/DataAsset.h>

#include "EnemyGroup.generated.h"

/**
 * 
 */
UCLASS()
class BATTLESYSTEM_API UEnemyGroup : public UDataAsset
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TArray<UCharacterData*> Enemies;
	
	UPROPERTY(EditAnywhere)
	TArray<FVector> EnemyPositions;
};
