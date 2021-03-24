// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include <Engine/DataAsset.h>
#include <Engine/SkeletalMesh.h>

#include "CharacterData.generated.h"

/**
 * 
 */
UCLASS()
class BATTLESYSTEM_API UCharacterData : public UDataAsset
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere)
	FString Name;
	UPROPERTY(EditAnywhere)
	unsigned int MaxHp;
	UPROPERTY(EditAnywhere)
	unsigned int MaxEp;
	UPROPERTY(EditAnywhere)
	unsigned int Defense;

	UPROPERTY(EditAnywhere)
	USkeletalMesh* Model;

	UPROPERTY(EditAnywhere)
	bool PartyMember = false;
};
