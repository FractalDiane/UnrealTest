// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#define GETTER(Type, Var) inline Type Get##Var() { return Var; }
#define SETTER(Type, Var) inline void Set##Var(Type Value) { Var = Value; }

/**
 * 
 */
/*class BATTLESYSTEM_API Macros
{
public:
	Macros();
	~Macros();
};*/
