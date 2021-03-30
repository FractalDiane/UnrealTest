// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Data/CharacterData.h"

#include <Engine/GameInstance.h>

#include "GameController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLESYSTEM_API UGameController : public UGameInstance
{
	GENERATED_BODY()
	
private:
	TArray<UCharacterData*> Party;

public:
	UGameController();

	virtual void Init() override;

public:
	GETTER(const TArray<UCharacterData*>&, Party);
};
