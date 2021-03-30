// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "../Utils/Macros.h"
#include "../Data/EnemyGroup.h"

#include <GameFramework/Actor.h>
#include <Blueprint/UserWidget.h>

#include "BattleScene.generated.h"

UCLASS()
class BATTLESYSTEM_API ABattleScene : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	class UEnemyGroup* EnemyGroup;
	
	UPROPERTY(EditAnywhere)
	class UBattleLogic* BattleLogic;
	UPROPERTY(EditAnywhere, DisplayName = "UI Blueprint Ref")
	TSubclassOf<UUserWidget> UIBlueprintRef;

	UPROPERTY(EditAnywhere)
	TArray<class UCharacterData*> PartyTest;

	FTimerHandle StartBattleTimerHandle;
	
public:	
	// Sets default values for this actor's properties
	ABattleScene();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	GETTER(UEnemyGroup*, EnemyGroup);
	SETTER(UEnemyGroup*, EnemyGroup);
	GETTER(TSubclassOf<UUserWidget>, UIBlueprintRef);

	UFUNCTION()
	void StartBattle();
	UFUNCTION()
	void NewTurn();

	void SpawnAllCharacters();
	void SpawnCharacter(class UCharacterData* Data, FVector Position, TArray<class ABattleCharacter*>& ArrayToAddTo, int Index);
};
