// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Utils/Macros.h"

#include <Animation/AnimInstance.h>

#include "CharacterAnimation.generated.h"

/**
 * 
 */
UCLASS()
class BATTLESYSTEM_API UCharacterAnimation : public UAnimInstance
{
	GENERATED_BODY()

private:
	UAnimInstance* Parent;
	
public:
	SETTER(UAnimInstance*, Parent);

	bool GetBool(FName Name);
	void SetBool(FName Name, bool Value);
	int GetInt(FName Name);
	void SetInt(FName Name, int value);
	float GetFloat(FName Name);
	void SetFloat(FName Name, float value);
};
