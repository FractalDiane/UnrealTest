// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ScrollBox.h"
#include "AbilityListUI.generated.h"

/**
 * 
 */
UCLASS()
class BATTLESYSTEM_API UAbilityListUI : public UScrollBox
{
	GENERATED_BODY()
	
public:
	void AddAbility(class UAbility* Ability, class UTexture2D* ButtonTexture);
	void ClearList();
};
