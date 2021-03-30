// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleScene.h"

#include "BattleLogic.h"
#include "BattleCharacter.h"
#include "../GameController.h"

namespace {
	UGameController* GameInstance;
}

// Sets default values
ABattleScene::ABattleScene()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	auto* Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	BattleLogic = CreateDefaultSubobject<UBattleLogic>(TEXT("BattleLogic"));
}

// Called when the game starts or when spawned
void ABattleScene::BeginPlay()
{
	Super::BeginPlay();

	// Init logic
	SpawnAllCharacters();
	BattleLogic->InitializeTurns();
	BattleLogic->OnAllTurnsEnded.BindDynamic(this, &ABattleScene::NewTurn);

	// Init UI
	/*UUserWidget* Widget = CreateWidget(GetWorld(), UIBlueprintRef, TEXT("BattleUI"));
	BattleUI = Cast<UBattleUI>(Widget);
	Widget->AddToViewport();*/
	
	// Start battle
	GameInstance = Cast<UGameController>(GetGameInstance());
	GetWorld()->GetTimerManager().SetTimer(StartBattleTimerHandle, this, &ABattleScene::StartBattle, 1.5f, false);
}


void ABattleScene::StartBattle()
{
	BattleLogic->RunNextTurn();
}


void ABattleScene::NewTurn()
{
	BattleLogic->InitializeTurns();
	BattleLogic->RunNextTurn();
}


void ABattleScene::SpawnAllCharacters()
{
	// Party
	TArray<UCharacterData*> PartyData = PartyTest;// GameInstance->GetParty();
	FVector CurrentPos{ -600, -540, 49 };

	for (int i = 0; i < PartyData.Num(); i++) {
		SpawnCharacter(PartyData[i], CurrentPos, BattleLogic->GetParty(), i);
		CurrentPos.Y += 540;
	}

	// Enemies
	TArray<FEnemyGroupEntry> Enemies = EnemyGroup->GetEnemies();
	for (int i = 0; i < Enemies.Num(); i++) {
		SpawnCharacter(Enemies[i].Enemy, Enemies[i].Position, BattleLogic->GetEnemies(), i);
	}
}


void ABattleScene::SpawnCharacter(class UCharacterData* Data, FVector Position, TArray<class ABattleCharacter*>& ArrayToAddTo, int Index)
{
	ABattleCharacter* NewChar = GetWorld()->SpawnActor<ABattleCharacter>();
	NewChar->SetCharacterIndex(Index);

	NewChar->SetActorLocation(Position);
	NewChar->SetData(Data);
	NewChar->SpawnCharacter();

	ArrayToAddTo.Add(NewChar);
}
