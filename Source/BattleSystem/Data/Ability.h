// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "../Utils/Macros.h"

#include <Engine/DataAsset.h>
#include <Engine/Texture2D.h>

#include "Ability.generated.h"

/**
 * 
 */
UCLASS()
class BATTLESYSTEM_API UAbility : public UDataAsset
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere)
	FText Name;
	UPROPERTY(EditAnywhere)
	UTexture2D* Icon;

	UPROPERTY(EditAnywhere, DisplayName = "EP Cost")
	unsigned int EPCost;

public:
	inline FText GetAbilityName() { return Name; }
	inline UTexture2D* GetAbilityIcon() { return Icon; }
	GETTER(unsigned int, EPCost);
};
