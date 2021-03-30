// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BattleCharacter.h"

#include <Components/ActorComponent.h>

#include <queue>

#include "BattleLogic.generated.h"

UCLASS()
class BATTLESYSTEM_API UBattleLogic : public UActorComponent
{
	GENERATED_BODY()

private:
	struct CharacterPriority {
		ABattleCharacter* Character;
		int Priority;

		CharacterPriority(ABattleCharacter* Character, int Priority) : Character{ Character }, Priority{ Priority } {}
		bool operator<(const CharacterPriority& Rvalue) const { return Priority < Rvalue.Priority; }
	};

	std::priority_queue<CharacterPriority> TurnQueue;

	//typedef TArray<ABattleCharacter*> CharacterArray;
	TArray<ABattleCharacter*> Party;
	TArray<ABattleCharacter*> Enemies;

	ABattleCharacter* CurrentCharacter;
	class UBattleUI* BattleUI;

	DECLARE_DYNAMIC_DELEGATE(FAllTurnsEndedSignature);

public:	
	// Sets default values for this actor's properties
	UBattleLogic();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	GETTER(TArray<ABattleCharacter*>&, Party);
	GETTER(TArray<ABattleCharacter*>&, Enemies);

	FAllTurnsEndedSignature OnAllTurnsEnded;

	void InitializeTurns();
	void EndTurn();
	void RunNextTurn();
};
