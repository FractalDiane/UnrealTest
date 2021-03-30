// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleLogic.h"

#include "BattleScene.h"
#include "../Data/CharacterData.h"
#include "../UI/BattleUI.h"

// Sets default values
UBattleLogic::UBattleLogic()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void UBattleLogic::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->GetFirstPlayerController()->SetViewTargetWithBlend(GetOwner());

	UUserWidget* Widget = CreateWidget(GetWorld(), Cast<ABattleScene>(GetOwner())->GetUIBlueprintRef(), TEXT("BattleUI"));
	BattleUI = Cast<UBattleUI>(Widget);
	Widget->AddToViewport();
}

// Called every frame
/*void ABattleLogic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}*/


void UBattleLogic::InitializeTurns()
{
	//CharacterArray ArrParty = Start ? _Party : this->Party;
	//CharacterArray ArrEnemies = Start ? _Enemies : this->Enemies;

	for (auto* Char : Party) {
		if (!Char->IsDead()) {
			TurnQueue.push(CharacterPriority(Char, Char->GetData()->GetAgility()));
		}
	}

	for (auto* Char : Enemies) {
		if (!Char->IsDead()) {
			TurnQueue.push(CharacterPriority(Char, Char->GetData()->GetAgility()));
		}
	}

	/*if (Start) {
		this->Party = _Party;
		this->Enemies = _Enemies;

		for (auto* Char : Party) {
			// initialize healthbar?
		}
	}*/
}


void UBattleLogic::EndTurn()
{

}


void UBattleLogic::RunNextTurn()
{
	do {
		if (!TurnQueue.empty()) {
			CurrentCharacter = TurnQueue.top().Character;
			TurnQueue.pop();
		}
		else {
			OnAllTurnsEnded.Execute();
			return;
		}
	} while (CurrentCharacter->IsDead());

	BattleUI->SetCurrentCharacter(CurrentCharacter);
	CurrentCharacter->ActivateRandomCamera();
	GetWorld()->GetFirstPlayerController()->SetViewTargetWithBlend(CurrentCharacter, 1.5f, VTBlend_Cubic);

	if (CurrentCharacter->GetData()->IsPartyMember()) {
		// Show UI
	}
}
