// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "../Utils/Macros.h"
#include "Ability.h"

#include <Animation/AnimSequence.h>
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
	FText Name;
	UPROPERTY(EditAnywhere)
	unsigned int MaxHp;
	UPROPERTY(EditAnywhere)
	unsigned int MaxEp;
	UPROPERTY(EditAnywhere)
	unsigned int Defense;
	UPROPERTY(EditAnywhere)
	unsigned int Agility;

	UPROPERTY(EditAnywhere)
	TArray<UAbility*> Abilities;

	UPROPERTY(EditAnywhere)
	USkeletalMesh* Model;
	UPROPERTY(EditAnywhere)
	FVector ModelScale = FVector::OneVector;

	UPROPERTY(EditAnywhere)
	UAnimSequence* IdleAnimation;

	UPROPERTY(EditAnywhere)
	TArray<FTransform> CameraPositions;

	UPROPERTY(EditAnywhere)
	bool PartyMember = false;

public:
	GETTER(FText, Name);
	GETTER(unsigned int, MaxHp);
	GETTER(unsigned int, MaxEp);
	GETTER(unsigned int, Defense);
	GETTER(unsigned int, Agility);
	GETTER(const TArray<UAbility*>&, Abilities);
	GETTER_BOOL(PartyMember);

	GETTER(USkeletalMesh*, Model);
	GETTER(FVector, ModelScale);
	GETTER(UAnimSequence*, IdleAnimation);
	GETTER(const TArray<FTransform>&, CameraPositions);
};
